# compiler-v3 — Code Analysis Report
**Generated:** June 14, 2026  
**Analyst:** Claude (Sonnet 4.6)  
**Against:** STABILIZATION_REPORT.md (June 14, 2026)

---

## 1. Report Verification — What Was Actually Fixed

Every claim in the stabilisation report was cross-checked against the source. All seven fixes are present and correctly implemented.

| Claim | File / Location | Verdict |
|---|---|---|
| Greedy struct heuristic (block vs struct-literal) | `parse_statements.c:1174–1188` | ✅ Correct. `TOK_LBRACE` after a non-`AST_MEMBER_EXPR` now breaks immediately; 2-token lookahead gates the literal path. |
| Shorthand field init + trailing commas | `parse_struct_declaration` | ✅ Present |
| `resolve_ast_type` handles `AST_MEMBER_EXPR` / `AST_IDENTIFIER` | `typecheck.c:163–196` | ✅ Both branches implemented |
| Hierarchical module loading / relative imports | `module_loader.c:185–229` | ✅ Parent logical path is prepended to relative components |
| String → `*char` decay | `type_utils.c`: `type_can_implicit_cast` rule 4 | ✅ Implemented |
| Bus Error 10 (LValue → Load pattern) | `codegen_expr.c: codegen_expr_ident`, `codegen_expr_member` | ✅ Both now delegate to `codegen_lvalue` + `codegen_load_value` |
| Missing basic-block terminators (implicit return after defers) | `codegen_decl.c:161–182` | ✅ Insert-block is re-fetched after deferred actions; sret path emits `ret void` |
| `-rdynamic` linker flag | `makefile: LDFLAGS_BASE` | ✅ Present |

**Test count:** The report claims 114/114. No regression suite was run here, but the code paths covering each fixed bug are all intact.

---

## 2. Security Issues

### S-1 · `system()` call with user-controlled input — `src/main.c:150` — **HIGH**

```c
char run_cmd[512];
snprintf(run_cmd, sizeof(run_cmd), "./%s", opts.output_name);
system(run_cmd);   // ← shell-invoked
```

`opts.output_name` is a CLI argument. A user passing `-o 'foo; rm -rf /'` will cause the shell spawned by `system()` to execute the injected command. The linker step directly above correctly uses `fork + execvp`, which never invokes a shell. The run step must match.

**Fix:** Replace with `fork + execvp`:

```c
pid_t pid2 = fork();
if (pid2 == 0) {
    char *run_args[] = { run_cmd, NULL };
    execvp(run_cmd, run_args);
    exit(1);
} else if (pid2 > 0) {
    waitpid(pid2, NULL, 0);
}
```

---

## 3. Memory Safety Issues

### M-1 · Unchecked `malloc` returns throughout codegen — **MEDIUM**

Every `malloc` call in `codegen_expr.c`, `codegen_decl.c`, `codegen_call.c`, and `codegen_utils.c` is used without a NULL check. In practice a compiler rarely hits OOM, but when it does the process will crash with a null-dereference inside LLVM rather than printing a clean error.

Key offenders:

```c
// codegen_expr.c:101
char *str = malloc(s->len + 1);
memcpy(str, s->ptr, s->len);   // ← segfault if malloc returns NULL

// codegen_utils.c:37
char *mangled = malloc(len);
snprintf(mangled, len, ...);   // ← same

// codegen_utils.c:28 — mangle_name
char *log_path_fixed = strdup(unit->logical_path);  // unchecked
```

**Fix:** Add a small helper:

```c
static void *xmalloc(size_t n) {
    void *p = malloc(n);
    if (!p) { fprintf(stderr, "fatal: out of memory\n"); abort(); }
    return p;
}
```

Replace every bare `malloc` / `strdup` in codegen with `xmalloc` / `xstrdup`. This converts a silent crash into a clean message.

### M-2 · Partially-initialised unit left in map on failed recursive load — `module_loader.c:139 vs 232` — **MEDIUM**

```c
// Line 139 — unit registered BEFORE children are loaded
hashmap_put(loader->units, abs_path, unit, str_hash, str_cmp);

// Line 232 — child load can fail
int res = load_module_recursive(loader, target_file, ...);
if (res != EXIT_OK) {
    free(src);
    return res;   // ← unit stays in the map, half-initialised
}
```

