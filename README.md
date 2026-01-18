# Simple Compiler (Work in progress)

A small, fast compiler front‑end written in C. Current pipeline:
File → Lexing → Parsing → Semantic analysis (type resolution) → Report

This README gives a practical overview: how to build and run, what’s implemented, where things live, and where to read more.

---

## Quick start

Build:
```sh
make
```

Run on the sample input with a useful set of flags:
```sh
./out/compiler ./input/test.txt --ast --types --time
```

Clean:
```sh
make clean
```

Requirements: POSIX environment (tested on macOS) and a C11 (or newer) compiler.

---

## CLI options
```
Usage: ./out/compiler <file> [options]
Options:
  -t, --tokens    Print all tokens
  -a, --ast       Print the parsed AST (after parsing)
  -y, --types     Print type store dump (interned types)
  -T, --time      Print lex/parse timing and throughput
  -h, --help      Show this help
  -v, --version   Print version and exit
```

---

## What’s implemented
- Hand‑written lexer (single pass over a character buffer)
- Token stream stored in a DynArray
- Dense arena‑backed interner for identifiers/keywords/strings
- Recursive‑descent parser that builds an arena‑allocated AST
- Semantic analysis: type resolution + interning, scope setup
- Pretty benchmarking report (timings, memory, throughput)

---

## Why it’s fast (highlights)
- Pointer‑based scanning in the lexer; minimal branching.
- No per‑token heap allocations: tokens hold Slice views into the source.
- Pre‑interned keywords, and O(1) identifier canonicalization.
- Arena allocation everywhere for cheap creation and O(1) teardown.
- Reserved token capacity to avoid frequent resizes.

---

## Project layout
```
.
├── include/           # Public headers
├── src/               # Sources (lexer, parser, driver, helpers)
├── docs/              # Documentation (start at docs/README.md)
├── input/             # Sample inputs (test.txt)
├── obj/               # Object files (generated)
└── out/               # Compiled binary (generated)
```

Key modules:
- Lexer: `lexer.*`
- Parser: `parser.*`, `parse_statements.*`, `ast.*`
- Interner: `dense_arena_interner.*`
- Containers: `dynamic_array.*`, `hash_map.*`
- Memory: `arena.*`
- CLI/metrics: `cli.*`, `metrics.*`
- Types (preview): `type.*`, `scope.*`, `type_print.*`, `type_report.*`

---

## Compilation pipeline (at a glance)
1) Read file into memory.
2) Lex: produce tokens with Slice+Span and an InternResult* for identifiers.
3) Parse: build an AST (arena‑allocated, spans preserved, canonical identifiers).
4) Semantic analysis: resolve types, build scopes, and intern type signatures.
5) Report: optional timing and memory summary.

Notes:
- `--types` prints the type store dump.
- `--ast` prints the parsed AST before semantics.

---

## Pipeline example
Input (`input/test.txt`):
```plaintext
fn mul(a: i64, b: i64) -> i64 {
    return a * b;
}
```

Tokens:
```plaintext
│   1:1   │ FN            │ 'fn'
│   1:4   │ IDENTIFIER    │ 'mul'
│   1:7   │ LPAREN        │ '('
│   1:8   │ IDENTIFIER    │ 'a'
│   1:9   │ COLON         │ ':'
│   1:11  │ I64           │ 'i64'
│   1:14  │ COMMA         │ ','
│   1:16  │ IDENTIFIER    │ 'b'
│   1:17  │ COLON         │ ':'
│   1:19  │ I64           │ 'i64'
│   1:22  │ RPAREN        │ ')'
│   1:24  │ ARROW         │ '->'
│   1:27  │ I64           │ 'i64'
│   1:31  │ LBRACE        │ '{'
│   2:5   │ RETURN        │ 'return'
│   2:12  │ IDENTIFIER    │ 'a'
│   2:14  │ STAR          │ '*'
│   2:16  │ IDENTIFIER    │ 'b'
│   2:17  │ SEMICOLON     │ ';'
│   3:1   │ RBRACE        │ '}'
│   3:2   │ EOF           │ (no-lexeme)
```

AST:
```plaintext
Program [1:1-3:2]
└── FunctionDeclaration [1:1-3:2]
│   ├── name: 'mul' (I-index:0)
│   ├── return_type:
│   │   ├── Type
│   │   │   ├── kind: NamedType [1:27-1:30]
│   │   │   └── type_name: 'i64' (K-index:10)
│   ├── parameters:
│   │   ├── Parameter [1:8-1:14]
│   │   │   ├── name: 'a' (index:1)
│   │   │   └── type:
│   │   │   │   └── Type
│   │   │   │   │   ├── kind: NamedType [1:11-1:14]
│   │   │   │   │   └── type_name: 'i64' (K-index:10)
│   │   └── Parameter [1:16-1:22]
│   │   │   ├── name: 'b' (index:2)
│   │   │   └── type:
│   │   │   │   └── Type
│   │   │   │   │   ├── kind: NamedType [1:19-1:22]
│   │   │   │   │   └── type_name: 'i64' (K-index:10)
│   └── body:
│   │   └── Block [1:31-3:2]
│   │   │   └── ReturnStatement [2:5-2:18]
│   │   │   │   └── expression:
│   │   │   │   │   └── BinaryExpression [2:12-2:17]
│   │   │   │   │   │   ├── operator: '*'
│   │   │   │   │   │   ├── left:
│   │   │   │   │   │   │   ├── Identifier [2:12-2:13]
│   │   │   │   │   │   │   │   └── name: 'a' (I-index:1)
│   │   │   │   │   │   └── right:
│   │   │   │   │   │   │   └── Identifier [2:16-2:17]
│   │   │   │   │   │   │   │   └── name: 'b' (I-index:2)
```

Type store dump (interned types):
- `--types` prints the interned type table and any resolved function signatures.

---

## Documentation
Start at the docs index: `docs/README.md`
- `docs/lexing.md` — tokens, slices, spans, interner integration
- `docs/parsing.md` — recursive‑descent parser and AST shapes
- Infra references: `docs/interner.md`, `docs/dynarray.md`, `docs/hashmap.md`, `docs/arena.md`
- `docs/semantics.md` — planned

---

## Notes & trade‑offs
- Slices reference the original buffer; keep it alive while tokens/AST live.
- Grammar uses precedence functions for expressions (no left recursion).
- Error messages are improving; spans are preserved for good diagnostics.

