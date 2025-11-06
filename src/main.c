// main.c - simple single-file lexer+parser benchmark CLI (pretty printing + JSON stats)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>
#include <inttypes.h> // for PRIu64
#include <math.h>     // for fmax

#include "file.h"
#include "lexer.h"
#include "parser.h"
#include "parse_statements.h"
#include "ast.h"
#include "arena.h"

#include "type.h"
#include "scope.h"

#define EXIT_USAGE 1
#define EXIT_IO    2
#define EXIT_LEX   3
#define EXIT_PARSE 4
#define EXIT_TYPE  5
#define EXIT_SCOPE 6

typedef struct {
    int print_tokens;
    int print_ast;
    int print_time;
    int print_types;
} Options;

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s <file> [options]\n", prog);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -t, --tokens    Print all tokens\n");
    fprintf(stderr, "  -a, --ast       Print the parsed AST (after parsing)\n");
    fprintf(stderr, "  -y, --types     Print type internment results\n");
    fprintf(stderr, "  -T, --time      Print lex/parse timing and throughput\n");
    fprintf(stderr, "  -h, --help      Show this help\n");
    fprintf(stderr, "  -v, --version   Print version and exit\n");
}

static void print_version(void) {
    printf("Lexer+Parser Benchmark CLI v1.2\n");
}

static int parse_options(int argc, char **argv, Options *opts, const char **out_path) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }
    *out_path = argv[1];

    opts->print_tokens = 0;
    opts->print_ast = 0;
    opts->print_time = 0;
    opts->print_types = 0;

    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "--tokens") == 0 || strcmp(argv[i], "-t") == 0) opts->print_tokens = 1;
        else if (strcmp(argv[i], "--ast") == 0 || strcmp(argv[i], "-a") == 0) opts->print_ast = 1;
    else if (strcmp(argv[i], "--types") == 0 || strcmp(argv[i], "-y") == 0) opts->print_types = 1;
        else if (strcmp(argv[i], "--time") == 0 || strcmp(argv[i], "-T") == 0) opts->print_time = 1;
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) { print_usage(argv[0]); return 0; }
        else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) { print_version(); return 0; }
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 0;
        }
    }
    return 1;
}

static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

static long get_peak_rss_kb(void) {
    struct rusage ru;
    if (getrusage(RUSAGE_SELF, &ru) != 0) return -1;
#if defined(__APPLE__) || defined(__MACH__) || defined(__FreeBSD__)
    return (long)(ru.ru_maxrss / 1024);
#else
    return (long)ru.ru_maxrss;
#endif
}

static void print_size_kb_mb(size_t bytes) {
    double kb = (double)bytes / 1024.0;
    double mb = kb / 1024.0;
    printf("%zu bytes (%.2f KB, %.2f MB)", bytes, kb, mb);
}

/* ---------- Pretty-print helpers for benchmark output ---------- */

static void human_readable_bytes(size_t bytes, char *out, size_t out_len) {
    double kb = (double)bytes / 1024.0;
    double mb = kb / 1024.0;
    if (bytes >= (1u << 20)) snprintf(out, out_len, "%.2f MB", mb);
    else if (bytes >= 1024) snprintf(out, out_len, "%.2f KB", kb);
    else snprintf(out, out_len, "%zu B", bytes);
}

/* ANSI color codes */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

/* Box drawing characters for prettier output */
#define BOX_H   "─"
#define BOX_V   "│"
#define BOX_TL  "┌"
#define BOX_TR  "┐"
#define BOX_BL  "└"
#define BOX_BR  "┘"
#define BOX_T   "┬"
#define BOX_B   "┴"
#define BOX_L   "├"
#define BOX_R   "┤"
#define BOX_X   "┼"

static void print_box_line(const char *left, const char *middle, const char *right, int width) {
    printf("%s", left);
    for (int i = 0; i < width - 2; i++) printf(BOX_H);
    printf("%s\n", right);
}

