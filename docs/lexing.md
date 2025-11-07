# Lexing

## On this page
- [What it is](#what-it-is)
- [Core data structures](#core-data-structures)
- [Core operations](#core-operations)
- [Interner integration](#interner-integration)
- [Spans and slices](#spans-and-slices)
- [Typical usage](#typical-usage)
- [Error handling](#error-handling)
- [Performance notes](#performance-notes)
- [Cross references](#cross-references)

## What it is
The lexer turns raw source text into a stream of tokens with type, text, and source location. It’s a single pass over the input buffer with minimal branching and no per-token heap allocation.

## Core data structures
Defined in `include/token.h`:

```c
typedef struct {
    TokenType type;   // what kind of token
    Slice slice;      // points into source buffer
    Span span;        // position in source for error reporting
    InternResult *record;
} Token;
```

Notes:
- `slice` is a view into the source; no copy is made.
- `span` is used by error printers to render source excerpts.
- `record` is a pointer to an [interner](interner.md) record:
  - For keywords, points into the keyword interner (meta holds TokenType).
  - For identifiers, points into the identifier interner (canonical spelling).

Categories used in this compiler:
- Keywords: `fn, if, else, while, for, return, break, continue, const, true, false`.
- Types (as tokens): `i32, i64, bool, f32, f64, string, char`.
- Operators: single and multi-char (e.g., `+`, `+=`, `++`, `==`, `->`, `&&`, `||`).
- Punctuation: `(){}[],:;.|` and `.`.
- Literals: integer, float, string, char.
- Identifiers, comments, EOF, unknown.

## Core operations
The scanner walks a `const char*` buffer; it tracks `line` and `col` for spans.

High-level steps per token:
1. Skip whitespace and comments.
2. Capture start position for the token’s `Span` and start pointer for the `Slice`.
3. Dispatch on the current character:
   - Letters/underscore: scan identifier/keyword.
   - Digits: scan numeric literal (int or float).
   - Quote `'`/`"`: scan char or string literal (with escapes).
   - Operators/punctuation: handle longest-match multi-char tokens first (e.g., `==`, `!=`, `<=`, `>=`, `->`, `++`, `--`, `+=`, …) then fall back to single-char.
   - Otherwise: emit `TOK_UNKNOWN` for the character.
4. Compute `Slice{start_ptr, len}` and `Span{start_line/col .. end_line/col}`.
5. For identifiers: consult the keyword table; otherwise intern the identifier spelling and attach `record`.

## [Interner](interner.md) integration
Two interners are commonly used:
- `KW_I`: pre-seeded [interner](interner.md) for keywords. `meta` holds the `TokenType`.
- `ID_I`: general [interner](interner.md) for identifiers (stores one canonical copy per spelling).

Keyword setup (once):
```c
static struct { const char *kw; TokenType tt; } KW[] = {
  {"fn", TOK_FN}, {"if", TOK_IF}, {"else", TOK_ELSE}, {"while", TOK_WHILE},
  {"for", TOK_FOR}, {"return", TOK_RETURN}, {"break", TOK_BREAK}, {"continue", TOK_CONTINUE},
  {"const", TOK_CONST}, {"true", TOK_TRUE}, {"false", TOK_FALSE},
};
HashMap *kw_map = hashmap_create(64);
DenseArenaInterner *KW_I = intern_table_create(kw_map, arena, string_copy_func, slice_hash, slice_cmp);
for (size_t i = 0; i < sizeof(KW)/sizeof(KW[0]); ++i) {
  Slice s = { KW[i].kw, (uint32_t)strlen(KW[i].kw) };
  intern(KW_I, &s, (void*)(uintptr_t)KW[i].tt);
}
```

Identifier/keyword decision during scan:
```c
Slice ident = { start_ptr, (uint32_t)(cur - start_ptr) };
InternResult *hit = intern_peek(KW_I, &ident);
Token tok = {0};
tok.slice = ident;
tok.span = (Span){start_line, start_col, line, col};
if (hit) {
  tok.type = (TokenType)(uintptr_t)hit->entry->meta; // keyword
  tok.record = hit;                                  // canonical keyword record
} else {
  InternResult *id_rec = intern(ID_I, &ident, NULL); // canonical identifier record
  tok.type = TOK_IDENTIFIER;
  tok.record = id_rec;
}
```

Benefits:
- Avoids N× `strncmp` keyword chains, does a single hash+lookup.
- Pointer equality for names across parser and semantic passes (re-use `tok.record`).
- Zero copies for identifiers (slice points into input; canonical copy lives in the interner’s arena).

## Spans and slices
- `Slice` is a view into the source (`ptr + len`). Tokens avoid copying the source text.
- `Span` carries line/column for diagnostics; combine spans across tokens with `span_join` when needed.
- For pretty diagnostics, error printers use the filename + span to render source excerpts (see `file.c`).

## Typical usage
Minimal lexer harness (pseudo-code):
```c
char *src = read_file(path);
size_t src_len = strlen(src);

Arena *arena = arena_create(1024 * 1024);
Lexer *lexer = lexer_create(src, src_len, arena);

if (!lexer_lex_all(lexer)) {
        fprintf(stderr, "Lexing failed\n");
        lexer_destroy(lexer);
        arena_destroy(arena);
        free(src);
        return 1;
}

for (size_t i = 0; i < lexer->tokens->count; i++) {
    Token *tok = (Token*)dynarray_get(lexer->tokens, i);
    print_token(tok);
}

lexer_destroy(lexer);
arena_destroy(arena);
free(src);

```

## Error handling
- Unknown characters: emit `TOK_UNKNOWN` with a precise span; higher layers can decide severity.


## Performance notes
- Operate on the raw `char*` buffer; avoid temporary allocations.
- Prefer a longest-match table for multi-character operators.
- [Interner](interner.md) lookups are O(1) expected; avoid repeated `intern` on same canonical pointer by reusing `tok.record` downstream.

## Cross references
- [arena.md](arena.md) – allocation & lifetime of canonical strings.
- [hashmap.md](hashmap.md) – used by the interner for deduplication.
- [dynarray.md](dynarray.md) – token storage during lexing.
- [interner.md](interner.md) – canonicalization layer and keyword/identifier flow.