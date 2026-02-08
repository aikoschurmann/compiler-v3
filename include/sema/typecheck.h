#pragma once

#include "parsing/ast.h"
#include "datastructures/scope.h"
#include "datastructures/arena.h"
#include "datastructures/dense_arena_interner.h"
#include "sema/type.h"
#include "sema/type_report.h" 

typedef struct {
    AstNode *program;
    TypeStore *store;
    DenseArenaInterner *identifiers;
    DenseArenaInterner *keywords;
    const char *filename;
    DynArray *errors; // DynArray<TypeError>
} TypeCheckContext;

// Context creation
TypeCheckContext typecheck_context_create(Arena *arena, AstNode *program, TypeStore *store, DenseArenaInterner *identifiers, DenseArenaInterner *keywords, const char *filename);

// Main Entry Point
void typecheck_program(TypeCheckContext *ctx);

// AST -> Type resolution (Updated to take Context)
Type *resolve_ast_type(TypeCheckContext *ctx, Scope *scope, AstNode *node);

void resolve_program_functions(TypeCheckContext *ctx, Scope *global_scope);
void check_variable_declaration(TypeCheckContext *ctx, Scope *scope, AstNode *var_node);