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
#include "scope.h"

#include "cli.h"
#include "metrics.h"
#include "type_print.h"
#include "type_report.h"

#define EXIT_USAGE 1
#define EXIT_IO    2
#define EXIT_LEX   3
#define EXIT_PARSE 4
#define EXIT_TYPE  5
#define EXIT_SCOPE 6

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


    // print promotion matrix for debugging
    //for (int i = 0; i < NUM_TYPE_KINDS; i++) {
    //    for (int j = 0; j < NUM_TYPE_KINDS; j++) {
    //        printf("%2d ", promotion_matrix[i][j]);
    //    }
    //    printf("\n");
    //}

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
