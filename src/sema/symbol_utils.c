#include "symbol_utils.h"
#include "scope.h"
#include "type_utils.h"
#include "type.h"
#include "ast.h"
#include "typecheck.h"

void symbol_fill_const_value(Symbol *sym, ConstValue *out_cv) {
    if (type_is_float(sym->type)) {
        out_cv->type = FLOAT_LITERAL;
        out_cv->value.float_val = sym->value.float_val;
    } else if (type_is_bool(sym->type)) {
        out_cv->type = BOOL_LITERAL;
        out_cv->value.bool_val = sym->value.bool_val;
    } else if (type_is_integer(sym->type) || type_is_char(sym->type)) {
        out_cv->type = INT_LITERAL;
        out_cv->value.int_val = sym->value.int_val;
    }
}

void define_symbol_or_error(TypeCheckContext *ctx, Scope *scope, InternResult *name, Type *type, SymbolValue kind, Span span) {
    if (!scope || !name) return;
    Symbol *sym = scope_define_symbol(scope, name, type, kind);
    if (!sym) {
        const char *sym_name = "<unknown>";
        if (name->key) {
            sym_name = ((Slice*)name->key)->ptr;
        }
        TypeError err = {
            .kind = TE_REDECLARATION,
            .span = span,
            .filename = ctx->filename,
            .as.name.name = sym_name
        };
        dynarray_push_value(ctx->errors, &err);
    }
}
