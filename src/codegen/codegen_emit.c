#include "codegen_internal.h"
#include <llvm-c/Analysis.h>

int codegen_program(CodegenContext *ctx) {
    if (!ctx->program || ctx->program->node_type != AST_PROGRAM) return -1;

    DynArray *decls = ctx->program->data.program.decls;
    if (!decls) return 0;

    for (size_t i = 0; i < decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(decls, i);
        codegen_decl_proto(ctx, decl);
    }
    for (size_t i = 0; i < decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(decls, i);
        codegen_decl_body(ctx, decl);
    }

    char *error = NULL;
    if (LLVMVerifyModule(ctx->module, LLVMPrintMessageAction, &error) == 1) {
        fprintf(stderr, "LLVM Verification Error: %s\n", error ? error : "Unknown");
        if (error) LLVMDisposeMessage(error);
        return -1;
    }
    if (error) LLVMDisposeMessage(error);
    return 0;
}

void codegen_dump_module(CodegenContext *ctx) {
    LLVMDumpModule(ctx->module);
}

void codegen_emit_object(CodegenContext *ctx, const char *filename) {
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmParsers();
    LLVMInitializeAllAsmPrinters();

    char *target_triple = LLVMGetDefaultTargetTriple();
    LLVMSetTarget(ctx->module, target_triple);

    char        *error  = NULL;
    LLVMTargetRef target;
    if (LLVMGetTargetFromTriple(target_triple, &target, &error)) {
        fprintf(stderr, "Error getting target: %s\n", error);
        LLVMDisposeMessage(error);
        LLVMDisposeMessage(target_triple);
        return;
    }

    LLVMTargetMachineRef machine = LLVMCreateTargetMachine(
        target, target_triple, "generic", "",
        LLVMCodeGenLevelAggressive, LLVMRelocDefault, LLVMCodeModelDefault);

    LLVMTargetDataRef data_layout = LLVMCreateTargetDataLayout(machine);
    LLVMSetModuleDataLayout(ctx->module, data_layout);

    if (LLVMTargetMachineEmitToFile(machine, ctx->module, (char *)filename,
                                    LLVMObjectFile, &error)) {
        fprintf(stderr, "Error emitting object file: %s\n", error);
        LLVMDisposeMessage(error);
    }

    LLVMDisposeMessage(target_triple);
    LLVMDisposeTargetMachine(machine);
    LLVMDisposeTargetData(data_layout);
}
