# Arena allocator

## What it is
A simple bump allocator:
- One contiguous memory region (or a chain of blocks).
- Pointer (offset) moves forward on each allocation.
 - No per-allocation free; reclaim everything at `arena_destroy`.

## Code datastructures
```c
typedef struct ArenaBlock {
    struct ArenaBlock *next; // Pointer to the next block
    size_t capacity;         // Total capacity of this block
    size_t used;             // Amount of memory used in this block
    char data[];             // Flexible array member for actual data
} ArenaBlock;

typedef struct Arena {
    ArenaBlock *blocks;      // Linked list of memory blocks
    size_t block_size;       // Size of each block (initial capacity)
} Arena;
```

## Core operations
- `arena_create(initial_capacity)` – create an arena with an initial block.
- `arena_alloc(arena, size)` – allocate uninitialized bytes (fast bump).
- `arena_calloc(arena, size)` – allocate zeroed bytes.
- `arena_destroy(arena)` – free all blocks at once.
- `arena_total_allocated(arena)` – total bytes currently allocated (diagnostics).

## Why use it
An arena allocates memory linearly, making many small allocations cheap and predictable. Instead of calling `malloc`/`free` repeatedly (overhead, fragmentation), you bump a pointer and keep going. This is ideal for compilers where lots of short‑lived objects (tokens, identifiers, AST nodes, types) are created during a pass. At the end, call `arena_destroy` and reclaim everything in O(1)—no per‑object frees or deep recursion to tear down an AST.

| Need | Arena advantage |
|------|------------------|
| Fast, predictable alloc | Single pointer increment |
| Batch lifetime | Free everything at once |
| Low fragmentation | Contiguous linear growth |
| Simplicity | No complex metadata, no free lists |

## Typical usage
```c
// Create an arena (1 MiB initial block)
Arena *a = arena_create(1u << 20);

// Allocate and copy a string (remember to add space for NUL if needed)
char *buf = arena_alloc(a, len + 1);
memcpy(buf, data, len);
buf[len] = '\0';

// Allocate a zeroed struct
typedef struct Node { int kind; struct Node *left, *right; } Node;
Node *n = arena_calloc(a, sizeof *n);
n->kind = 1; // use it

// ... use all arena-backed objects ...

// Tear down everything at once
arena_destroy(a);
```

