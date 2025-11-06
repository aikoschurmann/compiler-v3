# Simple Compiler (In progress 🙂)

A small, fast C implementation of a custom programming language.  
Current pipeline: **File load → Lexing → (Token dump / Lex benchmark optional)**.

This README focuses on the lexer’s design and the performance-minded choices I made — short and practical.

---

## Build
```sh
make        # builds executable (default target)
make clean
```
Requires a POSIX environment (tested on macOS) and a C compiler supporting C11 or later.

---

## Running
```
Usage: ./out/compiler <file> [options]
Options:
  --tokens            Print all tokens
  --time              Print how long lexing took (single run)
  --stats             Print file size and MB/s throughput (single run)
  --bench N           Run N iterations and print benchmarks
  --warmup N          Run N warm-up iterations before measuring (default: 2)
  --keep-lexer        Reuse the same lexer/arena across runs (reduces alloc noise)
  --csv               Emit CSV (run_index,seconds,MBps,tokens) for measured runs
```
Use `--bench` with `--warmup` and `--keep-lexer` to get stable measurements (warmups reduce JIT / cache noise; reusing lexer/arena avoids repeated allocations).

---

## Core components (concise)
- **Lexer**: single-pass, hand-written scanner over a buffer (`cur` / `end` pointer-based).
- **Token storage**: `DynArray` (reserves an initial capacity to reduce reallocations).
- **Interning**: Dense arena-backed interner for identifiers.
- **Memory**: arena allocator for lexer allocations (fast bulk alloc / free).
- **Slices**: tokens use `Slice { ptr, len }` pointing into the original source buffer — no `strdup`.

---

## Key design & performance choices (why it’s fast)
- **Pointer-based scanning**: uses `cur`/`end` pointers and pointer arithmetic rather than index-bound checks on every character. Fewer instructions per character.
- **Single-peek usage**: code peeks the next char exactly when needed (e.g., `++`, `+=`) to minimize branch work and redundant checks.
- **Advance updates line/col once**: `lexer_advance` increments `pos`, and updates `line`/`col` inline — keeps location bookkeeping cheap and local.
- **No unnecessary allocations**: tokens store `Slice` referencing the original buffer; identifiers are interned into an arena (no per-identifier malloc), dramatically reducing allocation overhead and fragmentation.
- **Pre-interned keywords + `intern_peek`**: keywords are pre-populated; `intern_peek` checks keywords without inserting or allocating accidentally, giving O(1) keyword→token mapping without polluting the identifier table.
- **Reserved token buffer**: `dynarray_reserve(INITIAL_TOKEN_CAPACITY)` reduces costly reallocs for small/medium files.
- **Arena lifetime semantics**: using an arena allows fast allocation and cheap reset — useful for repeated lexing runs / benchmarks. (later in AST will make freeing very easy instead of needing to do it recursively)

---

## Behavioural notes & trade-offs
- **Slices point into the source buffer**: the source must remain valid as long as tokens are used. This avoids copies but couples lifetime management (Thats why we intern keywords).
- **Interners survive `lexer_reset`**: `lexer_reset` reuses keywords and previously interned identifiers to reduce noise; intern tables are not cleared on reset.
- **Limited parsing of literals**: number parsing handles basic ints/floats (no exponents or hex yet). String/char handling supports escapes but does not perform full validation or normalization.
- **ASCII-focused**: character classification uses `ctype` and treats `_` as alpha — Unicode identifier support is not implemented.
- **Error reporting**: lexer returns `TOK_UNKNOWN` for some malformed inputs (e.g., unterminated string/char) — error messaging is minimal by design so far.

---

## Benchmarking tips
- Use `--warmup 2` (or more) to prime caches and get stable numbers.
- Use `--keep-lexer` to avoid repeated arena and interner allocations when benchmarking multiple runs — this reduces measurement noise caused by allocator churn.
- For CSV output and automated runs, combine `--bench` + `--csv` to collect machine-readable results.

---

## Where to look in the code
- `lexer.c` — pointer scanning, token emission, whitespace/comment skipping
- `dense_arena_interner.*` — interning strategy and metadata usage (keywords store `TokenType` in `meta`)
- `dynamic_array.*` — token storage
- `arena.*` — fast allocator used across lexer + interner

---
