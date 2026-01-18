#pragma once

#include "type.h"
#include "ast.h"
#include "type_report.h"
#include "scope.h"

// Context for type checking pass
typedef struct {
    AstNode *program; // Root AST node
    TypeStore *store;
    DenseArenaInterner *identifiers; // Need for looking up things, etc?
    DenseArenaInterner *keywords;
    const char *filename;
    
    // We can add an error list here
    DynArray *errors; // Array of TypeError
} TypeCheckContext;


TypeCheckContext typecheck_context_create(Arena *arena, AstNode *program, TypeStore *store, DenseArenaInterner *identifiers, DenseArenaInterner *keywords, const char *filename);

// Resolves an AST_TYPE node into a semantic Type*
// Returns NULL on failure.
Type *resolve_ast_type(TypeStore *store, Scope *scope, AstNode *node);

// Full Typecheck
void typecheck_program(TypeCheckContext *ctx);