The early registration is correct for cycle detection, but if a child fails the parent unit is left in `loader->units` with `imports_resolved = false` and an incomplete `units_ordered` list. Subsequent analysis passes that walk `units_ordered` won't see it, but anything that calls `module_loader_get_unit` on the same path again will get the broken unit instead of reloading.

**Fix:** On failure, remove the unit from the map before returning:

```c
if (res != EXIT_OK) {
    hashmap_remove(loader->units, abs_path, str_hash, str_cmp);
    free(src);
    return res;
}
```

### M-3 · `arena_total_allocated` returns `int` instead of `size_t` — `arena.c:137` — **LOW**

```c
int arena_total_allocated(const Arena *arena) {   // ← int
    size_t total = 0;
    for (...) total += b->used;
    return total;   // ← silently truncates on > 2 GB arenas
}
```

The function is used in `main.c` to compute `mem_sema`. A large compilation that crosses 2 GB of arena use will report a negative or wrapped metric. The declaration in `arena.h` is also `int`, so it's consistent but wrong.

**Fix:** Change signature to `size_t arena_total_allocated(const Arena *arena)` in both the header and implementation.

---

## 4. Code Quality Issues

### Q-1 · No compiler warning flags in `CFLAGS_BASE` — `makefile` — **HIGH**

```makefile
CFLAGS_BASE := -Iinclude ... -g   # ← no -Wall, no -Wextra
```

Every build mode (release, dev, asan) inherits this base. The compiler is thus building itself without catching signed/unsigned mismatches, unused variables, implicit function declarations, or missing return values — all of which are present or plausible given the issues found above.

**Fix:**

```makefile
CFLAGS_BASE := -Iinclude ... -g \
    -Wall -Wextra -Wno-unused-parameter \
    -Wshadow -Wstrict-prototypes -Wmissing-prototypes
```

Add `-Werror` for the dev/asan builds. Expect a first pass of warnings to surface the `int`/`size_t` mismatch, the `ptr_cmp` issue, and several others in this report.

### Q-2 · Debug `fprintf` left in production code — `typecheck.c:822` — **MEDIUM**

```c
fprintf(stderr, "DEBUG: Failed to resolve import '%s' in %s\n",
        logical_path_str, unit->absolute_path);
```

This fires on any unresolved import in a normal compile run and was clearly scaffolding. It should be removed or gated behind `opts->verbose`.

### Q-3 · `ptr_cmp` violates the comparator contract — `hash_map.h:18` — **MEDIUM**

```c
static inline int ptr_cmp(void *a, void *b) { return (a == b) ? 0 : 1; }
```

A standard C comparator must return negative, zero, or positive. This one only returns 0 or 1. It works correctly for hash-map equality lookups, but the same function signature (`int (*cmp)(void*, void*)`) is reused by `dynarray_find` and could be passed to `qsort`-style APIs in future. It also misleads any reader who expects the usual three-way contract.

**Fix:**

```c
static inline int ptr_cmp(void *a, void *b) {
    return (a > b) - (a < b);
}
```

Note: `ptr_identity_cmp` in `utils.h:49` already uses the correct pattern. The two functions are duplicates; one should be removed.

### Q-4 · `Slice.len` is `uint32_t` while surrounding code uses `size_t` — `utils.h:18` — **LOW**

```c
typedef struct {
    const char *ptr;
    uint32_t len;   // ← 32-bit
} Slice;
```

In `codegen_utils.c:43` this is passed as `(int)s->len` to `snprintf`, which is a narrowing cast with sign-change. For slices representing source tokens this is fine in practice (no 2 GB token), but the `(int)` cast suppresses any future warning. Change `uint32_t` to `size_t` and remove the cast, or add a `static_assert(s->len <= INT_MAX)` guard.

### Q-5 · Non-`inline` static functions defined in headers — `utils.h`, `hash_map.h` — **LOW**

Several utility functions (`slice_hash`, `slice_cmp`, `str_hash`, `str_cmp`, `ptr_identity_hash`, `ptr_identity_cmp`) are declared `static` but not `static inline`. Every `.c` file that includes these headers gets its own private copy. With ~15 translation units this means ~15 copies of each function. Mark them `static inline` or move their bodies to a `utils.c` and declare them `extern`.

### Q-6 · `parse_statements.c` is 2113 lines — **LOW**

This single file contains primary parsing, postfix parsing, type parsing, statement parsing, expression parsing, and all struct/function/variable declaration logic. It is the single largest file and the one most likely to receive future changes. A split into at least `parse_expressions.c`, `parse_types.c`, and `parse_declarations.c` would make the file tractable.

