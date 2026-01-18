#pragma once
#include <stddef.h>

int read_line_from_file_shared(const char *filename, size_t line_no,
                               char *buf, size_t buf_size, size_t *out_len);

void print_source_excerpt_shared(const char *filename, size_t line_no, size_t col);
void print_source_excerpt_span(const char *filename, size_t line_no, size_t start_col, size_t end_col);
