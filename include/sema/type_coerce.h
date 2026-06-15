#pragma once
#include "type.h"
#include "typecheck.h"
#include <stdbool.h>

/**
 * Checks if 'source' can be implicitly promoted/decayed to 'target'
 * based on the language's coercion rules (e.g. widening, array-to-slice).
 */
bool type_can_implicit_cast(Type *target, Type *source);

/**
 * Checks if 'source' can be explicitly cast to 'target' via 'as' operator.
 * This is a superset of implicit casts, allowing narrowing and bitcasts.
 */
bool type_can_explicit_cast(Type *target, Type *source);

/**
 * Inserts an AST_CAST node into the tree, wrapping 'node'.
 * Returns the same pointer to 'node' but with its internals transformed into a cast.
 */
void insert_cast(TypeCheckContext *ctx, AstNode *node, Type *to_type);

/**
 * Attempts to coerce 'node' to 'expected' type.
 * If possible, it calls insert_cast and returns the expected type.
 * If impossible, it logs a TE_TYPE_MISMATCH error and returns NULL.
 */
Type* coerce_or_error(TypeCheckContext *ctx, AstNode *node, Type *expected);

/**
 * Performs constant-folding for a cast node.
 * Should be called whenever a cast (implicit or explicit) is created or modified.
 */
void fold_cast_node(AstNode *cast_node);
