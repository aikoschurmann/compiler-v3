#include "scope.h"
#include <stdio.h>
#include <string.h>

Scope *scope_create(Arena *arena, Scope *parent, int identifier_count) {
    Scope *scope = arena_calloc(arena, sizeof(Scope));
    if (!scope) return NULL;

    scope->symbols = arena_calloc(arena, sizeof(Symbol *) * identifier_count);
    if (!scope->symbols) {
        return NULL;
    }

    scope->depth = parent ? parent->depth + 1 : 0;
    scope->arena = arena;  // Set the arena field

    return scope;
}

Symbol *scope_define_symbol(Scope *scope, InternResult *rec, Type *type, SymbolValue kind) {
    if (!scope || !rec || !type) {
        return NULL;
    }

    // Check for existing symbol in current scope
    if (scope_lookup_symbol_local(scope, rec)) {
        // Symbol already defined in this scope
        return NULL;
    }

    Symbol *symbol = arena_calloc(scope->arena, sizeof(Symbol));
    if (!symbol) {
        return NULL;
    }

    symbol->name_rec = rec;
    symbol->type = type;
    symbol->kind = kind;
    symbol->flags = SYMBOL_FLAG_NONE;

    scope->symbols[rec->entry->dense_index] = symbol;
    scope->symbol_count++;
    
    return symbol;
}

Symbol *scope_lookup_symbol_local(Scope *scope, InternResult *rec) {
    if (!scope || !rec) return NULL;
    return scope->symbols[rec->entry->dense_index];
}

Symbol *scope_lookup_symbol(Scope *scope, InternResult *rec) {
    if (!scope || !rec) return NULL;

    Scope *current = scope;
    while (current) {
        Symbol *symbol = scope_lookup_symbol_local(current, rec);
        if (symbol) return symbol;
        current = current->parent;
    }
    return NULL;
}

Symbol *symbol_set_value_int(Symbol *symbol, int value){
    if (!symbol) return NULL;
    symbol->kind = SYMBOL_VALUE_INT;
    symbol->value.int_val = value;
    return symbol;
}
Symbol *symbol_set_value_float(Symbol *symbol, float value){
    if (!symbol) return NULL;
    symbol->kind = SYMBOL_VALUE_FLOAT;
    symbol->value.float_val = value;
    return symbol;
}
Symbol *symbol_set_value_bool(Symbol *symbol, bool value){
    if (!symbol) return NULL;
    symbol->kind = SYMBOL_VALUE_BOOL;
    symbol->value.bool_val = value;
    return symbol;
}

size_t scope_get_symbol_count(Scope *scope){
    if (!scope) return 0;
    return scope->symbol_count;
}

void scope_set_flags(Scope *scope, InternResult *rec, int flags){
    if (!scope || !rec) return;

    Symbol *symbol = scope_lookup_symbol(scope, rec);
    if (symbol) {
        symbol->flags |= flags;
    }
}

void scope_check_unused_symbols(Scope *scope){
    if (!scope) return;

    for (size_t i = 0; i < scope->symbol_count; i++) {
        Symbol *symbol = scope->symbols[i];
        if (symbol && !(symbol->flags & SYMBOL_FLAG_USED)) {
            printf("Warning: Unused symbol '%s'\n", symbol->name_rec->key ? (char*)symbol->name_rec->key : "(unknown)");
        }
    }
}

void scope_print_symbols(Scope *scope, int indent) {
    if (!scope) return;

    for (size_t i = 0; i < scope->symbol_count; ++i) {
        Symbol *s = scope->symbols[i];
        if (!s) continue;
        const char *name = s->name_rec && s->name_rec->key ? (char*)s->name_rec->key : "(unknown)";
        const char *type_name = s->type ? type_kind_to_string(s->type->kind) : "(none)";
        printf("%*s- Symbol: '%s', type: %s, flags: 0x%02x\n", indent, "", name, type_name, (unsigned)s->flags);
    }
}

void scope_print_hierarchy(Scope *scope) {
    if (!scope) return;

    int indent = 0;
    Scope *cur = scope;
    while (cur) {
        printf("%*s- Scope (depth %zu):\n", indent, "", cur->depth);
        scope_print_symbols(cur, indent + 2);
        cur = cur->parent;
        indent += 2;
    }
}