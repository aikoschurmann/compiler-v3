//#pragma once
//
//#include <stddef.h>
//#include <stdbool.h>
//#include "arena.h"
//#include "dynamic_array.h"
//#include "dense_arena_interner.h"
//
//// Forward declarations
//typedef struct Scope Scope;
//typedef struct Symbol Symbol;
//
//// Symbol kinds for better type safety and debugging
//typedef enum {
//    SYMBOL_VALUE_INT,
//    SYMBOL_VALUE_FLOAT,
//    SYMBOL_VALUE_BOOL,
//    SYMBOL_VALUE_FUNCTION
//} SymbolValue;
//
//typedef enum {
//    SYMBOL_FLAG_NONE = 0,
//    SYMBOL_FLAG_CONST = 1 << 0,
//    SYMBOL_FLAG_USED = 1 << 2,
//    SYMBOL_FLAG_INITIALIZED = 1 << 3
//} SymbolFlags;
//
//typedef struct Type Type; // forward declaration
//
//
//typedef struct Symbol {
//    InternResult *name_rec;      // points to interned record (pointer, dense idx)
//    Type *type;
//    SymbolValue kind;
//    SymbolFlags flags;
//    Span span;
//
//    // Optional constant value (for compile-time constants)
//    union {
//        int int_val;
//        float float_val;
//        bool bool_val;
//    } value;
//    
//} Symbol;
//
//typedef struct Scope {
//    // array of symbols
//    Symbol **symbols;
//    size_t symbol_count;
//
//    Scope *parent;
//    Arena *arena;                // Arena for memory allocation
//    
//    // Scope metadata
//    size_t depth;                // Nesting depth (0 = global)
//    
//
//} Scope;
//
//// Scope management functions
//Scope *scope_create(Arena *arena, Scope *parent, int identifier_count);
//
//// Symbol management
//Symbol *scope_define_symbol(Scope *scope, InternResult *name, Type *type, SymbolValue  kind);
//Symbol *scope_lookup_symbol(Scope *scope, InternResult *name);
//Symbol *scope_lookup_symbol_local(Scope *scope, InternResult *name);
//
//// Symbol modification
//Symbol *symbol_set_value_int(Symbol *symbol, int value);
//Symbol *symbol_set_value_float(Symbol *symbol, float value);
//Symbol *symbol_set_value_bool(Symbol *symbol, bool value);
//
//
//// Scope utilities
//size_t scope_get_symbol_count(Scope *scope);
//void scope_set_flags(Scope *scope, InternResult *rec, int flags);
//void scope_check_unused_symbols(Scope *scope);
//
//// Debugging and introspection
//void scope_print_symbols(Scope *scope, int indent);
//void scope_print_hierarchy(Scope *scope);

