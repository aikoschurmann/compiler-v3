#include "codegen_internal.h"

void codegen_decl_proto(CodegenContext *ctx, AstNode *decl) {
    if (decl->node_type == AST_FUNCTION_DECLARATION) {
        AstFunctionDeclaration *fdecl       = &decl->data.function_declaration;
        Type                   *fn_type_sema = decl->type;

        if (!fn_type_sema || fn_type_sema->kind != TYPE_FUNCTION) {
            ICE("Function declaration missing type or has incorrect type kind: %d", fn_type_sema ? fn_type_sema->kind : -1);
        }

        // Return type: Use indirect return if large struct
        bool sret = type_is_indirect(ctx, fn_type_sema->as.func.return_type);
        LLVMTypeRef ret_type = sret ? LLVMVoidTypeInContext(ctx->context) : get_llvm_type(ctx, fn_type_sema->as.func.return_type);
        
        size_t param_count = fn_type_sema->as.func.param_count;
        size_t llvm_param_count = param_count + (sret ? 1 : 0);
        LLVMTypeRef *llvm_params = malloc(sizeof(LLVMTypeRef) * llvm_param_count);

        size_t idx = 0;
        if (sret) {
            llvm_params[idx++] = LLVMPointerType(get_llvm_type(ctx, fn_type_sema->as.func.return_type), 0);
        }

        for (size_t i = 0; i < param_count; i++) {
            Type *param_ty = fn_type_sema->as.func.params[i];
            if (type_is_indirect(ctx, param_ty)) {
                llvm_params[idx++] = LLVMPointerType(get_llvm_type(ctx, param_ty), 0);
            } else {
                llvm_params[idx++] = get_llvm_type(ctx, param_ty);
            }
        }

        const char *name           = "anon_func";
        char       *allocated_name = NULL;
        if (fdecl->intern_result && fdecl->intern_result->key) {
            Slice *s = (Slice*)fdecl->intern_result->key;
            allocated_name = strndup(s->ptr, s->len);
            name = allocated_name;
        }

        LLVMTypeRef func_type = LLVMFunctionType(ret_type, llvm_params, (unsigned)llvm_param_count, 0);
        LLVMValueRef func = LLVMAddFunction(ctx->module, name, func_type);
        
        // Add attributes for sret/byval
        if (sret) {
            LLVMAddAttributeAtIndex(func, 1, LLVMCreateTypeAttribute(ctx->context, 
                LLVMGetEnumAttributeKindForName("sret", 4), get_llvm_type(ctx, fn_type_sema->as.func.return_type)));
        }

        idx = sret ? 1 : 0;
        for (size_t i = 0; i < param_count; i++) {
            if (type_is_indirect(ctx, fn_type_sema->as.func.params[i])) {
                LLVMTypeRef param_ty = get_llvm_type(ctx, fn_type_sema->as.func.params[i]);
                LLVMAddAttributeAtIndex(func, (unsigned)(idx + i + 1), LLVMCreateTypeAttribute(ctx->context, 
                    LLVMGetEnumAttributeKindForName("byval", 5), param_ty));
            }
        }

        if (allocated_name) free(allocated_name);
        if (llvm_params)     free(llvm_params);

    } else if (decl->node_type == AST_VARIABLE_DECLARATION) {
        AstVariableDeclaration *vdecl = &decl->data.variable_declaration;
        if (!decl->type) ICE("Variable declaration missing type.");
        LLVMTypeRef ty = get_llvm_type(ctx, decl->type);

        const char *name           = "global_var";
        char       *allocated_name = NULL;
        if (vdecl->intern_result && vdecl->intern_result->key) {
            Slice *s = (Slice*)vdecl->intern_result->key;
            allocated_name = strndup(s->ptr, s->len);
            name = allocated_name;
        }

        LLVMValueRef gvar = LLVMAddGlobal(ctx->module, ty, name);
        if (LLVMGetTypeKind(ty) != LLVMVoidTypeKind)
            LLVMSetInitializer(gvar, LLVMConstNull(ty));

        if (vdecl->intern_result) {
            hashmap_put(ctx->globals,
                        (void*)(intptr_t)vdecl->intern_result->entry->dense_index,
                        gvar, ptr_hash, ptr_cmp);
        }
        if (allocated_name) free(allocated_name);
    }
}

