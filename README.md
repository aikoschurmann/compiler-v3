# Simple Compiler (In progress 🙂)

A small, fast C implementation of a custom programming language.  
Current pipeline: **File load → Lexing → (Token dump / Lex)**.

This README focuses on the lexer’s and parsing design and the performance-minded choices I made — short and practical.

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
  -t, --tokens    Print all tokens
  -a, --ast       Print the parsed AST (after parsing)
  -y, --types     Print type internment results
  -T, --time      Print lex/parse timing and throughput
  -h, --help      Show this help
  -v, --version   Print version and exit
```


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


## Where to look in the code
- `lexer.c` — pointer scanning, token emission, whitespace/comment skipping
- `dense_arena_interner.*` — interning strategy and metadata usage (keywords store `TokenType` in `meta`)
- `dynamic_array.*` — token storage
- `arena.*` — fast allocator used across lexer + interner

---

## Documentation
- Start here: `docs/README.md` (documentation guide and reading order)
  1. `docs/lexing.md` — tokens, slices, spans, interner integration
  2. `docs/parsing.md` — AST construction and parser APIs
  3. `docs/interner.md`, `docs/dynarray.md`, `docs/hashmap.md`, `docs/arena.md` — infrastructure references
  4. `docs/semantics.md` — planned
