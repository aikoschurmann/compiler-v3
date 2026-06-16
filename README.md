# The Language

A statically-typed, procedural language with a focus on explicit memory control and zero hidden allocations. Syntax borrows from Rust and C while keeping things simple: every variable is declared with a type, every allocation is visible, and there is no garbage collector.

Source files use the `.tn` extension.

---

## Getting Started

### Prerequisites

- Clang
- LLVM
- Make

### Build the compiler

```bash
make          # builds both release and dev binaries
make test     # runs the test suite
```

### Compile and run a program

```bash
./out/compiler path/to/program.tn --run
```

---

## Language Tour

### Variables and Constants

Variables are declared with `name: Type = value`. Type annotations are always required.

```
x: i32 = 10;
pi: f64 = 3.14159;
name: *char = "hello";
flag: bool = true;
```

Constants are evaluated at compile time and can be used anywhere a literal is valid.

```
const MAX: i32 = 100;
const HALF_MAX: i32 = MAX / 2;  // constant folding
```

---

### Primitive Types

| Type    | Description                    |
|---------|--------------------------------|
| `i32`   | 32-bit signed integer          |
| `i64`   | 64-bit signed integer          |
| `f32`   | 32-bit floating-point          |
| `f64`   | 64-bit floating-point          |
| `bool`  | Boolean (`true` / `false`)     |
| `char`  | Single byte character          |
| `*T`    | Pointer to type `T`            |
| `*void` | Untyped pointer                |
| `void`  | No value (function return only)|

---

### Functions

```
fn add(a: i32, b: i32) -> i32 {
    return a + b;
}

fn greet(name: *char) -> void {
    print("Hello, ");
    println(name);
}
```

Functions can be passed as values using function pointer types:

```
fn apply(a: i32, b: i32, op: fn(i32, i32) -> i32) -> i32 {
    return op(a, b);
}

fn main() -> i32 {
    result: i32 = apply(10, 20, add);
    return result;  // 30
}
```

---

### Control Flow

**If / else**

```
if x > 0 {
    println("positive");
} else if x < 0 {
    println("negative");
} else {
    println("zero");
}
```

**While**

```
i: i32 = 0;
while (i < 10) {
    i = i + 1;
}
```

**For**

```
for (i: i32 = 0; i < 10; i += 1) {
    println(i);
}
```

**Break and continue**

```
while true {
    if done { break; }
    if skip { continue; }
}
```

---

### Structs and Methods

Structs group fields together. Methods are regular functions with the struct type as a name prefix; `self` is an explicit pointer parameter.

```
struct Point {
    x: f64;
    y: f64;
}

fn Point.scale(self: *Point, factor: f64) -> void {
    self.x = self.x * factor;
    self.y = self.y * factor;
}

fn main() -> i32 {
    p: Point = Point { x: 1.0, y: 2.0 };
    p.scale(3.0);
    // p.x == 3.0, p.y == 6.0
    return 0;
}
```

Struct fields initialise in any order, and structs can be nested:

```
struct Color { r: i32; g: i32; b: i32; }
struct Pixel { pos: Point; color: Color; }

px: Pixel = Pixel {
    pos: Point { x: 10.0, y: 20.0 },
    color: Color { r: 255, g: 0, b: 128 }
};
```

---

### Pointers

Take the address of a variable with `&` and dereference with `*`.

```
x: i32 = 42;
p: *i32 = &x;
*p = 100;       // x is now 100
```

Pointer-to-pointer:

```
pp: **i32 = &p;
val: i32 = **pp;  // 100
```

Null pointers use the `null` keyword or an explicit zero cast:

```
p: *Node = null;
if p == null { ... }
```

Pointer arithmetic is done through integer casts:

```
next: *i32 = ((p as i64) + 4) as *i32;
```

Auto-deref through a pointer works on struct member access — `p.field` is shorthand for `(*p).field`.

---

### Arrays

Fixed-size arrays:

```
nums: i32[5] = {1, 2, 3, 4, 5};
matrix: f64[3][3];  // multidimensional
```

The size can be inferred from the initialiser:

```
primes: i32[] = {2, 3, 5, 7, 11};  // becomes i32[5]
```

Arrays decay to pointers when taken by address:

```
p: *i32 = &nums[0];
```

---

### Casts

Use `as` to cast between numeric types, pointers, and mixed combinations. Casts are explicit — there are no silent narrowing conversions.