static void print_progress_bar(double value, double max_value, int width, const char *color) {
    if (max_value <= 0) max_value = 1.0;
    int filled = (int)(((value / max_value) * width) + 0.5); // Round to nearest integer
    if (filled > width) filled = width;
    
    printf("%s", color);
    for (int i = 0; i < filled; i++) printf("█");
    printf(RESET DIM);
    for (int i = filled; i < width; i++) printf("░");
    printf(RESET);
}

static void human_readable_time(double seconds, char *out, size_t out_len) {
    snprintf(out, out_len, "%.3f ms", seconds * 1e3);
}

/* Pretty-print the benchmark summary table + JSON */
static void print_benchmark_stats(const char *filename,
                                  size_t file_size,
                                  size_t token_count,
                                  double tokenization_time,
                                  double parsing_time,
                                  size_t arena_used_lex,
                                  size_t arena_used_parse,
                                  long peak_rss_before_kb,
                                  long peak_rss_after_kb) {
    // Calculate derived values
    double type_inference_time = 0.0; // Not implemented yet
    double total_time = tokenization_time + parsing_time + type_inference_time;
    size_t arena_total_allocated = arena_used_lex + arena_used_parse;
    size_t rss_total = (peak_rss_after_kb - peak_rss_before_kb) * 1024;
    size_t tokens_second = tokenization_time > 0 ? (size_t)(token_count / tokenization_time) : 0;
    
    // Get maximum time for progress bars
    double max_time = fmax(fmax(tokenization_time, parsing_time), type_inference_time);
    if (max_time <= 0) max_time = total_time; // fallback
    
    // Calculate memory metrics
    char arena_size_str[32], rss_str[32];
    human_readable_bytes(arena_total_allocated, arena_size_str, sizeof(arena_size_str));
    human_readable_bytes(rss_total, rss_str, sizeof(rss_str));
    
    // Header
    printf("\n┌─────────────────────────────────────────────────────────────────────┐\n");
    printf("│" BOLD "                          COMPILATION REPORT                         " RESET "│\n");
    printf("└─────────────────────────────────────────────────────────────────────┘\n\n");
    
    // File info
    printf("File: %s (%zu bytes)\n\n", filename, file_size);
    
    // Timing section
    printf(BOLD "PERFORMANCE METRICS\n" RESET);
    printf("┌─────────────────┬──────────┬──────────────────┬────────────┬────────────┐\n");
    printf("│ %-15s │ %-8s │ %-16s │ %-10s │ %-10s │\n", "Phase", "Time", "Distribution", "Percentage", "ns/Token");
    printf("├─────────────────┼──────────┼──────────────────┼────────────┼────────────┤\n");
    
    char tokenization_str[32], parsing_str[32], inference_str[32], total_str[32];
    human_readable_time(tokenization_time, tokenization_str, sizeof(tokenization_str));
    human_readable_time(parsing_time, parsing_str, sizeof(parsing_str));
    human_readable_time(type_inference_time, inference_str, sizeof(inference_str));
    human_readable_time(total_time, total_str, sizeof(total_str));
    
    // Tokenization
    double tokenization_ns_per_token = token_count > 0 ? (tokenization_time * 1e9) / token_count : 0.0;
    printf("│ %-15s │ %8s │ ", "Tokenization", tokenization_str);
    print_progress_bar(tokenization_time, total_time, 16, "");
    printf(" │ %9.1f%% │ %9.1f  │\n", (tokenization_time / total_time) * 100, tokenization_ns_per_token);
    
    // Parsing
    double parsing_ns_per_token = token_count > 0 ? (parsing_time * 1e9) / token_count : 0.0;
    printf("│ %-15s │ %8s │ ", "Parsing", parsing_str);
    print_progress_bar(parsing_time, total_time, 16, "");
    printf(" │ %9.1f%% │ %9.1f  │\n", (parsing_time / total_time) * 100, parsing_ns_per_token);
    
    // Type inference (placeholder)
    //printf("│ %-15s │ %8s │ ", "Type Inference", inference_str);
    //print_progress_bar(type_inference_time, total_time, 16, "");
    //printf(" │ %9.1f%% │\n", total_time > 0 ? (type_inference_time / total_time) * 100 : 0.0);
    
    printf("└─────────────────┴──────────┴──────────────────┴────────────┴────────────┘\n");
    printf("\n");
 
    
    // Memory section
    printf(BOLD "MEMORY USAGE\n" RESET);
    printf("┌──────────────────────┬─────────────┬──────────────┐\n");
    printf("│ %-20s │ %-11s │ %-12s │\n", "Metric", "Value", "Bytes/Token");
    printf("├──────────────────────┼─────────────┼──────────────┤\n");
    
    // Calculate bytes per token for each phase
    double lex_bytes_per_token = token_count > 0 ? (double)arena_used_lex / token_count : 0.0;
    double parse_bytes_per_token = token_count > 0 ? (double)arena_used_parse / token_count : 0.0;
    double total_bytes_per_token = token_count > 0 ? (double)arena_total_allocated / token_count : 0.0;
    
    char lex_arena_str[32], parse_arena_str[32];
    human_readable_bytes(arena_used_lex, lex_arena_str, sizeof(lex_arena_str));
    human_readable_bytes(arena_used_parse, parse_arena_str, sizeof(parse_arena_str));
    
    printf("│ %-20s │ %11s │ %10.1f B │\n", "Arena (Lexing)", lex_arena_str, lex_bytes_per_token);
    printf("│ %-20s │ %11s │ %10.1f B │\n", "Arena (Parsing)", parse_arena_str, parse_bytes_per_token);
    printf("│ %-20s │ %11s │ %10.1f B │\n", "Arena Total", arena_size_str, total_bytes_per_token);
    printf("│ %-20s │ %11s │ %-12s │\n", "RSS Delta", rss_str, "");
    
    printf("└──────────────────────┴─────────────┴──────────────┘\n");
    printf("\n");
    
    // Stats summary
    printf(BOLD "SUMMARY\n" RESET);
    printf("  Total Time: %s\n", total_str);
    printf("  Tokens: %zu\n", token_count);
    printf("  AST Nodes: 0 (not counted yet)\n"); // placeholder
    
    // Performance indicators
    double total_ns_per_token = token_count > 0 ? (total_time * 1e9) / token_count : 0.0;
    double throughput_mbps = file_size / (1024.0 * 1024.0) / total_time;
    printf("  Throughput: %.2f MB/s (tokens/sec: %zu)\n", throughput_mbps, tokens_second);
    printf("\n");
}

