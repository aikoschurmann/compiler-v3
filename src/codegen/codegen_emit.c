#include "codegen_internal.h"
#include <llvm-c/Analysis.h>
#include <llvm-c/Transforms/PassBuilder.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Support.h>

void codegen_initialize(void) {
    LLVMInitializeAllTargetInfos();
    LLVMInitializeAllTargets();
    LLVMInitializeAllTargetMCs();
    LLVMInitializeAllAsmParsers();
    LLVMInitializeAllAsmPrinters();
    LLVMLinkInMCJIT();
    LLVMLoadLibraryPermanently(NULL);

#ifdef _WIN32
    // On Windows, LLVMLoadLibraryPermanently(NULL) does not expose CRT symbols
    // to the JIT. We must explicitly load the UCRT DLL so that @link("malloc"),
    // @link("free"), @link("printf"), etc. can be resolved at JIT runtime.
    LLVMLoadLibraryPermanently("ucrtbase.dll");   // UCRT (Windows 10+, MSYS2 UCRT64)
    LLVMLoadLibraryPermanently("msvcrt.dll");      // Fallback for older environments
#endif
}

static void run_optimizations(CodegenContext *ctx) {
    if (ctx->opt_level <= 0) return;

    char passes[32];
    snprintf(passes, sizeof(passes), "default<O%d>", ctx->opt_level);

    LLVMPassBuilderOptionsRef opts = LLVMCreatePassBuilderOptions();
    LLVMRunPasses(ctx->module, passes, ctx->machine, opts);
    LLVMDisposePassBuilderOptions(opts);
}

static bool is_generic_template(AstNode *decl) {
    if (!decl) return false;
    if (decl->node_type == AST_FUNCTION_DECLARATION) {
        AstFunctionDeclaration *func = &decl->data.function_declaration;
        if (func->type_params && func->type_params->count > 0) return true;
    } else if (decl->node_type == AST_STRUCT_DECLARATION) {
        AstStructDeclaration *str = &decl->data.struct_declaration;
        if (str->type_params && str->type_params->count > 0) return true;
    } else if (decl->node_type == AST_IMPL_DECLARATION) {
        AstImplDeclaration *impl = &decl->data.impl_declaration;
        if (impl->type_params && impl->type_params->count > 0) return true;
    }
    return false;
}

int codegen_program(CodegenContext *ctx) {
    if (!ctx || !ctx->loader || !ctx->loader->units_ordered) return -1;

    // Pass 1: Protos (All units)
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        if (!unit->ast_root) continue;
        
        AstProgram *prog = &unit->ast_root->data.program;
        if (!prog->decls) continue;

        for (size_t j = 0; j < prog->decls->count; j++) {
            AstNode *decl = *(AstNode**)dynarray_get(prog->decls, j);
            if (decl->node_type != AST_IMPORT_DECLARATION && !is_generic_template(decl)) {
                codegen_decl_proto(ctx, decl);
            }
        }

        if (unit->mono_instances) {
            for (size_t k = 0; k < unit->mono_instances->count; k++) {
                AstNode *mono_decl = *(AstNode**)dynarray_get(unit->mono_instances, k);
                codegen_decl_proto(ctx, mono_decl);
            }
        }
    }
    
    // Pass 2: Bodies (All units)
    for (size_t i = 0; i < ctx->loader->units_ordered->count; i++) {
        CompilationUnit *unit = *(CompilationUnit**)dynarray_get(ctx->loader->units_ordered, i);
        if (!unit->ast_root) continue;

        AstProgram *prog = &unit->ast_root->data.program;
        if (!prog->decls) continue;

        for (size_t j = 0; j < prog->decls->count; j++) {
            AstNode *decl = *(AstNode**)dynarray_get(prog->decls, j);
            if (decl->node_type != AST_IMPORT_DECLARATION && !is_generic_template(decl)) {
                codegen_decl_body(ctx, decl);
            }
        }

        if (unit->mono_instances) {
            for (size_t k = 0; k < unit->mono_instances->count; k++) {
                AstNode *mono_decl = *(AstNode**)dynarray_get(unit->mono_instances, k);
                codegen_decl_body(ctx, mono_decl);
            }
        }
    }

    // Run optimizations
    run_optimizations(ctx);

    char *v_error = NULL;
    if (LLVMVerifyModule(ctx->module, LLVMPrintMessageAction, &v_error) == 1) {
        fprintf(stderr, "Error: LLVM Code generation pass failed\n");
        LLVMDisposeMessage(v_error);
        exit(5);
    }
    if (v_error) LLVMDisposeMessage(v_error);
    return 0;
}

void codegen_dump_module(CodegenContext *ctx) {
    if (ctx->module) LLVMDumpModule(ctx->module);
}

void codegen_emit_object(CodegenContext *ctx, const char *filename) {
    if (!ctx->module) return;
    char *error = NULL;
    if (LLVMTargetMachineEmitToFile(ctx->machine, ctx->module, (char *)filename,
                                    LLVMObjectFile, &error)) {
        fprintf(stderr, "Error emitting object file: %s\n", error);
        LLVMDisposeMessage(error);
    }
}

int codegen_run_jit(CodegenContext *ctx) {
    if (!ctx->module) return -1;
    
    LLVMExecutionEngineRef engine;
    char *error = NULL;

    if (LLVMCreateExecutionEngineForModule(&engine, ctx->module, &error) != 0) {
        fprintf(stderr, "Failed to create execution engine: %s\n", error);
        LLVMDisposeMessage(error);
        return -1;
    }

    // CRITICAL FIX: The ExecutionEngine has successfully taken ownership of ctx->module.
    // We MUST set it to NULL here so we don't accidentally double-free it later.
    ctx->module = NULL;

    uint64_t addr = LLVMGetFunctionAddress(engine, "main");
    if (addr == 0) {
        fprintf(stderr, "Failed to resolve main function address in JIT\n");
        LLVMDisposeExecutionEngine(engine);
        return -1;
    }
    
    int (*main_ptr)(void) = (int (*)(void))addr;
    int result = main_ptr();

    LLVMDisposeExecutionEngine(engine);
    return result;
}
