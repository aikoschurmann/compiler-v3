#pragma once
#include "scope.h"
#include "type.h"
#include "ast.h"
#include "typecheck.h"

void symbol_fill_const_value(Symbol *sym, ConstValue *out_cv);
void define_symbol_or_error(TypeCheckContext *ctx, Scope *scope, InternResult *name, Type *type, SymbolValue kind, Span span);
