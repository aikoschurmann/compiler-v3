#include "typecheck.h"
#include "core/utils.h" 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Type *resolve_ast_type(TypeStore *store, Scope *scope, AstNode *node) {
    if (!store || !node) return NULL;
    
    if (node->node_type != AST_TYPE) {
        return NULL;
    }

    AstType *ast_ty = &node->data.ast_type;

    switch (ast_ty->kind) {
        case AST_TYPE_PRIMITIVE: {
            InternResult *name_res = ast_ty->u.base.intern_result;
            void *key_ptr = name_res ? name_res->key : NULL;

            // 1. FAST LOOKUP: Check the Primitive Registry
            // This effectively treats primitives as "reserved type names"
            if (key_ptr) {
                Type *prim = (Type*)hashmap_get(store->primitive_registry, key_ptr, ptr_hash, ptr_cmp);
                if (prim) {
                    return prim;
                }
            }

            // 2. If not a primitive, THEN check the User Scope
            // This finds structs, enums, or typedefs defined by the user.
            if (scope) {
                Symbol *sym = scope_lookup_symbol(scope, name_res);
                if (sym && sym->kind == SYMBOL_VALUE_TYPE) {
                    return sym->type;
                }
            }
            return NULL; 
        }

        case AST_TYPE_PTR: {
            Type *target = resolve_ast_type(store, scope, ast_ty->u.ptr.target);
            if (!target) return NULL;

            Type proto = {0};
            proto.kind = TYPE_POINTER;
            proto.as.ptr.base = target;
            
            InternResult *res = intern_type(store, &proto);
            if (!res) return NULL;
            return (Type*)((Slice*)res->key)->ptr;
        }

        case AST_TYPE_ARRAY: {
            Type *elem = resolve_ast_type(store, scope, ast_ty->u.array.elem);
            if (!elem) return NULL;

            int64_t size = 0;
            bool size_known = false;
            
            if (ast_ty->u.array.size_expr) {
                AstNode *sz = ast_ty->u.array.size_expr;
                if (sz->node_type == AST_LITERAL && sz->data.literal.type == INT_LITERAL) {
                    size = sz->data.literal.value.int_val;
                    size_known = true;
                } else if (sz->is_const_expr && sz->data.literal.type == INT_LITERAL) {
                     size = sz->data.literal.value.int_val;
                     size_known = true;
                }
                
                if (!size_known) {
                    return NULL;
                }
            }

            Type proto = {0};
            proto.kind = TYPE_ARRAY;
            proto.as.array.base = elem;
            proto.as.array.size = size;
            proto.as.array.size_known = size_known;

            InternResult *res = intern_type(store, &proto);
            if (!res) return NULL;
            return (Type*)((Slice*)res->key)->ptr;
        }

        case AST_TYPE_FUNC: {
             Type *ret = resolve_ast_type(store, scope, ast_ty->u.func.return_type);
             if (!ret) return NULL;
             
             DynArray *params = ast_ty->u.func.param_types;
             size_t count = params ? params->count : 0;
             
             Type **param_types = NULL;
             if (count > 0) {
                 param_types = malloc(sizeof(Type*) * count);
                 if (!param_types) return NULL;
             }
             
             for (size_t i = 0; i < count; i++) {
                 AstNode *p_node = *(AstNode**)dynarray_get(params, i);
                 Type *pt = resolve_ast_type(store, scope, p_node);
                 if (!pt) {
                     free(param_types);
                     return NULL;
                 }
                 param_types[i] = pt;
             }
             
             Type proto = {0};
             proto.kind = TYPE_FUNCTION;
             proto.as.func.return_type = ret;
             proto.as.func.param_count = count;
             proto.as.func.params = param_types;
             
             InternResult *res = intern_type(store, &proto);
             
             free(param_types);
             
             if (!res) return NULL;
             return (Type*)((Slice*)res->key)->ptr;
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
void resolve_program_functions(TypeStore *store, AstProgram *program, DenseArenaInterner *identifiers, DenseArenaInterner *keywords) {
    if (!store || !program || !program->decls) return;

    // Create Global Scope (root) using IDENTIFIERS
    // Primitives are in the registry, avoiding the need for a separate Universe scope.
    Arena *scope_arena = store->arena;
    int global_count = identifiers->dense_index_count + 64;
    Scope *global_scope = scope_create(scope_arena, NULL, global_count, SCOPE_IDENTIFIERS);  

    for (size_t i = 0; i < program->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(program->decls, i);
        if (!decl) continue;

        if (decl->node_type == AST_FUNCTION_DECLARATION) {
             resolve_function_decl(store, global_scope, decl);

             // Define function symbol in global scope
             AstFunctionDeclaration *func = &decl->data.function_declaration;
             if (func->intern_result && decl->type) {
                 scope_define_symbol(global_scope, func->intern_result, decl->type, SYMBOL_VALUE_FUNCTION);
             }
        }
        //else if (decl->node_type == AST_VARIABLE_DECLARATION) {
        //     AstVariableDeclaration *var = &decl->data.variable_declaration;
        //     if (var->type) {
        //         decl->type = resolve_ast_type(store, global_scope, var->type);
        //     }
        //     
        //     if (var->intern_result && decl->type) {
        //         scope_define_symbol(global_scope, var->intern_result, decl->type, SYMBOL_VARIABLE);
        //     }
        //}
    }
}
