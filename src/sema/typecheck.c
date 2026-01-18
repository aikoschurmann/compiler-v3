#include "typecheck.h"
#include "utils.h" 
#include "dynamic_array.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



TypeCheckContext typecheck_context_create(Arena *arena, AstNode *program, TypeStore *store, DenseArenaInterner *identifiers, DenseArenaInterner *keywords, const char *filename) {
    DynArray *errors = arena_alloc(arena, sizeof(DynArray));
    dynarray_init_in_arena(errors, arena, sizeof(TypeError), 8);

    TypeCheckContext ctx = {
        .program = program,
        .store = store,
        .identifiers = identifiers,
        .keywords = keywords,
        .filename = filename,
        .errors = errors
    };
    return ctx;
}

static void define_symbol_or_error(TypeCheckContext *ctx, Scope *scope, InternResult *name, Type *type, SymbolValue kind, Span span) {
    if (!scope || !name) return;

    Symbol *sym = scope_define_symbol(scope, name, type, kind);
    
    if (!sym) {
        // Symbol already exists! Report error.
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

#ifdef _MSC_VER
#include <malloc.h>
#define ALLOCA _alloca
#else
#include <alloca.h>
#define ALLOCA alloca
#endif

#define FAST_GET(arr, i) (((AstNode**)(arr)->data)[i])

Type *resolve_ast_type(TypeStore *store, Scope *scope, AstNode *node) {
    if (!store || !node) return NULL;
    
    if (node->node_type != AST_TYPE) {
        return NULL;
    }

    AstType *ast_ty = &node->data.ast_type;

    switch (ast_ty->kind) {
        case AST_TYPE_PRIMITIVE: {
            InternResult *name_res = ast_ty->u.base.intern_result;
            
            if (name_res && name_res->key) {
                 // 1. Primitive Registry (Fastest)
                Type *prim = (Type*)hashmap_get(store->primitive_registry, name_res->key, ptr_hash, ptr_cmp);
                if (prim) return prim;

                // 2. User Scope (Slower)
                if (scope) {
                    Symbol *sym = scope_lookup_symbol(scope, name_res);
                    if (sym && sym->kind == SYMBOL_VALUE_TYPE) return sym->type;
                }
            }
            return NULL; 
        }

        case AST_TYPE_PTR: {
            Type *target = resolve_ast_type(store, scope, ast_ty->u.ptr.target);
            if (!target) return NULL;

            Type proto = { .kind = TYPE_POINTER, .as.ptr.base = target };
            // Note: intern_type handles the pointer hashing logic
            InternResult *res = intern_type(store, &proto);
            return res ? (Type*)((Slice*)res->key)->ptr : NULL;
        }

        case AST_TYPE_ARRAY: {
            Type *elem = resolve_ast_type(store, scope, ast_ty->u.array.elem);
            if (!elem) return NULL;

            int64_t size = 0;
            bool size_known = false;
            
            AstNode *sz = ast_ty->u.array.size_expr;
            if (sz) {
                // Inline check for common literal case
                if (sz->node_type == AST_LITERAL && sz->data.literal.type == INT_LITERAL) {
                    size = sz->data.literal.value.int_val;
                    size_known = true;
                } else if (sz->is_const_expr && sz->data.literal.type == INT_LITERAL) {
                     size = sz->data.literal.value.int_val;
                     size_known = true;
                }
                if (!size_known) return NULL;
            }

            Type proto = { 
                .kind = TYPE_ARRAY, 
                .as.array.base = elem, 
                .as.array.size = size, 
                .as.array.size_known = size_known 
            };

            InternResult *res = intern_type(store, &proto);
            return res ? (Type*)((Slice*)res->key)->ptr : NULL;
        }

        case AST_TYPE_FUNC: {
             Type *ret = resolve_ast_type(store, scope, ast_ty->u.func.return_type);
             if (!ret) return NULL;
             
             DynArray *params = ast_ty->u.func.param_types;
             size_t count = params ? params->count : 0;
             
             Type **param_types = NULL;
             if (count > 0) {
                 // OPTIMIZATION: Use Stack Allocation for small params (99% of cases)
                 // Avoids malloc/free overhead completely.
                 if (count <= 64) {
                     param_types = ALLOCA(sizeof(Type*) * count);
                 } else {
                     param_types = malloc(sizeof(Type*) * count);
                 }
             }
             
             // OPTIMIZATION: Raw array access loop
             for (size_t i = 0; i < count; i++) {
                 AstNode *p_node = FAST_GET(params, i);
                 Type *pt = resolve_ast_type(store, scope, p_node);
                 if (!pt) {
                     if (count > 64) free(param_types);
                     return NULL;
                 }
                 param_types[i] = pt;
             }
             
             Type proto = {
                 .kind = TYPE_FUNCTION,
                 .as.func.return_type = ret,
                 .as.func.param_count = count,
                 .as.func.params = param_types
             };
             
             InternResult *res = intern_type(store, &proto);
             
             if (count > 64) free(param_types);
             
             return res ? (Type*)((Slice*)res->key)->ptr : NULL;
        }
    }
    return NULL;
}

/*
 * Resolves the full type signature of a function declaration.
 * 
 * Unlike resolving a bare function pointer type, this must also:
 * 1. Resolve the return type.
 * 2. Iterate through named parameters, resolving their individual types.
 * 3. Update the AstParam nodes with the resolved types (for later variable declaration phases).
 * 4. Intern the complete function signature type.
 */
static void resolve_function_decl(TypeStore *store, Scope *scope, AstNode *func_node) {
    if (func_node->node_type != AST_FUNCTION_DECLARATION) return;
    
    AstFunctionDeclaration *decl = &func_node->data.function_declaration;


    Type *ret_type = resolve_ast_type(store, scope, decl->return_type);

    if (!ret_type) {
        ret_type = store->t_void; 
    }

    size_t param_count = decl->params ? decl->params->count : 0;
    Type **param_types = NULL;
    
    if (param_count > 0) {
        param_types = malloc(sizeof(Type*) * param_count);
    }

    for (size_t i = 0; i < param_count; i++) {
        AstNode *param_node = *(AstNode**)dynarray_get(decl->params, i);
        AstNode *type_ast = param_node->data.param.type;
        
        Type *pt = resolve_ast_type(store, scope, type_ast);
        if (!pt) {
            pt = store->t_void; 
        }
        param_types[i] = pt;
        param_node->type = pt;
    }

    Type proto = {0};
    proto.kind = TYPE_FUNCTION;
    proto.as.func.return_type = ret_type;
    proto.as.func.param_count = param_count;
    proto.as.func.params = param_types;
    InternResult *res = intern_type(store, &proto);
    if (res) {
        func_node->type = (Type*)((Slice*)res->key)->ptr;
    }

    free(param_types);
}

/*
 * First pass of semantic analysis: Type Resolution.
 * Initializes the scope hierarchy (Global) and resolves types for all
 * top-level declarations (Functions, Variables).
 *
 * Does NOT check function bodies yet; only signatures and global variable types.
 */
void resolve_program_functions(TypeCheckContext *ctx, Scope *global_scope) {
    if (!ctx || !ctx->program) return;
    AstProgram *program = &ctx->program->data.program;
    TypeStore *store = ctx->store;

    if (!program->decls) return;


    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl) continue;

        if (decl->node_type == AST_FUNCTION_DECLARATION) {
             resolve_function_decl(store, global_scope, decl);

             // Define function symbol in global scope
             AstFunctionDeclaration *func = &decl->data.function_declaration;
             if (func->intern_result && decl->type) {
                 define_symbol_or_error(ctx, global_scope, func->intern_result, decl->type, SYMBOL_VALUE_FUNCTION, decl->span);
             }
        }

    }
}


