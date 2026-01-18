#pragma once
#include "test_harness.h"
#include "lexer.h"
#include "parser.h"
#include "parse_statements.h"
#include "ast.h"
#include "arena.h"
#include "scope.h"
#include "type.h"
#include "typecheck.h"
#include "file.h"

// Helper struct to hold compilation results
typedef struct {
    Arena *arena;
    Lexer *lexer;
    Parser *parser;
    AstNode *program;
    TypeStore *store;
    TypeCheckContext ctx;
    bool parse_failed;
} CompileResult;

CompileResult compile_source(const char *src);
void cleanup_compilation(CompileResult *res);