---

## 5. Technical Debt — Status and Priority

These are the items acknowledged in the stabilisation report, assessed against the current code.

### TD-1 · Fixed-size buffers in `module_loader.c` — **Active Risk**

The report flags this. The specific sizes and where they can silently truncate:

| Buffer | Size | Risk |
|---|---|---|
| `fallback[1024]` (line 62) | 1 KB | Truncated path → wrong file resolved silently |
| `current_dir[1024]` (line 148) | 1 KB | Same |
| `base_dir[1024]` (line 192) | 1 KB | Same |
| `components_path[512]` (line 165) | 512 B | Long import chain truncated |
| `components_logical[512]` (line 166) | 512 B | Same |
| `mod_path_full[2048]` (line 187) | 2 KB | Composed path truncated |
| `target_file[2100]` (line 225) | 2.1 KB | Same |

All use `snprintf` so there is no buffer overflow — but silent truncation causes the wrong file to be looked up with no error message. On deep stdlib paths this is a latent correctness bug.

**Suggested fix:** A small `StringBuilder` backed by the arena:

```c
typedef struct { char *buf; size_t len; size_t cap; Arena *arena; } StrBuf;
// strbuf_append(sb, str), strbuf_appendf(sb, fmt, ...)
// strbuf_cstr(sb) — returns null-terminated pointer into arena
```

Replace all path-composing snprintf chains with this. One-time cost, eliminates the whole class of issue.

### TD-2 · Dummy module symbols polluting the scope — **Manageable**

```c
// typecheck.c:863
// Create a dummy module symbol for the namespace.
// This dummy is 'pub' so we can traverse it.
```

Dummy symbols exist so that `std.io.open` can be looked up as `std → io → open` through the scope chain. The problem is they're indistinguishable from real symbols to any code that iterates the scope, which will matter when implementing features like "list all symbols in scope" for error recovery or an LSP.

The report's recommended fix (a dedicated `Universe` scope) would also solve this. Intermediate mitigation: add a `SYMBOL_KIND_NAMESPACE_PROXY` kind to make them identifiable.

### TD-3 · `is_const_expr` dual semantics — **Active in codegen**

The flag means two different things:

1. "This expression is safe to fold at compile time" (used in `codegen_expr.c:266` to short-circuit)
2. "This value is safe to use as a global initializer" (the `LLVMIsConstant` check in `codegen_decl.c:238` is actually used instead, which partially decouples them)

The codegen correctly falls back to `LLVMIsConstant` for globals, but the semantic analysis still sets `is_const_expr = 1` on struct/array constants (`typecheck_expr.c:280`) even when their codegen path goes through alloca+load rather than a constant fold. This means the fast-path in `codegen_expr` will attempt to call `codegen_const_value` on a struct, which will hit the `ICE` at the bottom of that function.

**Fix:** Split into two flags:
```c
uint8_t is_foldable_const;    // safe for constant folding (primitives only)
uint8_t is_llvm_const_safe;   // safe as LLVM global initializer
```

### TD-4 · Implicit cast logic is scattered — **Refactor Priority**

`type_can_implicit_cast` lives in `type_utils.c`. `insert_cast` lives in `typecheck_expr.c`. The call sites are in at least three different check functions. When a new implicit conversion is added (like the `str → *char` one in this release), you must remember to update the rule in one place but verify the cast insertion happens in all the right call sites.

**Fix:** The report's recommendation is correct — a single `coerce_or_error(ctx, node, target_type)` function that calls `type_can_implicit_cast` and `insert_cast` together, replacing all scattered call-pairs.

### TD-5 · No recursion depth limit on `load_module_recursive` — **Unacknowledged Debt**

This was not listed in the report. Extremely deep import chains (not circular — the cycle guard works — but chains like A → B → C → ... → Z) can exhaust the C call stack. A depth counter passed through the recursion and capped at a reasonable limit (e.g., 256) would give a clean error instead of a SIGSEGV.

---

## 6. Architecture Observations

**What's working well:**

- The arena allocator is solid — proper alignment, overflow checks, multi-block growth, and a `reset` path. The `arena_calloc` helper is a nice touch.
- The `ICE` / `ICE_AT` macros with stack traces make internal errors debuggable quickly.
- The two-pass codegen (proto then body) is the correct architecture for mutual recursion and forward references.
- The ASAN build target in the Makefile is good infrastructure — it just needs to be run regularly.
- The LValue → Load unification was the right architectural fix; the pre-fix pattern of having `codegen_expr_ident` and `codegen_expr_member` do their own loads independently was the root of the Bus Error 10.

