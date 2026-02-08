#pragma once

#include "parsing/ast.h"
#include "arena.h"
#include <stddef.h>

typedef struct {
    double time_tokenize_ms;
    double time_parse_ms;
    double time_sema_ms;
    
    size_t mem_lex_bytes;
    size_t mem_parse_bytes;
    size_t mem_sema_bytes;
    size_t rss_delta_bytes;
    
    size_t token_count;
    size_t file_size_bytes;
    const char *filename;
} CompilationStats;

// Traverses the AST to count total nodes
size_t count_ast_nodes(AstNode *program);

// Prints the formatted table report
void print_compilation_report(CompilationStats *stats, AstNode *program);