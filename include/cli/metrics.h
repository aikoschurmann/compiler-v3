#pragma once
#include <stddef.h>

void human_readable_bytes(size_t bytes, char *out, size_t out_len);
void human_readable_time(double seconds, char *out, size_t out_len);
void print_benchmark_stats(const char *filename,
                           size_t file_size,
                           size_t token_count,
                           double tokenization_time,
                           double parsing_time,
                           double semantics_time,
                           size_t arena_used_lex,
                           size_t arena_used_parse,
                           size_t arena_used_sema,
                           long peak_rss_before_kb,
                           long peak_rss_after_kb);

double now_seconds(void);
long get_peak_rss_kb(void);