**Structural concerns going forward:**

The typecheck file at 1043 lines already feels heavy and the sema pass is still growing. The report's "Universe scope" and "Unify path resolution" recommendations would meaningfully reduce the size and complexity of `typecheck.c`. They should be prioritised before the file becomes unmaintainable.

---

## 7. Priority Summary

| ID | Issue | Severity | Effort |
|---|---|---|---|
| S-1 | `system()` command injection in `--run` | 🔴 High | Small |
| Q-1 | No `-Wall -Wextra` in build flags | 🔴 High | Trivial |
| M-1 | Unchecked `malloc` in codegen | 🟠 Medium | Small |
| M-2 | Half-initialised unit left in map on error | 🟠 Medium | Small |
| Q-2 | `DEBUG:` print left in `typecheck.c` | 🟠 Medium | Trivial |
| Q-3 | `ptr_cmp` violates comparator contract | 🟠 Medium | Trivial |
| TD-1 | Fixed-size buffers in `module_loader.c` | 🟠 Medium | Medium |
| TD-3 | `is_const_expr` dual semantics | 🟠 Medium | Medium |
| TD-5 | No recursion depth limit on module loading | 🟠 Medium | Small |
| M-3 | `arena_total_allocated` returns `int` | 🟡 Low | Trivial |
| Q-4 | `Slice.len` width mismatch | 🟡 Low | Small |
| Q-5 | Non-inline statics in headers | 🟡 Low | Small |
| Q-6 | `parse_statements.c` monolith (2113 lines) | 🟡 Low | Large |
| TD-2 | Dummy module symbols in scope | 🟡 Low | Large |
| TD-4 | Scattered implicit cast logic | 🟡 Low | Medium |

---

*All file references are relative to the `compiler-v3/` root of the submitted archive.*

# compiler-v3 — Architectural & Design Analysis
**Scope:** Phase separation, type-driven design, hidden inefficiencies  
**Complement to:** compiler-v3-analysis.md (safety/memory/technical debt)

---

## 1. Phase Separation — Where the Lines Blur

A well-separated compiler pipeline keeps each phase ignorant of the others. Sema produces a typed AST; codegen reads it. Here are the places where that contract breaks.

---

### PS-1 · Sema writes codegen-layout hints into the AST — **Structural**

```c
// typecheck_expr.c:603
init->field_index = (int)j;  // Store the resolved index for Codegen

// typecheck_expr.c:898
member_expr->field_index = 1; // Index 1 is the 'len' in the { ptr, len } fat pointer struct
```

The second comment is the clearest violation: sema knows that `T[]` is laid out in LLVM as `{ T*, i64 }` and that `len` is at index 1. That is a codegen representation detail. Sema is computing the struct field offset for a fat pointer that doesn't exist yet — it only becomes a struct when `get_llvm_type` runs.

The `field_index` field on `AstMemberExpr` and `AstFieldInit` is annotated "Resolved at Sema, used by Codegen" in `ast.h`. The annotation is honest, but the dependency is wrong. If the fat-pointer layout ever changes (say, swapping to `{ i64, T* }`), both sema and codegen must be updated.

**Better model:** Codegen resolves field indices itself from the canonical `Type*`. Since types are interned and pointer-identical, a `struct_field_index(type, name)` call in codegen is O(n) and always correct regardless of representation changes.

---

### PS-2 · Array-to-slice decay is implemented twice, in two different forms — **Duplication + Divergence Risk**

In sema, `type_can_implicit_cast` (rule 2) allows `T[N]` → `T[]` and triggers `insert_cast` on the argument. This puts a `AST_CAST` node into the AST.

In codegen, `codegen_expr_call` has a separate special branch:

```c
// codegen_call.c:143
} else if (arg_node->type->kind == TYPE_ARRAY && arg_node->type->as.array.size_known
        && param_type->kind == TYPE_ARRAY && !param_type->as.array.size_known) {
    // Decay to fat pointer — manually builds slice struct
    LLVMValueRef slice_val = LLVMGetUndef(slice_ty);
    slice_val = LLVMBuildInsertValue(ctx->builder, slice_val, ptr, 0, "slice_ptr");
    slice_val = LLVMBuildInsertValue(ctx->builder, slice_val, len, 1, "slice_len");
```

