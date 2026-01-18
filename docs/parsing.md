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
The parser consumes tokens and produces an Abstract Syntax Tree (AST).

### Recursive‑descent (overview)
"Recursive‑descent" means: one function per grammar rule, calling other rule functions in a top‑down manner. Control flow follows the shape of the grammar instead of using tables. Each function:
- Peeks the current token (simple lookahead) and decides which production applies.
- Consumes the tokens belonging to that production.
- Allocates and returns an AST node (or NULL on error) from the arena.

Operator precedence is handled by a chain of functions (`parse_logical_or` → ... → `parse_primary`), each responsible for one precedence level and delegating to the next tighter level.

Benefits:
- Very readable: grammar shape maps directly to call graph.
- Easy to extend: add a new construct by adding a new parse_* function.
- Good for hand‑written, mid‑sized languages (< few hundred grammar rules).

Trade‑offs:
- Left‑recursive grammar rules must be rewritten (we use precedence functions for expressions).
- More manual error recovery than table‑driven parsers.

### Abstract Syntax Tree (AST)
The AST is a structured, loss‑filtered representation of the program:
- Nodes encode semantic categories (declaration, statement, expression, type) rather than raw token spelling.
- It strips layout trivia (comments/whitespace) but preserves source spans for diagnostics.
- Identifiers and type names store canonical interner records; pointer equality makes name comparisons O(1).
- Later phases (type checking, constant folding, code generation) annotate nodes (e.g. fill the `Type*` field, set `is_const_expr`, compute `const_value`).

Why not operate directly on tokens? Tokens are flat; the AST groups them into higher‑level constructs with hierarchy (e.g. a function has params, a body, a return type). This enables semantic passes to walk meaningful structures rather than re‑parsing token sequences.

Allocation: All nodes are arena‑allocated for fast creation and O(1) bulk teardown.

## Core data structures
Parser state and errors (from [`include/parsing/parser.h`](../include/parsing/parser.h)):
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

Key AST shapes (from [`include/parsing/ast.h`](../include/parsing/ast.h)):
```c
typedef enum { /* …see ast.h… */ AST_IDENTIFIER, AST_FUNCTION_DECLARATION, AST_PARAM, AST_TYPE, /* … */ } AstNodeType;

typedef struct { InternResult *intern_result; } AstIdentifier;

typedef struct {
  AstNode *return_type;    /* AST_TYPE */
  InternResult *intern_result;  /* interned function name */
  DynArray *params;        /* AstParam nodes */
  AstNode *body;           /* AstBlock */
} AstFunctionDeclaration;

typedef struct {
  int name_idx;            /* interned dense index for parameter; -1 if anonymous */
  AstNode *type;           /* AST_TYPE */
} AstParam;

typedef enum { AST_TYPE_PRIMITIVE, AST_TYPE_PTR, AST_TYPE_ARRAY, AST_TYPE_FUNC } AstTypeKind;
typedef struct AstType {
  AstTypeKind kind;
  Span span;
  union {
    struct { InternResult *intern_result; } base;     /* name */
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
Public API (from `include/parsing/parser.h` and `include/parsing/parse_statements.h`):
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
  - `AstType.u.base.intern_result` holds interned type names.


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