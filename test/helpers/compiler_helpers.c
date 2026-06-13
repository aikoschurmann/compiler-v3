#include "compiler_helpers.h"
#include "../harness/test_harness.h"
#include <string.h>
#include <stdio.h>

TestCompileResult test_compile_source(const char *src) {
    TestCompileResult res = {0};
    res.arena = arena_create(2 * 1024 * 1024); // 2MB
    
    // 1. Interners
    DenseArenaInterner *keywords = intern_table_create(hashmap_create(32), res.arena, string_copy_func, slice_hash, slice_cmp);
    DenseArenaInterner *identifiers = intern_table_create(hashmap_create(128), res.arena, string_copy_func, slice_hash, slice_cmp);
    DenseArenaInterner *strings = intern_table_create(hashmap_create(64), res.arena, string_copy_func, slice_hash, slice_cmp);
    
    lexer_populate_default_keywords(keywords);

    // 2. Lex
    res.lexer = lexer_create_ex(src, strlen(src), res.arena, keywords, identifiers, strings);
    if (!lexer_lex_all(res.lexer)) {
        res.failed = true;
        return res;
    }

    // 3. Parse
    res.parser = parser_create(res.lexer->tokens, "<test>", res.arena);
    ParseError p_err = {0};
    res.program = parse_program(res.parser, &p_err);
    if (p_err.message) {
        res.failed = true;
        return res;
    }

    // 4. Sema
    res.store = typestore_create(res.arena, identifiers, keywords);
    res.sema_ctx = typecheck_context_create(res.arena, res.program, res.store, identifiers, keywords, "<test>");
    typecheck_program(&res.sema_ctx);
    
    if (res.sema_ctx.errors->count > 0) {
        res.failed = true;
    }

    return res;
}

void test_cleanup_compilation(TestCompileResult *res) {
    if (res->arena) arena_destroy(res->arena);
    // Lexer and other objects are in the arena
}

bool test_is_lex_valid(const char *src) {
    Arena *arena = arena_create(64 * 1024);
    Lexer *l = lexer_create(src, strlen(src), arena);
    bool ok = lexer_lex_all(l);
    arena_destroy(arena);
    return ok;
}

bool test_is_parse_valid(const char *src) {
    TestCompileResult res = test_compile_source(src);
    bool ok = (res.program != NULL && !res.failed); // This is a bit coarse but works for now
    // Actually, test_compile_source checks sema too. 
    // Let's refine:
    TestCompileResult res2 = {0};
    res2.arena = arena_create(1024 * 1024);
    res2.lexer = lexer_create(src, strlen(src), res2.arena);
    lexer_lex_all(res2.lexer);
    res2.parser = parser_create(res2.lexer->tokens, "<test>", res2.arena);
    ParseError p_err = {0};
    res2.program = parse_program(res2.parser, &p_err);
    ok = (p_err.message == NULL);
    test_cleanup_compilation(&res2);
    return ok;
}

bool test_is_sema_valid(const char *src) {
    TestCompileResult res = test_compile_source(src);
    bool ok = !res.failed;
    if (!ok) {
        test_log("\n      %s[Sema Validation Failed]%s\n", COL_RED, COL_RESET);
        test_log("      Source: %s\n", src);
        if (res.sema_ctx.errors) {
            for (size_t i = 0; i < res.sema_ctx.errors->count; i++) {
                TypeError *err = (TypeError*)dynarray_get(res.sema_ctx.errors, i);
                // We need to capture the output of print_type_error
                // For now, let's just log the kind. 
                // A better fix would be to make print_type_error take a FILE* or buffer.
                test_log("      Error %zu: Type Error Kind %d\n", i + 1, err->kind);
            }
        }
    }
    test_cleanup_compilation(&res);
    return ok;
}

bool test_check_sema_error(const char *src, TypeErrorKind kind) {
    TestCompileResult res = test_compile_source(src);
    bool found = false;
    if (res.sema_ctx.errors) {
        for (size_t i = 0; i < res.sema_ctx.errors->count; i++) {
            TypeError *err = (TypeError*)dynarray_get(res.sema_ctx.errors, i);
            if (err->kind == kind) {
                found = true;
                break;
            }
        }
    }
    test_cleanup_compilation(&res);
    return found;
}

int test_run_and_get_exit_code(const char *src) {
    TestCompileResult res = test_compile_source(src);
    if (res.failed) {
        test_cleanup_compilation(&res);
        return -100; // Compilation failed
    }
    
    CodegenContext *cg_ctx = codegen_context_create(res.program, res.store, "test_jit", 0);
    if (codegen_program(cg_ctx) != 0) {
        codegen_context_destroy(cg_ctx);
        test_cleanup_compilation(&res);
        return -101; // Codegen failed
    }

    int exit_code = codegen_run_jit(cg_ctx);

    codegen_context_destroy(cg_ctx);
    test_cleanup_compilation(&res);
    return exit_code;
}
