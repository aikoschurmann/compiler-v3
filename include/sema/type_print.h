#pragma once

#include "type.h"

#include <stdio.h> // for FILE*

typedef struct AstNode AstNode;

/**
 * @brief Print a human-readable signature for a type (e.g., "(i32, i32) -> void")
 */
void type_print_signature(const Type *type);

/**
 * @brief Recursive printer helper that can write to a specific file or stdout.
 */
void type_print(FILE *f, const Type *type);

/**
 * @brief Diagnostic dump: prints all interned types and function symbol mappings.
 *        Useful for debugging compiler internals.
 * 
 * @param store The TypeStore containing all interned types.
 * @param program Optional AST program root to inspect function symbols (pass NULL if unavailable).
 */
void type_print_store_dump(TypeStore *store, AstNode *program);
