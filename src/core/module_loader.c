#include "module_loader.h"
#include "file.h"
#include "lexing/lexer.h"
#include "parsing/parser.h"
#include "parsing/parse_statements.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>

#define EXIT_OK    0
#define EXIT_USAGE 1
#define EXIT_IO    2
#define EXIT_LEX   3
#define EXIT_PARSE 4
#define EXIT_TYPE  5

ModuleLoader* module_loader_create(Arena *arena, Options *opts, 
                                   DenseArenaInterner *keywords, 
                                   DenseArenaInterner *identifiers, 
                                   DenseArenaInterner *strings) {
    ModuleLoader *loader = arena_alloc(arena, sizeof(ModuleLoader));
    loader->arena = arena;
    loader->opts = opts;
    loader->keywords = keywords;
    loader->identifiers = identifiers;
    loader->strings = strings;
    
    loader->units = hashmap_create(16);
    loader->units_by_logical_path = hashmap_create(16);
    loader->units_ordered = arena_alloc(arena, sizeof(DynArray));
    dynarray_init_in_arena(loader->units_ordered, arena, sizeof(CompilationUnit*), 8);
    
    loader->project_root = NULL;

    return loader;
}

static char* get_absolute_path_real(Arena *arena, const char *path) {
    char *abs = realpath(path, NULL);
    if (!abs) return NULL;
    char *interned = arena_alloc(arena, strlen(abs) + 1);
    strcpy(interned, abs);
    free(abs);
    return interned;
}

CompilationUnit* module_loader_get_unit(ModuleLoader *loader, const char *path) {
    return (CompilationUnit*)hashmap_get(loader->units, (void*)path, str_hash, str_cmp);
}

static bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