This branch fires on arguments that *weren't* wrapped in a cast node by sema — either because the implicit cast path wasn't triggered for that call site, or because this is a fallback. There is also `codegen_materialize_slice` in `codegen_ops.c` for cast nodes, and the inline fat-pointer build in `codegen_lvalue.c` for subscript targets. Three different places, all materialising fat pointers, none sharing code.

---

### PS-3 · `print`/`println` have split identities across the pipeline — **Inconsistent Intrinsic Model**

There are two kinds of intrinsic in this compiler. The `@`-prefix kind (`@alloc`, `@free`) are parsed as `AST_INTRINSIC` nodes, type-checked in `check_intrinsic`, and generated in `codegen_expr_intrinsic`. The name-based kind (`print`, `println`) are registered as `SYMBOL_VALUE_INTRINSIC` in the symbol table but are handled entirely differently in both phases:

- In sema (`check_call_expr`): any call to a `SYMBOL_VALUE_INTRINSIC` symbol gets `t_void` blindly and skips argument type checking — all args are checked with `check_expression(ctx, scope, arg, NULL)` (no type hint). This means `println(42)` and `println("hello")` get the same treatment and no type mismatch is possible.
- In codegen (`codegen_expr_call`): detected by **string comparison** — `memcmp(s->ptr, "print", 5)`. The `INTRINSIC_PRINT` enum value set on the symbol during registration is never read in codegen.

The `IntrinsicKind` enum exists precisely to avoid string matching in later phases. It's being set but not used for the most common intrinsics.

Additionally, `println()` with no arguments generates a newline by hardcoding `print_newline` — but that function name is also hardcoded in two separate places (`codegen_call.c:60` and `:96`).

---

### PS-4 · `resolve_ast_type` calls `check_expression` for member-type paths — **Sema re-entry**

```c
// typecheck.c:185
if (node->node_type == AST_MEMBER_EXPR) {
    // Resolve member expression as a type path
    check_expression(ctx, scope, node, NULL);
    Symbol *sym = node->data.member_expr.symbol;
    ...
}
```

When a type annotation is written as `std.mem.Allocator`, the parser produces an `AST_MEMBER_EXPR` in the type position. To resolve this to a `Type*`, sema calls the full expression checker on it. This means:

1. Type resolution can trigger expression side-effects (symbol lookups, error reporting, `is_const_expr` being reset to 0).
2. The same `AST_MEMBER_EXPR` node gets expression-checked during the signature pass, then checked again when it appears as a parameter type during body checking.
3. The type and the expression checker share state through `expr->type`, which makes the order of resolution matter in ways that aren't obvious.

Type paths should be a distinct syntactic and semantic category from value-expression paths.

---

### PS-5 · The pass architecture uses a "pass flag" anti-pattern — **Structural**

Four functions — `resolve_program_structs`, `resolve_program_globals`, `resolve_program_functions`, `resolve_program_aliases` — each contain:

```c
if (ctx->current_pass == 1) {
    // Register names
} else if (ctx->current_pass == 3) {
    // Resolve types
}
```

Each function is actually two functions glued together by an integer switch. The caller sets `ctx->current_pass` before each call:

```c
ctx->current_pass = 1;
resolve_program_structs(ctx, ...);
// ... then later
ctx->current_pass = 3;
resolve_program_structs(ctx, ...);
```

This is the "flag argument" anti-pattern extended to a global integer. Any function that has a `TypeCheckContext*` can read or silently write `current_pass`, changing the behavior of every other resolve function. The `current_pass` field is effectively a global mode switch disguised as a context field.

**Cleaner design:** Split each function at the if/else:

```c
void register_struct_names(TypeCheckContext *ctx, Scope *scope);  // pass 1 behavior
void resolve_struct_bodies(TypeCheckContext *ctx, Scope *scope);  // pass 3 behavior
```

The call site becomes self-documenting and there's no shared state to corrupt.

---

### PS-6 · `check_expression` has no idempotency guard — **Redundant Work**

```c
// typecheck_expr.c:1028 — no early exit if already typed
Type* check_expression(TypeCheckContext *ctx, Scope *scope, AstNode *expr, Type *expected_type) {
    if (!expr) return NULL;
    Type *result_type = NULL;
    expr->is_const_expr = 0;   // ← reset unconditionally
    ...
```

