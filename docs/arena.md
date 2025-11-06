# Arena allocator

## What it is
A simple bump allocator:
- One contiguous memory region (or a chain of blocks).
- Pointer (offset) moves forward on each allocation.
- No per-allocation free; all memory reclaimed at arena_destroy.

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
- arena_create(capacity)
- arena_alloc(arena, size)
- arena_calloc(arena, size)
- arena_destroy(arena)

## Why use it
A memory arena is a pre-allocated block of memory used for fast, efficient allocation of many small objects or strings. Instead of calling malloc() repeatedly (which incurs overhead and fragmentation), the arena allocates  memory linearly from its internal buffer. This is particularly useful in compilers or lexers where many short-lived objects (like tokens or identifiers) need to be allocated quickly. This entire block can be freed at once and thus idividual objects within this block don't need to be freed. This is especially usefull for recursive structures like an AST. Else on the root you would need to recurse down the entire AST freeing each node one by one. Now you simply free the arena in which the AST is located and thus it becomes 0(1).

| Need | Arena advantage |
|------|------------------|
| Fast, predictable alloc | Single pointer increment |
| Batch lifetime | Free everything at once |
| Low fragmentation | Contiguous linear growth |
| Simplicity | No complex metadata, no free lists |

## Typical usage
```c
Arena *a = arena_create(1 << 20);
char *buff = arena_alloc(a, len);
memcpy(buf, data, len);
return buff;
```




