// test/cases/codegen_std.inc

CODEGEN_EXIT("std_vec_push",
    "import std;\n"
    "import std.vec;\n"
    "fn main() -> i32 {\n"
    "    alloc: std.mem.Allocator = std.heap.allocator;\n"
    "    v: std.vec.Vec<i32>;\n"
    "    v.init(&alloc);\n"
    "    v.push(10);\n"
    "    v.push(20);\n"
    "    v.push(30);\n"
    "    val: i32 = v.get(1);\n"
    "    v.free();\n"
    "    return val;\n"
    "}", 20)

CODEGEN_EXIT("std_vec_pop",
    "import std;\n"
    "import std.vec;\n"
    "fn main() -> i32 {\n"
    "    alloc: std.mem.Allocator = std.heap.allocator;\n"
    "    v: std.vec.Vec<i32>;\n"
    "    v.init(&alloc);\n"
    "    v.push(10);\n"
    "    v.push(20);\n"
    "    val: i32 = v.pop();\n"
    "    v.free();\n"
    "    return val;\n"
    "}", 20)

CODEGEN_EXIT("std_mem_clone",
    "import std;\n"
    "fn main() -> i32 {\n"
    "    src: i32[3];\n"
    "    src[0] = 1; src[1] = 2; src[2] = 3;\n"
    "    alloc: std.mem.Allocator = std.heap.allocator;\n"
    "    alloc_ref: *std.mem.Allocator = &alloc;\n"
    "    dst: i32[] = alloc_ref.clone<i32>(src);\n"
    "    val: i32 = dst[2];\n"
    "    @free(alloc_ref, dst);\n"
    "    return val;\n"
    "}", 3)