void codegen_decl_body(CodegenContext *ctx, AstNode *decl) {
    if (decl->node_type == AST_FUNCTION_DECLARATION) {
        AstFunctionDeclaration *fdecl = &decl->data.function_declaration;
        Type *fn_type_sema = decl->type;

        const char *name           = "anon_func";
        char       *allocated_name = NULL;
        if (fdecl->intern_result && fdecl->intern_result->key) {
            Slice *s = (Slice*)fdecl->intern_result->key;
            allocated_name = strndup(s->ptr, s->len);
            name = allocated_name;
        }

        LLVMValueRef func = LLVMGetNamedFunction(ctx->module, name);
        if (!func) ICE("codegen_decl_body: function '%s' not declared in proto pass", name);

        if (fdecl->body) {
            LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(ctx->context, func, "entry");
            LLVMPositionBuilderAtEnd(ctx->builder, entry);

            ctx->locals = codegen_map_create(ctx, ctx->locals);
            ctx->current_func_type = fn_type_sema;

            bool sret = type_is_indirect(ctx, fn_type_sema->as.func.return_type);
            if (sret) {
                ctx->sret_ptr = LLVMGetParam(func, 0);
            } else {
                ctx->sret_ptr = NULL;
            }
            
            // Register parameters
            size_t param_count = fdecl->params ? fdecl->params->count : 0;
            size_t idx = 0;
            if (sret) idx++;

            for (size_t i = 0; i < param_count; i++) {
                AstNode *param_node = *(AstNode**)dynarray_get(fdecl->params, i);
                AstParam *param = &param_node->data.param;
                
                LLVMValueRef val = LLVMGetParam(func, (unsigned int)idx++);
                Type *param_ty = fn_type_sema->as.func.params[i];
                
                LLVMValueRef storage;
                if (type_is_indirect(ctx, param_ty)) {
                    // Already a pointer (byval) - use it as-is
                    storage = val;
                } else {
                    // Value-type: register via alloca
                    LLVMTypeRef ty = get_llvm_type(ctx, param_node->type);
                    storage = LLVMBuildAlloca(ctx->builder, ty, "param");
                    LLVMBuildStore(ctx->builder, val, storage);
                }

                if (param->name_idx != -1) {
                    codegen_map_put(ctx->locals, (void*)(intptr_t)param->name_idx, storage);
                }
            }
            
            // Generate the user's actual code
            codegen_expr_stmt(ctx, fdecl->body);

            CodegenMap *old = ctx->locals;
            ctx->locals = old->parent;
            codegen_map_destroy(old);
            ctx->current_func_type = NULL;
            ctx->sret_ptr = NULL;
            
            LLVMBasicBlockRef current_block = LLVMGetInsertBlock(ctx->builder);
            if (!LLVMGetBasicBlockTerminator(current_block)) {
                LLVMTypeRef ret_ty = LLVMGetReturnType(LLVMGlobalGetValueType(func));
                if (LLVMGetTypeKind(ret_ty) == LLVMVoidTypeKind) {
                    LLVMBuildRetVoid(ctx->builder);
                } else {
                    LLVMBuildRet(ctx->builder, LLVMConstNull(ret_ty));
                }
            }

        } else if (fdecl->link_name) {
            // ... (linkage logic remains)
            Slice *s = (Slice*)fdecl->link_name->key;
            char *ext_name = malloc(s->len + 1);
            memcpy(ext_name, s->ptr, s->len);
            ext_name[s->len] = '\0';

            Slice *ns = (Slice*)fdecl->intern_result->key;
            char *int_name = malloc(ns->len + 1);
            memcpy(int_name, ns->ptr, ns->len);
            int_name[ns->len] = '\0';

            if (strcmp(ext_name, int_name) != 0) {
                LLVMSetLinkage(func, LLVMInternalLinkage);

                LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(ctx->context, func, "entry");
                LLVMPositionBuilderAtEnd(ctx->builder, entry);

                LLVMValueRef ext_func = LLVMGetNamedFunction(ctx->module, ext_name);
                if (!ext_func) {
                    ext_func = LLVMAddFunction(ctx->module, ext_name, LLVMGlobalGetValueType(func));
                }

                size_t param_count = LLVMCountParams(func);
                LLVMValueRef *args = NULL;
                if (param_count > 0) {
                    args = malloc(sizeof(LLVMValueRef) * param_count);
                    for (size_t i = 0; i < param_count; i++) {
                        args[i] = LLVMGetParam(func, (unsigned int)i);
                    }
                }

                LLVMTypeRef ret_ty = LLVMGetReturnType(LLVMGlobalGetValueType(func));
                if (LLVMGetTypeKind(ret_ty) == LLVMVoidTypeKind) {
                    LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(ext_func), ext_func, args, (unsigned int)param_count, "");
                    LLVMBuildRetVoid(ctx->builder);
                } else {
                    LLVMValueRef call_res = LLVMBuildCall2(ctx->builder, LLVMGlobalGetValueType(ext_func), ext_func, args, (unsigned int)param_count, "ffi_call");
                    LLVMBuildRet(ctx->builder, call_res);
                }
                if (args) free(args);
            }
            free(ext_name);
            free(int_name);
        }
        if (allocated_name) free(allocated_name);

    } else if (decl->node_type == AST_VARIABLE_DECLARATION) {
        AstVariableDeclaration *vdecl = &decl->data.variable_declaration;
        if (vdecl->initializer) {
            const char *name           = "global_var";
            char       *allocated_name = NULL;
            if (vdecl->intern_result && vdecl->intern_result->key) {
                Slice *s = (Slice*)vdecl->intern_result->key;
                allocated_name = strndup(s->ptr, s->len);
                name = allocated_name;
            }
            LLVMValueRef gvar = LLVMGetNamedGlobal(ctx->module, name);
            if (gvar) {
                LLVMValueRef init_val = codegen_expr(ctx, vdecl->initializer);
                if (init_val && LLVMIsConstant(init_val))
                    LLVMSetInitializer(gvar, init_val);
            }
            if (allocated_name) free(allocated_name);
        }
    }
}
