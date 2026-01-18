#pragma once

#include "type.h"
#include "token.h" // For Span and potentially TokenKind
#include "ast.h"   // For Expr or Stmt if needed

typedef enum {
    TE_NONE = 0,
    
    // Simple errors
    TE_UNKNOWN_TYPE,       // "Unknown type 'foo'"
    TE_REDECLARATION,      // "Symbol 'x' already defined"
    TE_UNDECLARED,         // "Use of undeclared identifier 'x'"
    
    // Type mismatch errors
    TE_TYPE_MISMATCH,      // "Expected 'i32', found 'bool'"
    TE_RETURN_MISMATCH,    // "Function declared to return 'i32' but returns 'void'"
    TE_VARIABLE_TYPE_RESOLUTION_FAILED, // "Failed to resolve variable type"
    
    // Operator errors
    TE_BINOP_MISMATCH,     // "Invalid operands for '+': 'i32' and 'str'"
    TE_UNOP_MISMATCH,      // "Invalid operand for '!': 'i32' (expected bool)"
    
    // Structure/Array errors
    TE_NOT_CALLABLE,       // "Type 'i32' is not callable"
    TE_NOT_INDEXABLE,      // "Type 'bool' is not an array or pointer"
    TE_FIELD_ACCESS,       // "Type 'Point' has no field named 'z'"
    
    TE_CONST_ASSIGN,       // "Cannot assign to constant 'x'"
    TE_ARG_COUNT_MISMATCH  // "Expected 3 arguments, found 2"
} TypeErrorKind;

typedef struct {
    TypeErrorKind kind;
    Span span;             // Where in the source code?
    const char *filename;  // Which file?
    
    // Specific details for each error type
    union {
        // TE_UNKNOWN_TYPE, TE_UNDECLARED, TE_REDECLARATION, TE_FIELD_ACCESS, TE_VARIABLE_TYPE_RESOLUTION_FAILED
        struct {
            const char *name; // The identifier name
        } name;

        // TE_TYPE_MISMATCH, TE_RETURN_MISMATCH, TE_CONST_ASSIGN
        struct {
            Type *expected;
            Type *actual;
        } mismatch;

        // TE_BINOP_MISMATCH
        struct {
            OpKind op;      // '+', '-', etc.
            Type *left;
            Type *right;
        } binop;

        // TE_UNOP_MISMATCH
        struct {
            OpKind op;      // '!', '-', etc.
            Type *operand;
        } unop;
        
        // TE_NOT_CALLABLE, TE_NOT_INDEXABLE
        struct {
            Type *actual;
        } bad_usage;

        // TE_ARG_COUNT_MISMATCH
        struct {
            size_t expected;
            size_t actual;
        } arg_count;

    } as;
} TypeError;

// -- API --

void print_type_error(TypeError *err);