static Type* check_expression(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    if (!expr) return NULL;
    
    Type *result_type = NULL;

    switch (expr->node_type) {
        case AST_LITERAL: {
            LiteralType lit_kind = expr->data.literal.type;
            if (lit_kind == INT_LITERAL) {
                if (expected_type == ctx->store->t_i64) result_type = ctx->store->t_i64;
                else result_type = ctx->store->t_i32;
            } 
            else if (lit_kind == FLOAT_LITERAL) {
                if (expected_type == ctx->store->t_f32) result_type = ctx->store->t_f32;
                else result_type = ctx->store->t_f64;
            } 
            else if (lit_kind == BOOL_LITERAL)   result_type = ctx->store->t_bool;
            else if (lit_kind == CHAR_LITERAL)   result_type = ctx->store->t_char;
            else if (lit_kind == STRING_LITERAL) result_type = ctx->store->t_str;
            break;
        }

        case AST_IDENTIFIER: {
            AstIdentifier *ident = &expr->data.identifier;
            InternResult *name_res = ident->intern_result;
            Symbol *sym = scope_lookup_symbol(scope, name_res);
            
            if (!sym) {
                TypeError err = {
                    .kind = TE_UNDECLARED,
                    .span = expr->span,
                    .filename = ctx->filename,
                    .as.name.name = name_res && name_res->key ? ((Slice*)name_res->key)->ptr : "<unknown>"
                };
                dynarray_push_value(ctx->errors, &err);
                return NULL;
            }
            result_type = sym->type;
            break;
        }
        
        
        case AST_CALL_EXPR: {
            AstCallExpr *call = &expr->data.call_expr;
            Type *callee_type = check_expression(ctx, scope, call->callee, NULL);
            
            if (!callee_type) return NULL;
            
            if (callee_type->kind != TYPE_FUNCTION) {
                 TypeError err = {
                    .kind = TE_NOT_CALLABLE,
                    .span = call->callee->span,
                    .filename = ctx->filename,
                    .as.bad_usage.actual = callee_type
                };
                dynarray_push_value(ctx->errors, &err);
                return NULL;
            }

            // Argument Check
            size_t param_count = callee_type->as.func.param_count;
            size_t arg_count = call->args ? call->args->count : 0;

            
            if (arg_count != param_count) {
                TypeError err = {
                    .kind = TE_ARG_COUNT_MISMATCH,
                    .span = expr->span,
                    .filename = ctx->filename,
                    .as.arg_count = {
                        .expected = param_count,
                        .actual = arg_count
                    }
                };
                dynarray_push_value(ctx->errors, &err);
                return NULL;
            }

            for (size_t i = 0; i < arg_count; i++) {
                AstNode *arg = *(AstNode**)dynarray_get(call->args, i);
                Type *param_type = callee_type->as.func.params[i];

                // Check argument against parameter type
                Type *arg_type = check_expression(ctx, scope, arg, param_type);

                if (arg_type && param_type && arg_type != param_type) {
                    TypeError err = {
                        .kind = TE_TYPE_MISMATCH,
                        .span = arg->span,
                        .filename = ctx->filename,
                        .as.mismatch = {
                            .expected = param_type,
                            .actual = arg_type
                        }
                    };
                    dynarray_push_value(ctx->errors, &err);
                }
            }
            
            result_type = callee_type->as.func.return_type;
            break;
        }

        case AST_SUBSCRIPT_EXPR: {
            AstSubscriptExpr *subscript = &expr->data.subscript_expr;
            Type *base_type = check_expression(ctx, scope, subscript->target, NULL);
            Type *index_type = check_expression(ctx, scope, subscript->index, NULL);
            
            if (!base_type) return NULL;

            if (base_type->kind != TYPE_ARRAY && base_type->kind != TYPE_POINTER) {
                TypeError err = {
                    .kind = TE_NOT_INDEXABLE,
                    .span = subscript->target->span,
                    .filename = ctx->filename,
                    .as.bad_usage.actual = base_type
                };
                dynarray_push_value(ctx->errors, &err);
                return NULL;
            }
      
            if (base_type->kind == TYPE_ARRAY) {
                result_type = base_type->as.array.base;
            } else {
                result_type = base_type->as.ptr.base;
            }
            break;
        }

        default:
            break;
    }

    



    expr->type = result_type;
    return result_type;
}

