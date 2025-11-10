#include <stdio.h>
#include <time.h>
#include <math.h>
#include "metrics.h"

/* ANSI color codes */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"

static void print_progress_bar(double value, double max_value, int width) {
    if (max_value <= 0) max_value = 1.0;
    int filled = (int)(((value / max_value) * width) + 0.5);
    if (filled > width) filled = width;
    for (int i = 0; i < filled; i++) printf("█");
    printf(DIM);
    for (int i = filled; i < width; i++) printf("░");
    printf(RESET);
}

void human_readable_bytes(size_t bytes, char *out, size_t out_len) {
    double kb = (double)bytes / 1024.0;
    double mb = kb / 1024.0;
    if (bytes >= (1u << 20)) snprintf(out, out_len, "%.2f MB", mb);
    else if (bytes >= 1024) snprintf(out, out_len, "%.2f KB", kb);
    else snprintf(out, out_len, "%zu B", bytes);
}

void human_readable_time(double seconds, char *out, size_t out_len) {
    snprintf(out, out_len, "%.3f ms", seconds * 1e3);
}

static void print_box_line(const char *left, int width) {
    printf("%s", left);
    for (int i = 0; i < width - 2; i++) printf("─");
    printf("\n");
}

void print_benchmark_stats(const char *filename,
                           size_t file_size,
                           size_t token_count,
                           double tokenization_time,
                           double parsing_time,
                           size_t arena_used_lex,
                           size_t arena_used_parse,
                           long peak_rss_before_kb,
                           long peak_rss_after_kb) {
    double type_inference_time = 0.0;
    double total_time = tokenization_time + parsing_time + type_inference_time;
    size_t arena_total_allocated = arena_used_lex + arena_used_parse;
    size_t rss_total = (peak_rss_after_kb - peak_rss_before_kb) * 1024;
    size_t tokens_second = tokenization_time > 0 ? (size_t)(token_count / tokenization_time) : 0;

    double max_time = fmax(fmax(tokenization_time, parsing_time), type_inference_time);
    if (max_time <= 0) max_time = total_time;

    char arena_size_str[32], rss_str[32];
    human_readable_bytes(arena_total_allocated, arena_size_str, sizeof(arena_size_str));
    human_readable_bytes(rss_total, rss_str, sizeof(rss_str));

    printf("\n┌─────────────────────────────────────────────────────────────────────┐\n");
    printf("│" BOLD "                          COMPILATION REPORT                         " RESET "│\n");
    printf("└─────────────────────────────────────────────────────────────────────┘\n\n");

    printf("File: %s (%zu bytes)\n\n", filename, file_size);

    printf(BOLD "PERFORMANCE METRICS\n" RESET);
    printf("┌─────────────────┬──────────┬──────────────────┬────────────┬────────────┐\n");
    printf("│ %-15s │ %-8s │ %-16s │ %-10s │ %-10s │\n", "Phase", "Time", "Distribution", "Percentage", "ns/Token");
    printf("├─────────────────┼──────────┼──────────────────┼────────────┼────────────┤\n");

    char tokenization_str[32], parsing_str[32], inference_str[32], total_str[32];
    human_readable_time(tokenization_time, tokenization_str, sizeof(tokenization_str));
    human_readable_time(parsing_time, parsing_str, sizeof(parsing_str));
    human_readable_time(type_inference_time, inference_str, sizeof(inference_str));
    human_readable_time(total_time, total_str, sizeof(total_str));

    double tokenization_ns_per_token = token_count > 0 ? (tokenization_time * 1e9) / token_count : 0.0;
    printf("│ %-15s │ %8s │ ", "Tokenization", tokenization_str);
    print_progress_bar(tokenization_time, total_time, 16);
    printf(" │ %9.1f%% │ %9.1f  │\n", (tokenization_time / total_time) * 100, tokenization_ns_per_token);

    double parsing_ns_per_token = token_count > 0 ? (parsing_time * 1e9) / token_count : 0.0;
    printf("│ %-15s │ %8s │ ", "Parsing", parsing_str);
    print_progress_bar(parsing_time, total_time, 16);
    printf(" │ %9.1f%% │ %9.1f  │\n", (parsing_time / total_time) * 100, parsing_ns_per_token);

    printf("└─────────────────┴──────────┴──────────────────┴────────────┴────────────┘\n");
    printf("\n");

    printf(BOLD "MEMORY USAGE\n" RESET);
    printf("┌──────────────────────┬─────────────┬──────────────┐\n");
    printf("│ %-20s │ %-11s │ %-12s │\n", "Metric", "Value", "Bytes/Token");
    printf("├──────────────────────┼─────────────┼──────────────┤\n");

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

    printf(BOLD "SUMMARY\n" RESET);
    printf("  Total Time: %s\n", total_str);
    printf("  Tokens: %zu\n", token_count);
    printf("  AST Nodes: 0 (not counted yet)\n");

    double throughput_mbps = file_size / (1024.0 * 1024.0) / total_time;
    printf("  Throughput: %.2f MB/s (tokens/sec: %zu)\n", throughput_mbps, tokens_second);
    printf("\n");
}

#ifdef __APPLE__
#include <sys/resource.h>
long get_peak_rss_kb(void) {
    struct rusage ru; if (getrusage(RUSAGE_SELF, &ru) != 0) return -1; return (long)(ru.ru_maxrss / 1024);
}

#else
long get_peak_rss_kb(void) {
    return -1; // Not implemented on this platform
}
#endif

double now_seconds(void) {
    struct timespec ts; clock_gettime(CLOCK_MONOTONIC, &ts); return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
