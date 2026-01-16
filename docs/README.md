# Documentation Guide

## On this page
- [Getting started](#getting-started)
- [Recommended reading order](#recommended-reading-order)
- [Pipeline at a glance](#pipeline-at-a-glance)
- [Reference modules](#reference-modules)
- [Source-of-truth notes](#source-of-truth-notes)

## Getting started
- Build: see the root README for `make` targets.
- Run: `./out/compiler <file> [--tokens|--ast|--types|--time]`.
- Then follow the reading order below to connect code and docs.

## Recommended reading order
1) Lexing — tokens, slices, spans, and interner usage
  - [lexing.md](./lexing.md)
2) Parsing — AST construction with arena allocation and canonical identifiers
  - [parsing.md](./parsing.md)
3) Semantics & types — symbol tables, type interning, checking
  - [semantics.md](./semantics.md)
  - [scope.md](./scope.md)

Keep these infrastructure docs handy while reading the above:
- Interner — canonical keys, dense indices, and how intern() works
  - [interner.md](./interner.md)
- DynArray — variable-length arrays used for tokens and AST lists
  - [dynarray.md](./dynarray.md)
- HashMap — separate-chaining table used for lookups
  - [hashmap.md](./hashmap.md)
- Arena — fast bump allocator backing most allocations
  - [arena.md](./arena.md)

## Pipeline at a glance
- File load → Lexing → Tokens (with interned identifiers) → Parsing → AST
- Each token carries:
  - TokenType, Slice (view into source), Span (source range), InternResult* (for identifiers)
- AST nodes are arena-allocated; identifier/type names store interner records.

### Example
See the root README’s Pipeline example for tokens, AST, and type internment:
[../README.md#pipeline-example](../README.md#pipeline-example)

## Reference modules
- [include/token.h](../include/token.h) — Token, TokenType, Slice, Span
- [include/parser.h](../include/parser.h) — Parser state and ParseError helpers
- [include/ast.h](../include/ast.h) — AST node kinds and payloads
- [include/parse_statements.h](../include/parse_statements.h) — parse_* entry points and precedence chain
- [include/dense_arena_interner.h](../include/dense_arena_interner.h) — InternResult, DenseArenaInterner
- [include/dynamic_array.h](../include/dynamic_array.h) — DynArray API
- [include/hash_map.h](../include/hash_map.h) — HashMap API
- [include/arena.h](../include/arena.h) — Arena API

### Grammar snippets (BNF)
- Type-focused examples live in [`input/type_test.bnf`](../input/type_test.bnf).
- A full language grammar file (`input/lang.bnf`) is planned; for now, the parser code (`include/parse_statements.h`) reflects the authoritative grammar structure.

## Source-of-truth notes
- Headers under `include/` are authoritative for types and function signatures.
- Docs mirror those headers; if they diverge, prefer the headers and open an issue/PR to sync the docs.
