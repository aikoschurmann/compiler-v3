# Parsing

[← Back to docs index](./README.md)

## On this page
- [What it is](#what-it-is)
- [Core data structures](#core-data-structures)
- [Core operations](#core-operations)
- [Interner integration](#interner-integration)
- [Spans and errors](#spans-and-errors)
- [Typical usage](#typical-usage)
- [Error handling](#error-handling)
- [Performance notes](#performance-notes)
- [Cross references](#cross-references)

## What it is
The parser consumes tokens and produces an Abstract Syntax Tree (AST). It’s a recursive‑descent parser using lookahead and arena‑allocated nodes for fast construction and O(1) teardown.

## Core data structures
Parser state and errors (from [`include/parser.h`](../include/parser.h)):
```c
typedef struct {
  DynArray   *tokens;   /* DynArray of Token (borrowed) */
  size_t      current;  /* next token index to consume */
  size_t      end;      /* tokens.count */
  char       *filename; /* filename in arena */
  Arena      *arena;    /* arena owning parser/filename/messages */
} Parser;

typedef struct {
  char     *message;  /* message in arena */
  Token    *token;    /* offending token (nullable) */
  Parser   *p;        /* parser where error occurred */
  int      use_prev_token; /* use previous token for location */
} ParseError;
```

Key AST shapes (from [`include/ast.h`](../include/ast.h)):
```c
typedef enum { /* …see ast.h… */ AST_IDENTIFIER, AST_FUNCTION_DECLARATION, AST_PARAM, AST_TYPE, /* … */ } AstNodeType;

typedef struct { InternResult *name_rec; } AstIdentifier;

typedef struct {
  AstNode *return_type;    /* AST_TYPE */
  InternResult *name_rec;  /* interned function name */
  DynArray *params;        /* AstParam nodes */
  AstNode *body;           /* AstBlock */
} AstFunctionDeclaration;

typedef struct {
  int name_idx;            /* interned dense index for parameter; -1 if anonymous */
  AstNode *type;           /* AST_TYPE */
} AstParam;

typedef enum { AST_TYPE_NAME, AST_TYPE_PTR, AST_TYPE_ARRAY, AST_TYPE_FUNC } AstTypeKind;
typedef struct AstType {
  AstTypeKind kind;
  Span span;
  union {
    struct { InternResult *rec; } base;               /* name */
    struct { AstNode *target; } ptr;                  /* *T */
    struct { AstNode *elem; AstNode *size_expr; } array; /* T[n] or T[] */
    struct { DynArray *param_types; AstNode *return_type; } func; /* (T..)->U */
  } u;
} AstType;
```

Notes:
- AST nodes carry `Span` for precise diagnostics and a `Type*` field for later semantic info.
- Canonical names are stored via `InternResult*`/dense indices from the [interner](interner.md).
- Node lists use [DynArray](dynarray.md).

## Core operations
Public API (from `include/parser.h` and `include/parse_statements.h`):
- Create/free: `parser_create`, `parser_free`.
- Token access: `current_token`, `peek`.
- Advance/consume: `parser_advance`, `consume`, `parser_match`.
- Entry points: `parse_program`, `parse_declaration`, `parse_statement`, `parse_block`, `parse_expression`, `parse_initializer_list`, `parse_type`, `parse_type_atom`, `get_base_type`, `parse_function_type`.
- Expression precedence: `parse_logical_or`, `parse_logical_and`, `parse_equality`, `parse_relational`, `parse_additive`, `parse_multiplicative`, `parse_unary`, `parse_postfix`, `parse_primary`, `parse_assignment`.
- Lists: `parse_parameter_list`, `parse_argument_list`.

Creation pattern:
- Nodes are allocated in an `Arena`; attach spans from token ranges; identifier fields use canonical interner records from `Token.record`.

## Interner integration
- Parser reuses the lexer’s canonical identifier record (`Token.record`) directly:
  - `AstIdentifier.name_rec`, `AstFunctionDeclaration.name_rec`.
  - `AstParam.name_idx` stores dense indices when useful.
  - `AstType.u.base.rec` holds interned type names.


## Spans and errors
- Use token spans for precise highlights; for composed nodes, use `span_join(lhs, rhs)`.
- Construct errors with `create_parse_error` and print with `print_parse_error`.
- Error printers render source excerpts using filename and span (see `file.c`).

## Typical usage
High‑level flow:
```c
Parser *p = parser_create(tokens, filename_in_arena, arena);
ParseError err = {0};
AstNode *program = parse_program(p, &err);
if (!program) { print_parse_error(&err); /* handle error */ }
/* optionally: print_ast(program, 0, KW_I, ID_I, STR_I); */
parser_free(p);
```

## Performance notes
- Arena allocation makes node creation cheap and teardown O(1).
- Re‑use canonical identifier pointers to avoid string compares.
- Keep token access branch‑light; avoid copying tokens.

## Cross references
- [lexing.md](lexing.md) – source of tokens and canonical identifier records.
- [arena.md](arena.md) – fast allocation for AST nodes and tables.
- [dynarray.md](dynarray.md) – variable‑length lists of nodes/params.
- [hashmap.md](hashmap.md) – scopes and symbol tables.
- [interner.md](interner.md) – canonical names and dense handles.