int load_module_recursive(ModuleLoader *loader, const char *path, const char *logical_path, const char *importer_path) {
    char *abs_path = get_absolute_path_real(loader->arena, path);
    if (!abs_path) {
        // Fallback for module.tn if path might be a directory
        char fallback[1024];
        snprintf(fallback, sizeof(fallback), "%s/module.tn", path);
        abs_path = get_absolute_path_real(loader->arena, fallback);
        
        if (!abs_path) {
            if (importer_path) {
                fprintf(stderr, "Error in %s: Could not resolve module path '%s'\n", importer_path, path);
            } else {
                fprintf(stderr, "Error: Could not resolve module path '%s'\n", path);
            }
            return EXIT_IO;
        }
    }
    
    // Set project root on first call
    if (!loader->project_root) {
        char *dir = strdup(abs_path);
        char *last_slash = strrchr(dir, '/');
        if (last_slash) *last_slash = '\0';
        loader->project_root = arena_alloc(loader->arena, strlen(dir) + 1);
        strcpy(loader->project_root, dir);
        free(dir);
    }

    // 1. Check if module is already loaded
    CompilationUnit *unit = module_loader_get_unit(loader, abs_path);
    if (unit) {
        // Map to logical path if provided
        if (logical_path) {
            hashmap_put(loader->units_by_logical_path, (void*)logical_path, unit, str_hash, str_cmp);
            if (!unit->logical_path) unit->logical_path = (char*)logical_path;
        }
        return EXIT_OK;
    }

    if (loader->opts->verbose) printf("Loading module: %s\n", abs_path);

    // 2. Read Source
    char *src = read_file(abs_path);
    if (!src) {
        fprintf(stderr, "Error: Failed to read file: %s\n", abs_path);
        return EXIT_IO;
    }
    size_t src_len = strlen(src);

    // 3. Lexing (Shared Interners)
    Lexer *lexer = lexer_create_ex(src, src_len, loader->arena, loader->keywords, loader->identifiers, loader->strings);
    if (!lexer_lex_all(lexer)) {
        fprintf(stderr, "Error: Lexing failed for %s\n", abs_path);
        free(src);
        return EXIT_LEX;
    }

    // 4. Parsing
    Parser *parser = parser_create(lexer->tokens, abs_path, loader->arena);
    ParseError parse_err = {0};
    AstNode *module_ast = parse_program(parser, &parse_err);
    if (parse_err.message) {
        print_parse_error(&parse_err);
        free(src);
        return EXIT_PARSE;
    }

    if (!module_ast) {
        free(src);
        return EXIT_OK;
    }

    // Create CompilationUnit
    unit = arena_alloc(loader->arena, sizeof(CompilationUnit));
    unit->absolute_path = abs_path;
    unit->logical_path = (char*)logical_path; 
    unit->ast_root = module_ast;
    unit->global_scope = NULL; 
    unit->signatures_resolved = false;
    unit->imports_resolved = false;
    
    hashmap_put(loader->units, abs_path, unit, str_hash, str_cmp);
    if (logical_path) {
        hashmap_put(loader->units_by_logical_path, (void*)logical_path, unit, str_hash, str_cmp);
    }

    // 5. Recursive Loading
    AstProgram *module_prog = &module_ast->data.program;
    
    // Get directory of current module for relative resolution
    char current_dir[1024];
    const char *last_slash = strrchr(abs_path, '/');
    if (last_slash) {
        size_t len = (size_t)(last_slash - abs_path);
        if (len >= sizeof(current_dir)) len = sizeof(current_dir) - 1;
        memcpy(current_dir, abs_path, len);
        current_dir[len] = '\0';
    } else {
        strcpy(current_dir, ".");
    }

    for (size_t i = 0; i < module_prog->decls->count; i++) {
        AstNode *decl = *(AstNode**)dynarray_get(module_prog->decls, i);
        
        if (decl->node_type == AST_IMPORT_DECLARATION) {
            AstImportDeclaration *imp = &decl->data.import_declaration;
            
            char components_path[512] = {0};
            char components_logical[512] = {0};
            size_t cp_len = 0;
            size_t cl_len = 0;
            
            for (size_t j = 0; j < imp->module_path->count; j++) {
                InternResult *part = *(InternResult**)dynarray_get(imp->module_path, j);
                Slice *s = (Slice*)part->key;
                if (cp_len + s->len + 1 < sizeof(components_path)) {
                    if (j > 0) components_path[cp_len++] = '/';
                    memcpy(components_path + cp_len, s->ptr, s->len);
                    cp_len += s->len;
                }
                if (cl_len + s->len + 1 < sizeof(components_logical)) {
                    if (j > 0) components_logical[cl_len++] = '.';
                    memcpy(components_logical + cl_len, s->ptr, s->len);
                    cl_len += s->len;
                }
            }
            components_path[cp_len] = '\0';
            components_logical[cl_len] = '\0';

            char mod_path_full[2048];
            char *target_logical = NULL;
            
            if (imp->leading_dots > 0) {
                // Relative Import
                char base_dir[1024];
                strcpy(base_dir, current_dir);
                
                // For .. or more, go up
                for (int d = 1; d < imp->leading_dots; d++) {
                    char *up = strrchr(base_dir, '/');
                    if (up) *up = '\0';
                }
                
                snprintf(mod_path_full, sizeof(mod_path_full), "%s/%s", base_dir, components_path);

                // Target logical name: importer's logical path + components_logical
                if (unit->logical_path) {
                    size_t t_len = strlen(unit->logical_path) + cl_len + 2;
                    target_logical = arena_alloc(loader->arena, t_len);
                    snprintf(target_logical, t_len, "%s.%s", unit->logical_path, components_logical);
                } else {
                    target_logical = arena_alloc(loader->arena, cl_len + 1);
                    strcpy(target_logical, components_logical);
                }
            } else if (imp->is_root_relative) {
                // Root-relative Import
                snprintf(mod_path_full, sizeof(mod_path_full), "%s/%s", loader->project_root, components_path);
                target_logical = arena_alloc(loader->arena, cl_len + 1);
                strcpy(target_logical, components_logical);
            } else {
                // Absolute (Library) Import
                snprintf(mod_path_full, sizeof(mod_path_full), "%s/%s", loader->opts->stdlib_path, components_path);
                target_logical = arena_alloc(loader->arena, cl_len + 1);
                strcpy(target_logical, components_logical);
            }

            // Try .tn then /module.tn
            char target_file[2100];
            snprintf(target_file, sizeof(target_file), "%s.tn", mod_path_full);
            
            if (!file_exists(target_file)) {
                 snprintf(target_file, sizeof(target_file), "%s/module.tn", mod_path_full);
            }
            
            int res = load_module_recursive(loader, target_file, target_logical, abs_path);
            if (res == EXIT_OK) {
                decl->data.import_declaration.resolved_logical_path = target_logical;
            } else {
                free(src);
                return res;
            }
        }
    }

    dynarray_push_value(loader->units_ordered, &unit);

    free(src);
    return EXIT_OK;
}
