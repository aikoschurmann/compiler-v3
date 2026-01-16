#pragma once

#include "type.h"
#include "ast.h"
#include "type_report.h"
#include "scope.h"

// Resolves an AST_TYPE node into a semantic Type*
// Returns NULL on failure.
Type *resolve_ast_type(TypeStore *store, Scope *scope, AstNode *node);

// Traverses the AST program and resolves types for all function declarations.
// Populates the 'type' field of the AST nodes.
void resolve_program_functions(TypeStore *store, AstProgram *program, DenseArenaInterner *identifiers, DenseArenaInterner *keywords);


