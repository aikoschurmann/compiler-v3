// main.c - driver: orchestrates lexing, parsing, type internment, reporting

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "lexer.h"
#include "parser.h"
#include "parse_statements.h"
#include "ast.h"
#include "arena.h"
#include "type.h"
#include "typecheck.h"
#include "type_print.h"
#include "scope.h"
#include "cli.h"
#include "metrics.h"

// Exit codes
#define EXIT_OK    0
#define EXIT_USAGE 1
#define EXIT_IO    2
#define EXIT_LEX   3
#define EXIT_PARSE 4
#define EXIT_TYPE  5

int main(int argc, char **argv) {
    // 1. Parse CLI Options
    Options opts;
    const char *path = NULL;
    if (!parse_options(argc, argv, &opts, &path)) {
        return EXIT_USAGE;
    }

    int exit_code = EXIT_OK;
    char *src = NULL;
    Arena *arena = NULL;
    Lexer *lexer = NULL;
    Parser *parser = NULL;
    
    // Metric tracking
    long peak_rss_before_kb = get_peak_rss_kb();
    double t_start = now_seconds();
    double t_lex = 0, t_parse = 0, t_sema = 0;
    size_t mem_lex = 0, mem_parse = 0, mem_sema = 0;

    // 2. Initialize Core Resources
    // Pre-allocate 4MB to avoid OS page fault jitter during initialization
    arena = arena_create(4 * 1024 * 1024);
    if (!arena) {
        fprintf(stderr, "Error: Failed to create memory arena\n");
        return EXIT_IO;
    }

    // Copy filename to arena for safety/lifetime management
    char *filename_interned = arena_alloc(arena, strlen(path) + 1);
    strcpy(filename_interned, path);

    // 3. Read Source File
    src = read_file(path);
    if (!src) {
        fprintf(stderr, "Error: Failed to read file: %s\n", path);
        exit_code = EXIT_IO;
        goto cleanup;
    }
    size_t src_len = strlen(src);

    // ---------------------------------------------------------
    // PHASE 1: Lexical Analysis
    // ---------------------------------------------------------
    lexer = lexer_create(src, src_len, arena);
    if (!lexer) {
        fprintf(stderr, "Error: Failed to initialize lexer\n");
        exit_code = EXIT_LEX;
        goto cleanup;
    }

    double t0 = now_seconds();
    if (!lexer_lex_all(lexer)) {
        fprintf(stderr, "Error: Lexing failed\n");
        exit_code = EXIT_LEX;
        goto cleanup;
    }
    t_lex = now_seconds() - t0;
    mem_lex = arena_total_allocated(arena);

    // Optional: Print Tokens
    if (opts.print_tokens && lexer->tokens) {
        printf("--- Tokens ---\n");
        for (size_t i = 0; i < lexer->tokens->count; i++) {
            Token *tok = (Token*)dynarray_get(lexer->tokens, i);
            print_token(tok);
        }
        printf("\n");
    }

    // ---------------------------------------------------------
    // PHASE 2: Parsing
    // ---------------------------------------------------------
    parser = parser_create(lexer->tokens, filename_interned, arena);
    if (!parser) {
        fprintf(stderr, "Error: Failed to initialize parser\n");
        exit_code = EXIT_PARSE;
        goto cleanup;
    }

    ParseError parse_err = {0};
    double t1 = now_seconds();
    AstNode *program = parse_program(parser, &parse_err);
    double t2 = now_seconds();
    t_parse = t2 - t1;
    mem_parse = arena_total_allocated(arena) - mem_lex;

    if (parse_err.message) {
        print_parse_error(&parse_err);
        exit_code = EXIT_PARSE;
        goto cleanup;
    }

    if (!program) {
        // Empty program or non-fatal parse failure
        goto cleanup;
    }

    // ---------------------------------------------------------
    // PHASE 3: Semantic Analysis (Type Checking)
    // ---------------------------------------------------------
    size_t mem_before_sema = arena_total_allocated(arena);
    double t3 = now_seconds();

    // Create Type System
    TypeStore *store = typestore_create(arena, lexer->identifiers, lexer->keywords);
    TypeCheckContext type_ctx = typecheck_context_create(
        arena, 
        program, 
        store, 
        lexer->identifiers, 
        lexer->keywords, 
        filename_interned
    );

    // Run Semantic Passes
    typecheck_program(&type_ctx);
    
    double t4 = now_seconds();
    t_sema = t4 - t3;
    mem_sema = arena_total_allocated(arena) - mem_before_sema;

    // Check for Semantic Errors
    if (type_ctx.errors->count > 0) {
        for (size_t i = 0; i < type_ctx.errors->count; i++) {
            TypeError *e = (TypeError*)dynarray_get(type_ctx.errors, i);
            print_type_error(e); // Filename is already in context
        }
        exit_code = EXIT_TYPE;
        goto cleanup;
    }

    // ---------------------------------------------------------
    // Reporting & Output
    // ---------------------------------------------------------
    
    // 1. Print AST (Now populated with Types)
    if (opts.print_ast) {
        printf("--- AST ---\n");
        print_ast(program, 0, lexer->keywords, lexer->identifiers, lexer->strings);
        printf("\n");
    }

    // 2. Print Type Store Dump
    if (opts.print_types) {
        printf("--- Type Store ---\n");
        type_print_store_dump(store, program);
        printf("\n");
    }

    // 3. Print Metrics
    if (opts.print_time) {
        long peak_rss_after_kb = get_peak_rss_kb();
        size_t token_count = lexer->tokens ? lexer->tokens->count : 0;
        
        print_benchmark_stats(path,
                              src_len,
                              token_count,
                              t_lex,
                              t_parse,
                              t_sema,
                              mem_lex,
                              mem_parse,
                              mem_sema,
                              peak_rss_before_kb,
                              peak_rss_after_kb);
    }

cleanup:
    // Single cleanup point for resources
    if (parser) parser_free(parser);
    if (lexer) lexer_destroy(lexer);
    if (arena) arena_destroy(arena);
    // if (src) free(src); // Intentionally commented out to cause a leak

    return exit_code;
}