```
big: i64 = 0xFFFFFFFF0000000A;
small: i32 = big as i32;   // truncate

ratio: f64 = 7.9;
n: i32 = ratio as i32;     // truncate to 7

c: char = 'A';
code: i32 = c as i32;      // 65

raw: *void = &x as *void;  // pointer reinterpret
```

---

### Aliases

`alias` binds a new name to any existing symbol — a variable, function, struct, or type. The alias and the original refer to the same thing.

```
alias Vec2 = Point;                 // type alias
alias origin = default_point;      // variable alias
alias sum = add;                    // function alias

s: Vec2 = Vec2 { x: 0.0, y: 0.0 };
result: i32 = sum(1, 2);
```

---

### Defer

`defer` schedules a statement or block to run when the current scope exits, including on early returns. Deferred actions run in last-in, first-out order.

```
fn read_file() -> i32 {
    f: *File = open("data.txt");
    defer { close(f); }       // always runs, even on early return

    if f == null { return -1; }
    // ... work with f ...
    return 0;
}
```

Defer inside loops fires on each iteration:

```
for (i: i32 = 0; i < 3; i += 1) {
    defer { cleanup(i); }  // runs at the end of each loop body
    do_work(i);
}
```

---

### Modules and Imports

Code is split into modules. A module is a `.tn` file; its public declarations (marked `pub`) are visible to importers.

**Import the whole standard library:**

```
import std;

fn main() -> i32 {
    a: std.arena.Arena = std.arena.Arena.new(std.heap.allocator, 4096);
    defer { a.destroy(); }
    return 0;
}
```

**Import a specific sub-module:**

```
import std.mem;

alloc: std.mem.Allocator = std.heap.allocator;
```

**Import from a relative path:**

```
// project/utils.tn
pub fn clamp(x: i32, lo: i32, hi: i32) -> i32 { ... }

// project/main.tn
import .utils { clamp };

fn main() -> i32 {
    return clamp(150, 0, 100);  // 100
}
```

**Re-export:** mark an import `pub` to expose it to downstream modules.

```
pub import .mem;
pub import .heap;
```

---

### Memory Management

There is no implicit allocation. All heap memory goes through an `Allocator` value, which you pass explicitly. The standard library ships two ready-to-use allocators.

**Heap allocator** — wraps `malloc`/`free`:

```
import std;

fn main() -> i32 {
    p: *i32 = @alloc(i32, std.heap.allocator, 1);
    *p = 42;
    @free(std.heap.allocator, p);
    return 0;
}
```

**Arena allocator** — bump-pointer, freed all at once:

```
import std;
alias Arena = std.arena.Arena;

fn main() -> i32 {
    arena: Arena = Arena.new(std.heap.allocator, 4096);
    defer { arena.destroy(); }

    a: std.mem.Allocator = arena.get_allocator();

    node: *Node = @alloc(Node, a, 1);
    node.val = 99;
    // everything freed when arena.destroy() runs
    return 0;
}
```

**Allocating arrays:** pass a count as the third argument to `@alloc`.

```
buf: *i32 = @alloc(i32, std.heap.allocator, 64);
buf[0] = 1;
buf[63] = 2;
@free(std.heap.allocator, buf);
```

**Custom allocators** implement `std.mem.Allocator`:

```
import std.mem;

pub struct Allocator {
    ctx: *void;
    _alloc: fn(*void, i64) -> *void;
    _free:  fn(*void, *void) -> void;
}
```

Any struct with `ctx`, `_alloc`, and `_free` fields works as a drop-in allocator.

---

### FFI — Calling C Functions

Declare an external C function with `@link` and the symbol name. No body is needed.

```
@link("malloc")
fn malloc(size: i64) -> *void;

@link("free")
fn free(ptr: *void) -> void;

@link("printf")
fn printf(fmt: *char) -> i32;
```

The standard library's `std.libc` module provides ready-made bindings for the most common C functions.

---

## Standard Library

| Module            | Contents                                              |
|-------------------|-------------------------------------------------------|
| `std.heap`        | `allocator` — global heap allocator (malloc/free)     |
| `std.mem`         | `Allocator` struct and interface                      |
| `std.arena`       | `Arena` — bump-pointer allocator with bulk free       |
| `std.fixed_arena` | `FixedArena` — arena over a caller-supplied buffer    |
| `std.string`      | `Str` — non-owning string view with slice/compare ops |
| `std.math`        | `abs`, `min`, `max`, `clamp` for i32/i64/f64          |
| `std.io`          | `print` / `println`                                   |
| `std.libc`        | Bindings for malloc, free, printf, memcpy, strlen … |

Import `std` to get everything, or import individual sub-modules to keep dependencies explicit.