/* ---------- end pretty-print helpers ---------- */

static void print_type_signature(Type *type, int depth) {
    if (!type) {
        printf("NULL");
        return;
    }
    
    switch (type->kind) {
        case TY_NAMED:
            if (type->u.named.name_rec && type->u.named.name_rec->key) {
                const char *name = (const char*)((Slice*)type->u.named.name_rec->key)->ptr;
                printf("%s", name);
            } else {
                printf("unnamed");
            }
            break;
            
        case TY_PTR:
            print_type_signature(type->u.ptr.target, depth + 1);
            printf("*");
            break;
            
        case TY_ARRAY:
            print_type_signature(type->u.array.elem, depth + 1);
            if (type->u.array.size_known) {
                printf("[%lld]", (long long)type->u.array.size);
            } else {
                printf("[]");
            }
            break;
            
        case TY_FUNC:
            printf("(");
            for (size_t i = 0; i < type->u.func.param_count; i++) {
                if (i > 0) printf(", ");
                print_type_signature(type->u.func.params[i], depth + 1);
            }
            printf(") -> ");
            print_type_signature(type->u.func.ret, depth + 1);
            break;
            
        default:
            printf("unknown(%d)", type->kind);
            break;
    }
}

static void print_type_category_colored(Type *type) {
    if (!type) {
        printf(RED "(null)" RESET);
        return;
    }
    
    switch (type->kind) {
        case TY_NAMED: {
            if (type->u.named.name_rec && type->u.named.name_rec->key) {
                Slice *name_slice = (Slice*)type->u.named.name_rec->key;
                if (name_slice->ptr && name_slice->len > 0) {
                    // Check if it's a primitive type
                    if ((name_slice->len == 3 && strncmp((char*)name_slice->ptr, "i32", 3) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "i64", 3) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "f32", 3) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "f64", 3) == 0) ||
                        (name_slice->len == 4 && strncmp((char*)name_slice->ptr, "bool", 4) == 0) ||
                        (name_slice->len == 4 && strncmp((char*)name_slice->ptr, "char", 4) == 0) ||
                        (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "str", 3) == 0)) {
                        printf(BLUE "(primitive)" RESET);
                    } else {
                        printf(YELLOW "(named)" RESET);
                    }
                } else {
                    printf(YELLOW "(named)" RESET);
                }
            } else {
                printf(YELLOW "(named)" RESET);
            }
            break;
        }
        case TY_PTR:
            printf(GREEN "(pointer)" RESET);
            break;
        case TY_ARRAY:
            printf(MAGENTA "(array)" RESET);
            break;
        case TY_FUNC:
            printf(CYAN "(function)" RESET);
            break;
        default:
            printf(RED "(unknown)" RESET);
            break;
    }
}

