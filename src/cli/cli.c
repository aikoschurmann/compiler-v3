#include <stdio.h>
#include <string.h>
#include "cli.h"

int parse_options(int argc, char **argv, Options *opts, const char **out_path) {
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

void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s <file> [options]\n", prog);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -t, --tokens    Print all tokens\n");
    fprintf(stderr, "  -a, --ast       Print the parsed AST (after parsing)\n");
    fprintf(stderr, "  -y, --types     Print type internment results\n");
    fprintf(stderr, "  -T, --time      Print lex/parse timing and throughput\n");
    fprintf(stderr, "  -h, --help      Show this help\n");
    fprintf(stderr, "  -v, --version   Print version and exit\n");
}

void print_version(void) {
    printf("Lexer+Parser Benchmark CLI v1.2\n");
}