`check_expression` re-runs from scratch on every call, including resetting `is_const_expr` to 0 before the check. Combined with PS-4, an `AST_MEMBER_EXPR` used as a type annotation gets fully expression-checked every time `resolve_ast_type` is called on it — once during the signature pass for the parameter, once when the function type is resolved for call sites, potentially more.

For a type like `std.mem.Allocator` used in 10 function parameters, the member chain `std → mem → Allocator` is walked 10 times during signature resolution. Adding an early exit `if (expr->type && !expected_type) return expr->type;` would eliminate most of this redundant work.

---

## 2. Type System Design — Structural Issues

---

### TS-1 · `TYPE_ARRAY` represents two incompatible representations — **Core Design**

`TYPE_ARRAY` with `size_known=true` is a value-type fixed-size array (stored contiguously, passed by pointer, layout `[N x T]` in LLVM). `TYPE_ARRAY` with `size_known=false` is a fat-pointer slice (stored as a struct `{ T*, i64 }`, passed by value).

These are not the same type at all — they have different sizes, different copy semantics, different calling conventions, and different field access patterns. Yet every switch on `type->kind` that handles `TYPE_ARRAY` must internally branch on `size_known` to determine which representation applies:

- `codegen_types.c:83` — two LLVM types from one TypeKind
- `codegen_lvalue.c:47` and `:58` — two entirely different GEP strategies
- `codegen_call.c:143` — the decay branch
- `type_is_address_only` — returns true for `size_known`, false otherwise

**Better design:** `TYPE_SLICE` as a separate TypeKind. Every switch becomes unambiguous, the decay cast becomes a cross-kind conversion (like pointer-to-void), and the fat-pointer layout question is isolated to the `TYPE_SLICE` codegen path.

---

### TS-2 · `PRIM_STR` is not a primitive — **Misclassification**

`str` lives as `PRIM_STR` inside `TYPE_PRIMITIVE`. At the LLVM level it maps to `i8*`. Subscripting `s[i]` returns `t_char`. The implicit cast `str → *char` was just added. It walks and quacks like a pointer.

The consequence: every place in the type system that checks `type->kind == TYPE_POINTER` misses `str`. Code that wants to check "is this pointer-like?" must explicitly test `|| (type->kind == TYPE_PRIMITIVE && type->as.primitive == PRIM_STR)`. That check appears in at least `codegen_lvalue.c`, `codegen_ops.c`, and `check_subscript`. Anywhere it's missing, `str` silently falls through or ICEs.

**Better design:** `TYPE_STR` as its own TypeKind (or just represent it as `*char` in the type system and alias `str` to it). Keeping it as a pseudo-primitive means the "is indexable?" check, the "can take address of?" check, and any future "is this utf8?" check all need to know about this special case.

---

### TS-3 · `PRIM_VOID` and `TYPE_VOID` represent the same thing — **Redundancy**

`type.h` has both `TYPE_VOID` as a `TypeKind` and `PRIM_VOID` as a `PrimitiveKind`. In `get_llvm_type`, both map to `LLVMVoidTypeInContext`:

```c
case TYPE_VOID: res = LLVMVoidTypeInContext(ctx->context); break;
// ...
case PRIM_VOID: res = LLVMVoidTypeInContext(ctx->context); break;
```

The `TypeStore` pre-creates `t_void` (using `TYPE_VOID`) but `typestore_create` also calls `register_prim(ts, ids, "void", ...)` with `PRIM_VOID`. A function declared `fn foo() -> void` may end up with either variant depending on which resolution path was taken. Any equality check `ret_type == ctx->store->t_void` will miss the `PRIM_VOID` case if that was used.

---

### TS-4 · `TYPE_ENUM` is declared but inert — **Maintenance Trap**

`TypeKind` includes `TYPE_ENUM`. The associated `user` union member contains a `Symbol *decl_node` field (which should probably be `AstNode*`). No sema code handles `TYPE_ENUM`, no codegen handles it, and no switch has a case for it.

This is harmless now, but:
- Any `switch (t->kind)` without a default will generate no warning when `TYPE_ENUM` is eventually introduced, silently skipping the new case.
- The `user.decl_node` being typed `Symbol*` instead of `AstNode*` suggests this was started and abandoned mid-way.

Either remove it until enums are implemented, or add `ICE("TYPE_ENUM not yet implemented")` to every relevant switch default.

---