static void print_type_internment_results(TypeChecker *tc, AstNode *program) {
    printf("\n" BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf(BOLD "                    TYPE INTERNMENT ANALYSIS" RESET "\n");
    printf(BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf("Total types interned: " YELLOW "%d" RESET "\n", tc->type_interner->dense_index_count);
    
    // Clean table header for interned types
    printf("\n" BOLD "┌─ INTERNED TYPES ──────────────────────────────────────────────────────────────┐" RESET "\n");
    printf(BOLD "│" RESET " %-4s │ %-50s │ %-12s " BOLD "│" RESET "\n", "IDX", "TYPE SIGNATURE", "CATEGORY");
    printf(BOLD "├──────┼────────────────────────────────────────────────────────┼──────────────┤" RESET "\n");
    for (int i = 0; i < tc->type_interner->dense_index_count; i++) {
        InternResult **result_ptr = (InternResult**)dynarray_get(tc->type_interner->dense_array, i);
        if (result_ptr && *result_ptr) {
            InternResult *result = *result_ptr;
            Slice *key_slice = (Slice*)result->key;
            Type *type = (Type*)key_slice->ptr;
            
            printf(BOLD "│" RESET " " YELLOW "%2d" RESET "   " BOLD "│" RESET " ", i);
            print_type_signature(type, 0);
            
            // Simple padding
            for (int p = 0; p < 15; p++) printf(" ");
            
            printf(" " BOLD "│" RESET " ");
            print_type_category_colored(type);
            printf("   " BOLD "│" RESET "\n");
        }
    }
    printf(BOLD "└──────┴──────────────────────────────────────────┴──────────────┘" RESET "\n");
    
    if (!program || !program->data.program.decls) {
        printf("\nNo function declarations found.\n");
        return;
    }
    
    printf("\n" BOLD "Function Type Mapping:" RESET "\n");
    size_t func_count = program->data.program.decls->count;
    
    for (size_t i = 0; i < func_count; i++) {
        AstNode *func_decl = *(AstNode**)dynarray_get(program->data.program.decls, i);
        if (!func_decl || func_decl->node_type != AST_FUNCTION_DECLARATION) continue;
        
        const char *func_name = "(unknown)";
        if (func_decl->data.function_declaration.name_rec && 
            func_decl->data.function_declaration.name_rec->key) {
            func_name = (const char*)((Slice*)func_decl->data.function_declaration.name_rec->key)->ptr;
        }
        
        printf("  " CYAN "%-12s" RESET, func_name);
        
        if (func_decl->type) {
            // Get the actual dense index from the interner
            Slice slice = { .ptr = (const char*)func_decl->type, .len = sizeof(Type) };
            InternResult *result = intern(tc->type_interner, &slice, NULL);
            int dense_index = result ? result->entry->dense_index : -1;
            
            printf(" → " YELLOW "dense_index: %2d" RESET, dense_index);
            
            if (func_decl->type->kind == TY_FUNC) {
                printf(" " DIM "(%zu params)" RESET, func_decl->type->u.func.param_count);
                
                // Show parameter details
                if (func_decl->type->u.func.param_count > 0) {
                    printf("\n");
                    for (size_t p = 0; p < func_decl->type->u.func.param_count; p++) {
                        Type *param_type = func_decl->type->u.func.params[p];
                        
                        // Get the dense index for this parameter type
                        Slice param_slice = { .ptr = (const char*)param_type, .len = sizeof(Type) };
                        InternResult *param_result = intern(tc->type_interner, &param_slice, NULL);
                        int param_dense_index = param_result ? param_result->entry->dense_index : -1;
                        
                        printf("    " DIM "param %zu:" RESET " ", p);
                        print_type_signature(param_type, 0);
                        printf(" " DIM "(dense_index: %d)" RESET, param_dense_index);
                        
                        // Add colored type category for param
                        printf(" ");
                        switch (param_type->kind) {
                            case TY_NAMED: {
                                const char *type_name = "unknown";
                                if (param_type->u.named.name_rec && param_type->u.named.name_rec->key) {
                                    Slice *name_slice = (Slice*)param_type->u.named.name_rec->key;
                                    if (name_slice->ptr && name_slice->len > 0) {
                                        // Check if it's a primitive type
                                        if ((name_slice->len == 3 && strncmp((char*)name_slice->ptr, "i32", 3) == 0) ||
                                            (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "i64", 3) == 0) ||
                                            (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "f32", 3) == 0) ||
                                            (name_slice->len == 3 && strncmp((char*)name_slice->ptr, "f64", 3) == 0) ||
                                            (name_slice->len == 4 && strncmp((char*)name_slice->ptr, "bool", 4) == 0) ||
                                            (name_slice->len == 4 && strncmp((char*)name_slice->ptr, "char", 4) == 0) ||
                                            (name_slice->len == 6 && strncmp((char*)name_slice->ptr, "string", 6) == 0)) {
                                            printf(BLUE "(primitive)" RESET);
                                        } else {
                                            printf(YELLOW "(named)" RESET);
                                        }
                                    } else {
                                        printf(YELLOW "(named)" RESET);
                                    }
                                } else {
                                    printf(YELLOW "(named)" RESET);
                                }
                                break;
                            }
                            case TY_PTR:
                                printf(GREEN "(pointer)" RESET);
                                break;
                            case TY_ARRAY:
                                printf(MAGENTA "(array)" RESET);
                                break;
                            case TY_FUNC:
                                printf(CYAN "(function)" RESET);
                                break;
                            default:
                                printf(RED "(unknown)" RESET);
                                break;
                        }
                        printf("\n");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Clean, simple format without tables
static void print_clean_type_internment_results(TypeChecker *tc, AstNode *program) {
    printf("\n" BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf(BOLD "                    TYPE INTERNMENT ANALYSIS" RESET "\n");
    printf(BOLD "═══════════════════════════════════════════════════════════════════" RESET "\n");
    printf("Total types interned: " YELLOW "%d" RESET "\n", tc->type_interner->dense_index_count);
    
    // Simple list of interned types
    printf("\n" BOLD "Interned Types:" RESET "\n");
    for (int i = 0; i < tc->type_interner->dense_index_count; i++) {
        InternResult **result_ptr = (InternResult**)dynarray_get(tc->type_interner->dense_array, i);
        if (result_ptr && *result_ptr) {
            InternResult *result = *result_ptr;
            Slice *key_slice = (Slice*)result->key;
            Type *type = (Type*)key_slice->ptr;
            
            printf("  " YELLOW "[%d]" RESET " ", i);
            print_type_signature(type, 0);
            printf(" ");
            print_type_category_colored(type);
            printf("\n");
        }
    }
    
    // Function symbol mapping
    if (!program || !program->data.program.decls) {
        printf("\n" DIM "No function declarations found." RESET "\n");
        return;
    }
    
    printf("\n" BOLD "Function Symbol Mapping:" RESET "\n");
    size_t func_count = program->data.program.decls->count;
    
    for (size_t i = 0; i < func_count; i++) {
        AstNode *func_decl = *(AstNode**)dynarray_get(program->data.program.decls, i);
        if (!func_decl || func_decl->node_type != AST_FUNCTION_DECLARATION) continue;
        
        const char *func_name = "(unknown)";
        if (func_decl->data.function_declaration.name_rec && 
            func_decl->data.function_declaration.name_rec->key) {
            func_name = (const char*)((Slice*)func_decl->data.function_declaration.name_rec->key)->ptr;
        }
        
        printf("\n  " CYAN "%s" RESET ":\n", func_name);
        
        // Show symbol location info
        if (func_decl->data.function_declaration.name_rec) {
            printf("    • Symbol ptr: " DIM "%p" RESET "\n", (void*)func_decl->data.function_declaration.name_rec);
            if (func_decl->data.function_declaration.name_rec->entry) {
                printf("    • Symbol Name Dense Index: " GREEN "[%d]" RESET "\n", 
                       func_decl->data.function_declaration.name_rec->entry->dense_index);
            } else {
                printf("    • Symbol Name Dense Index: " RED "none" RESET "\n");
            }
        }
        
        if (func_decl->type) {
            // Get the actual dense index from the interner
            Slice slice = { .ptr = (const char*)func_decl->type, .len = sizeof(Type) };
            InternResult *result = intern_peek(tc->type_interner, &slice);
            int dense_index = result ? result->entry->dense_index : -1;
            
            printf("    • Type Index: " YELLOW "[%d]" RESET " → ", dense_index);
            print_type_signature(func_decl->type, 0);
            printf(" ");
            print_type_category_colored(func_decl->type);
            printf("\n");
            
            if (func_decl->type->kind == TY_FUNC) {
                printf("    • Parameters (%zu):\n", func_decl->type->u.func.param_count);
                
                for (size_t p = 0; p < func_decl->type->u.func.param_count; p++) {
                    Type *param_type = func_decl->type->u.func.params[p];
                    
                    // Get the dense index for this parameter type
                    Slice param_slice = { .ptr = (const char*)param_type, .len = sizeof(Type) };
                    InternResult *param_result = intern(tc->type_interner, &param_slice, NULL);
                    int param_dense_index = param_result ? param_result->entry->dense_index : -1;
                    
                    printf("      [%zu] ", p);
                    print_type_signature(param_type, 0);
                    printf(" " YELLOW "[%d]" RESET " ", param_dense_index);
                    print_type_category_colored(param_type);
                    printf("\n");
                }
                // print return type
                Type *return_type = func_decl->type->u.func.ret;
                if (return_type) {
                    // Get the dense index for the return type
                    Slice return_slice = { .ptr = (const char*)return_type, .len = sizeof(Type) };
                    InternResult *return_result = intern(tc->type_interner, &return_slice, NULL);
                    int return_dense_index = return_result ? return_result->entry->dense_index : -1;

                    printf("    • Return Type: " YELLOW "[%d]" RESET " → ", return_dense_index);
                    print_type_signature(return_type, 0);
                    printf(" ");
                    print_type_category_colored(return_type);
                    printf("\n");
                } else {
                    printf("    • Return Type: " RED "none" RESET "\n");
                }

            }
        } else {
            printf("    • Type: " RED "none" RESET "\n");
        }
    }
    printf("\n");
}

int main(int argc, char **argv) {
    Options opts;
    const char *path = NULL;
    if (!parse_options(argc, argv, &opts, &path)) return EXIT_USAGE;

    char *src = read_file(path);
    if (!src) {
        fprintf(stderr, "Failed to read file: %s\n", path);
        return EXIT_IO;
    }
    size_t src_len = strlen(src);

    long peak_rss_before_kb = get_peak_rss_kb();

    Arena *arena = arena_create(1024 * 1024);
    if (!arena) {
        fprintf(stderr, "Failed to create arena\n");
        free(src);
        return EXIT_IO;
    }

    char *filename_in_arena = arena_alloc(arena, strlen(path) + 1);
    if (!filename_in_arena) {
        fprintf(stderr, "Failed to allocate filename in arena\n");
        arena_destroy(arena);
        free(src);
        return EXIT_IO;
    }
    strcpy(filename_in_arena, path);

    Lexer *lexer = lexer_create(src, src_len, arena);
    if (!lexer) {
        fprintf(stderr, "Failed to create lexer\n");
        arena_destroy(arena);
        free(src);
        return EXIT_LEX;
    }

    double t0 = now_seconds();
    if (!lexer_lex_all(lexer)) {
        fprintf(stderr, "Lexing failed\n");
        lexer_destroy(lexer);
        arena_destroy(arena);
        free(src);
        return EXIT_LEX;
    }
    double t1 = now_seconds();
    size_t arena_used_lex = arena_total_allocated(arena);


    size_t token_count = 0;
    if (lexer->tokens) token_count = lexer->tokens->count;

    if (opts.print_tokens) {
        for (size_t i = 0; i < token_count; i++) {
            Token *tok = (Token*)dynarray_get(lexer->tokens, i);
            print_token(tok);
        }
        printf("\n");
    }

    Parser *parser = parser_create(lexer->tokens, filename_in_arena, arena);
    if (!parser) {
        fprintf(stderr, "Failed to create parser\n");
        lexer_destroy(lexer);
        arena_destroy(arena);
        free(src);
        return EXIT_PARSE;
    }

    double t2 = now_seconds();
    ParseError err = {0};
    AstNode *program = parse_program(parser, &err);
    double t3 = now_seconds();
    size_t arena_used_parse = arena_total_allocated(arena) - arena_used_lex;

    if(err.message){
        print_parse_error(&err);
    }

    if (opts.print_ast && program) {
        print_ast(program, 0, lexer->keywords, lexer->identifiers, lexer->strings);
    }

    TypeChecker *tc = typecheck_create(arena, filename_in_arena);

    if (!tc) {
        fprintf(stderr, "Failed to create type checker\n");
        parser_free(parser);
        lexer_destroy(lexer);
        arena_destroy(arena);
        free(src);
        return EXIT_TYPE;
    }

    Scope *scope = scope_create(arena, NULL, lexer->identifiers->dense_index_count);
    if (!scope) {
        fprintf(stderr, "Failed to create scope\n");
        parser_free(parser);
        lexer_destroy(lexer);
        arena_destroy(arena);
        free(src);
        return EXIT_SCOPE;
    }   

    int res = intern_type_handles(tc, lexer->keywords);
    TypeError terr = {0};
    int result = intern_function_types(tc, scope, program, &terr);
    init_promotion_matrix();


    for (int i = 0; i < NUM_TYPE_KINDS; i++) {
        for (int j = 0; j < NUM_TYPE_KINDS; j++) {
            printf("%2d ", promotion_matrix[i][j]);
        }
        printf("\n");
    }

    if (result != 0) {
        fprintf(stderr, "Type internment failed\n");
        print_type_error(&terr);
        parser_free(parser);
        lexer_destroy(lexer);
        arena_destroy(arena);
        free(src);
        return EXIT_TYPE;
    }

    if (opts.print_types) {
        print_clean_type_internment_results(tc, program);
    }

    long peak_rss_after_kb = get_peak_rss_kb();

    if (opts.print_time) {
        print_benchmark_stats(path,
                              src_len,
                              token_count,
                              t1 - t0,   // lex_time
                              t3 - t2,   // parse_time
                              arena_used_lex,
                              arena_used_parse,
                              peak_rss_before_kb,
                              peak_rss_after_kb);
    }

    parser_free(parser);
    lexer_destroy(lexer);
    arena_destroy(arena);
    free(src);

    return 0;
}
