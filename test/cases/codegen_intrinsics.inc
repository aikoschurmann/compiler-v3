// test/cases/codegen_intrinsics.inc

CODEGEN_OUTPUT("print_i32",
    "fn main() -> i32 {\n"
    "    print(42);\n"
    "    return 0;\n"
    "}", 0, "42")

CODEGEN_OUTPUT("println_bool",
    "fn main() -> i32 {\n"
    "    println(true);\n"
    "    return 0;\n"
    "}", 0, "true\n")

CODEGEN_EXIT("alloc_free_basic",
    "import std;\n"
    "fn main() -> i32 {\n"
    "    p: *i32 = @alloc(i32, std.heap.allocator, 1);\n"
    "    if (p == 0 as *i32) { return 1; }\n"
    "    *p = 100;\n"
    "    val: i32 = *p;\n"
    "    @free(std.heap.allocator, p);\n"
    "    return val;\n"
    "}", 100)

CODEGEN_EXIT("alloc_array",
    "import std;\n"
    "fn main() -> i32 {\n"
    "    p: *i32 = @alloc(i32, std.heap.allocator, 5);\n"
    "    p[0] = 10;\n"
    "    p[4] = 20;\n"
    "    val: i32 = p[0] + p[4];\n"
    "    @free(std.heap.allocator, p);\n"
    "    return val;\n"
    "}", 30)

CODEGEN_OUTPUT("print_struct",
    "struct Point { x: i32; y: i32; }\n"
    "fn main() -> i32 {\n"
    "    p: Point = Point { x: 10, y: 20 };\n"
    "    print(p);\n"
    "    return 0;\n"
    "}", 0, "{ x: 10, y: 20 }")
