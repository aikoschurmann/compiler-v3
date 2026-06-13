#include "codegen_internal.h"

LLVMValueRef create_entry_block_alloca(CodegenContext *ctx, LLVMTypeRef ty, const char *name) {
    LLVMBasicBlockRef current_block = LLVMGetInsertBlock(ctx->builder);
    LLVMValueRef current_func = LLVMGetBasicBlockParent(current_block);
    LLVMBasicBlockRef entry_block = LLVMGetEntryBasicBlock(current_func);
    
    // Create a temporary builder pointing to the top of the entry block
    LLVMBuilderRef tmp_builder = LLVMCreateBuilderInContext(ctx->context);
    
    LLVMValueRef first_instr = LLVMGetFirstInstruction(entry_block);
    if (first_instr) {
        LLVMPositionBuilderBefore(tmp_builder, first_instr);
    } else {
        LLVMPositionBuilderAtEnd(tmp_builder, entry_block);
    }
    
    LLVMValueRef alloca = LLVMBuildAlloca(tmp_builder, ty, name);
    LLVMDisposeBuilder(tmp_builder);
    
    return alloca;
}

size_t struct_field_index(Type *struct_type, const char *field_name) {
    if (struct_type->kind != TYPE_STRUCT) return (size_t)-1;
    
    for (size_t i = 0; i < struct_type->as.struct_type.field_count; i++) {
        Slice *name = (Slice*)struct_type->as.struct_type.fields[i].name->key;
        if (name->len == strlen(field_name) && memcmp(name->ptr, field_name, name->len) == 0) {
            return i;
        }
    }
    return (size_t)-1;
}
