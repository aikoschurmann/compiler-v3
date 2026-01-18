#include "test_utils.h"
#include <string.h>

CompileResult compile_source(const char *src) {
    CompileResult res = {0};
    res.arena = arena_create(1024 * 1024);
    
    char *filename = arena_alloc(res.arena, 16);
    strcpy(filename, "<test>");

    // LEXER
    res.lexer = lexer_create(src, strlen(src), res.arena);
    if (!res.lexer || !lexer_lex_all(res.lexer)) {
        res.parse_failed = true;
        return res;
    }

    // PARSER
    res.parser = parser_create(res.lexer->tokens, filename, res.arena);
    ParseError err = {0};
    res.program = parse_program(res.parser, &err);
    
    if (err.message) {
        fprintf(stderr, "Parse Error in compile_source: %s\n", err.message);
        res.parse_failed = true;
        return res;
    }

    // SEMA
    if (res.program) {
        res.store = typestore_create(res.arena, res.lexer->identifiers, res.lexer->keywords);
        res.ctx = typecheck_context_create(res.arena, res.program, res.store, res.lexer->identifiers, res.lexer->keywords, filename);
        typecheck_program(&res.ctx);
    }

    return res;
}

void cleanup_compilation(CompileResult *res) {
    if (res->lexer) lexer_destroy(res->lexer);
    if (res->arena) arena_destroy(res->arena);
}