static void check_initializer(TypeCheckContext *ctx, Scope *scope, AstNode *initializer, Type *var_type) {
    if (!initializer) return;
    
    Type *actual_type = check_expression(ctx, scope, initializer, var_type);
    
    // Type Mismatch Check
    if (actual_type && var_type && actual_type != var_type) {
        TypeError err = {
            .kind = TE_TYPE_MISMATCH,
            .span = initializer->span,
            .filename = ctx->filename,
            .as.mismatch = {
                .expected = var_type,
                .actual = actual_type
            }
        };
        dynarray_push_value(ctx->errors, &err);
    }
}



void check_variable_declaration(TypeCheckContext *ctx, Scope *scope, AstNode *var_node){
    if (var_node->node_type != AST_VARIABLE_DECLARATION) return;

    AstVariableDeclaration *var_decl = &var_node->data.variable_declaration;

    Type *var_type = resolve_ast_type(ctx->store, scope, var_decl->type);
    if (!var_type) {
        const char *var_name = "<unknown>";
        if (var_decl->intern_result && var_decl->intern_result->key) {
             var_name = ((Slice*)var_decl->intern_result->key)->ptr;
        }

        

        TypeError err = {
            .kind = TE_VARIABLE_TYPE_RESOLUTION_FAILED,
            .span = var_node->span,
            .filename = ctx->filename,
            .as.name.name = var_name
        };

        dynarray_push_value(ctx->errors, &err);
        return;
    }

    var_node->type = var_type;
    // Define variable symbol in the current scope
    if (var_decl->intern_result) {
        define_symbol_or_error(ctx, scope, var_decl->intern_result, var_type, SYMBOL_VARIABLE, var_node->span);
    }
    
    check_initializer(ctx, scope, var_node->data.variable_declaration.initializer, var_type);


}