### TS-5 · `type_is_indirect` requires a `CodegenContext*` — **ABI knowledge locked in codegen**

```c
// codegen_types.c:42
bool type_is_indirect(CodegenContext *ctx, Type *t) {
    if (t->kind != TYPE_STRUCT) return false;
    LLVMTypeRef llvm_ty = get_llvm_type(ctx, t);
    return LLVMABISizeOfType(ctx->target_data, llvm_ty) > 16;
}
```

The calling convention decision (pass by value vs pointer) depends on struct layout, which requires `LLVMABISizeOfType`. This is fundamentally an ABI calculation and correctly lives in codegen. However, the 16-byte threshold is a magic number with no named constant and no comment explaining it's "2 × 64-bit register width for System V AMD64 ABI".

More importantly, there's no way for sema to know if a function it's checking will use sret (indirect return) without pulling in codegen. If sema ever needs to type-check sret behavior (e.g., for ABI-specific error reporting), it can't. Consider naming the constant:

```c
#define SRET_SIZE_THRESHOLD_BYTES 16  // System V AMD64: max 2 x 8-byte registers
```

---

## 3. Hidden Inefficiencies

---

### I-1 · `check_struct_literal` field resolution is O(n²) — **Performance**

```c
// typecheck_expr.c:596
for (size_t i = 0; i < lit_field_count; i++) {          // ← outer: each init field
    AstFieldInit *init = ...;
    for (size_t j = 0; j < defined_field_count; j++) {  // ← inner: all struct fields
        if (struct_type->as.struct_type.fields[j].name == init->name) { ...
```

For a struct with N fields initialised in-order, this is O(n²) pointer comparisons. Since field names are interned (`name` is `InternResult*`), pointer identity is already canonical — no string comparison needed. But the loop still runs. For large structs (e.g., the Allocator or a fat config struct), this is unnecessary.

Since struct literals require all fields and initialiser order matches field order (the `init->field_index` is resolved to the declaration order), this can be a single O(n) pass matching by position when field names are provided in order, with a fallback to a hashmap for out-of-order initialisation.

---

### I-2 · `resolve_function_decl` allocates then immediately frees a temporary `param_types` array — **Allocation Churn**

```c
// typecheck.c:327
if (param_count > 0) param_types = malloc(sizeof(Type*) * param_count);
// ... fill it ...
InternResult *res = intern_type(ctx->store, &proto);  // deep-copies params into arena
free(param_types);   // immediately freed
```

The `intern_type` call deep-copies the params array into the arena. So `param_types` exists solely to pass the array to the interner, which immediately makes its own copy. This is an unnecessary heap round-trip for every function in the program.

The alternative is to allocate `param_types` directly from the arena, pass it, and let the interner decide whether to copy or reuse:

```c
Type **param_types = arena_alloc(ctx->store->arena, sizeof(Type*) * param_count);
```

The interner's `type_copy_func` would then detect the pointer already lives in the arena and could skip the copy (or the intern can be redesigned to take arena-backed input). At minimum, this eliminates one `malloc+free` per function declaration.

---

### I-3 · Deferred actions use a linear scan during implicit function return — **Unnecessary**

```c
// codegen_decl.c:162
for (int i = (int)ctx->deferred_actions->count - 1; i >= 0; i--) {
    AstNode *body = *(AstNode**)dynarray_get(ctx->deferred_actions, i);
    codegen_statement(ctx, body);
}
ctx->deferred_actions->count = 0;
```

This is at the function-level implicit return. But `codegen_stmt.c` already does the same iteration for block-level defer:

```c
// codegen_stmt.c:32
for (int i = ...; i >= (int)previous_defer_count; i--) {
    ...
    ctx->deferred_actions->count = previous_defer_count;
}
```

The block-level code correctly restores count to `previous_defer_count`. The function-level code resets to 0. If there are nested blocks, the function-level path might re-execute defers that the block-level path already ran — or defers registered in an inner block that has already been exited. This is likely correct today because the block-level code reduces `count` before the function-level code sees it, but it's fragile: the deferred action stack is shared and both levels modify it. A per-function deferred action list would make the ownership unambiguous.

---

### I-4 · `codegen_stmt.c` manually re-implements boolean coercion — **Duplication**

