#pragma once

#include <stdio.h>
#include <stdlib.h>


char *read_file(const char *filename);
void free_file_content(char *content);

int read_line_from_file(const char *filename, size_t line_no,
                        char *buf, size_t buf_size, size_t *out_len);
void print_source_excerpt(const char *filename, size_t line_no, size_t col);
void print_source_excerpt_span(const char *filename, size_t line_no, size_t start_col, size_t end_col);