static void check_function_body(TypeCheckContext *ctx, Scope *scope, AstNode *body_node, Type *expected_return_type) {
    if (body_node->node_type != AST_BLOCK) return;

    AstBlock *block = &body_node->data.block;

    
}

static void check_function(TypeCheckContext *ctx, Scope *parent_scope, AstNode *func_node) {
    AstFunctionDeclaration *decl = &func_node->data.function_declaration;
    
    // 1. Create a Scope for the arguments
    // (Arguments are local variables inside the function)
    Scope *fn_scope = scope_create(ctx->store->arena, parent_scope, 32, SCOPE_IDENTIFIERS);
    
    // 2. Define arguments in this scope
    Type *func_type = func_node->type;
    for (size_t i = 0; i < decl->params->count; i++) {
        AstNode *param = *(AstNode**)dynarray_get(decl->params, i);
        // The type was already resolved in Phase 1 and stored in param->type!
        if (param->data.param.name_idx != -1) {
            InternResult *name_rec = interner_get_result(ctx->identifiers, param->data.param.name_idx);
            define_symbol_or_error(ctx, fn_scope, name_rec, param->type, SYMBOL_VARIABLE, param->span);
        }
    }

    // 3. Check the body
    // We pass the expected return type so 'return' statements can be validated.
    check_function_body(ctx, fn_scope, decl->body, func_type->as.func.return_type);
}




void typecheck_program(TypeCheckContext *ctx) {
    if (!ctx || !ctx->program) return;
    // Create Global Scope (root)
    Arena *scope_arena = ctx->store->arena;
    int global_count = (ctx->identifiers ? ctx->identifiers->dense_index_count : 0) + 64;
    Scope *global_scope = scope_create(scope_arena, NULL, global_count, SCOPE_IDENTIFIERS);  

    
    // PASS 1: Resolve Function Signatures
    resolve_program_functions(ctx, global_scope);

    // PASS 2: Check Bodies and variable declarations
    // cant do variables in Pass 1 because they might depend on functions declared later
    // and because variables should only be valid from their point of declaration onward
    // whereas function signatures are valid throughout the entire global scope
    AstProgram *program = &ctx->program->data.program;
    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        switch (decl->node_type)
        {
        case AST_VARIABLE_DECLARATION:
            check_variable_declaration(ctx, global_scope, decl);
            break;
        case AST_FUNCTION_DECLARATION:
            check_function(ctx, global_scope, decl);
            break;
        default:
            break;
        }
    }
}