```c
// codegen_stmt.c: every if/while/for condition
LLVMTypeRef cond_ty = LLVMTypeOf(cond);
if (LLVMGetTypeKind(cond_ty) == LLVMPointerTypeKind) {
    cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstNull(cond_ty), "cond");
} else if (LLVMGetTypeKind(cond_ty) == LLVMIntegerTypeKind && LLVMGetIntTypeWidth(cond_ty) > 1) {
    cond = LLVMBuildICmp(ctx->builder, LLVMIntNE, cond, LLVMConstInt(cond_ty, 0, 0), "cond");
} else if (LLVMGetTypeKind(cond_ty) == LLVMFloatTypeKind || ...) {
    cond = LLVMBuildFCmp(ctx->builder, LLVMRealUNE, cond, LLVMConstNull(cond_ty), "cond");
}
```

This pattern appears separately for `if`, `while`, and `for` conditions. Extract it:

```c
static LLVMValueRef coerce_to_bool(CodegenContext *ctx, LLVMValueRef val) { ... }
```

---

### I-5 · `@alloc`/`@free` argument index calculation is duplicated across sema and codegen — **Fragile**

```c
// typecheck_expr.c (check_intrinsic):
AstNode *type_arg = *(AstNode**)dynarray_get(node->data.intrinsic.args, 0);
if (arg_count == 3) { /* first arg is type hint */ }

// codegen_expr.c (codegen_expr_intrinsic):
AstNode *allocator_arg = *(AstNode**)dynarray_get(args, args->count == 3 ? 1 : 0);
AstNode *count_arg     = *(AstNode**)dynarray_get(args, args->count == 3 ? 2 : 1);
```

The "is 3-arg form?" logic is independently re-implemented in both sema and codegen. If the calling convention for `@alloc` changes (say, adding a 4th arg), both sites need updating separately. Sema should annotate the resolved arg indices onto the `AST_INTRINSIC` node once, and codegen should read them.

---

### I-6 · `scope_lookup_symbol` re-scans `depth > 1` logic on every lookup — **Minor**

```c
// scope.c:113
if (current->depth > 0 && !current->unit) {
    // local scope, visible
}
```

The depth check exists to distinguish function-body scopes from module global scopes. Using `depth > 0` is fragile because it depends on how deep the scope chain is at any given point. The `unit` pointer provides a better signal: if a scope has no associated unit, it's an inner/function scope; if it does, it's a module global scope. The logic already uses `current->unit` but combines it with the depth check redundantly. A single `scope->is_local` boolean set at creation would be clearer and faster.

---

## 4. Summary Table

| ID | Issue | Category | Impact |
|---|---|---|---|
| PS-1 | Sema writes LLVM layout hints (`field_index`) into AST | Phase bleed | Medium |
| PS-2 | Array→slice decay in sema (insert_cast) AND codegen (manual InsertValue) | Duplication | Medium |
| PS-3 | `print`/`println` split between symbol kind and string matching | Inconsistency | Low |
| PS-4 | `resolve_ast_type` calls `check_expression` for member-type paths | Sema re-entry | Medium |
| PS-5 | Pass counter as mutable public field — multi-behavior functions | Anti-pattern | Medium |
| PS-6 | `check_expression` no idempotency — repeated full re-checks | Performance | Low |
| TS-1 | `TYPE_ARRAY` represents both fixed arrays and fat-pointer slices | Core design | High |
| TS-2 | `PRIM_STR` is not a primitive — it's a `*char` alias | Misclassification | Medium |
| TS-3 | `PRIM_VOID` and `TYPE_VOID` are redundant | Redundancy | Low |
| TS-4 | `TYPE_ENUM` declared and inert — silent miss in future switches | Trap | Low |
| TS-5 | `type_is_indirect` threshold magic number, no named constant | Clarity | Low |
| I-1 | O(n²) struct literal field resolution | Performance | Low |
| I-2 | `resolve_function_decl` malloc+free for param array that's immediately copied | Churn | Low |
| I-3 | Deferred action stack shared/modified at both block and function level | Fragile | Low |
| I-4 | Boolean coercion for conditions re-implemented per statement type | Duplication | Low |
| I-5 | `@alloc` arg-index logic duplicated in sema and codegen | Fragile | Low |
| I-6 | Scope depth check redundant alongside `unit` pointer | Minor | Low |

The two issues worth prioritising above the others are **TS-1** (the array/slice unification is load-bearing for every future feature involving array types) and **PS-5** (the pass flag anti-pattern makes the signature resolution pass hard to reason about and extend). Both have clear, mechanical fix paths.