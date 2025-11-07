#pragma once
#include <stddef.h>

typedef struct {
    int print_tokens;
    int print_ast;
    int print_time;
    int print_types;
} Options;

int parse_options(int argc, char **argv, Options *opts, const char **out_path);
void print_usage(const char *prog);
void print_version(void);
