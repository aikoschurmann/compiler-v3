// test/cases/codegen_pointers.inc

CODEGEN_EXIT("array_ptr_math", 
    "fn main() -> i32 {\n"
    "    arr: i32[2] = {10, 20};\n"
    "    p: *i32 = &arr[0];\n"
    "    if (*p != 10) { return 1; }\n"
    "    return 0;\n"
    "}", 0)

CODEGEN_EXIT("recursive_fn_ptr", 
    "fn f(n: i32) -> i32 {\n"
    "    if (n == 0) { return 42; }\n"
    "    return f(n - 1);\n"
    "}\n"
    "fn main() -> i32 {\n"
    "    return f(5);\n"
    "}", 42)

CODEGEN_EXIT("pointer_to_pointer_deref",
    "fn main() -> i32 {\n"
    "    x: i32 = 42;\n"
    "    p: *i32 = &x;\n"
    "    pp: **i32 = &p;\n"
    "    return **pp;\n"
    "}", 42)

CODEGEN_EXIT("null_pointer_init",
    "fn main() -> i32 {\n"
    "    p: *i32 = 0 as *i32;\n"
    "    if (p == 0 as *i32) { return 1; }\n"
    "    return 0;\n"
    "}", 1)

CODEGEN_EXIT("null_keyword_init",
    "fn main() -> i32 {\n"
    "    p: *i32 = null;\n"
    "    if (p == null) { return 1; }\n"
    "    return 0;\n"
    "}", 1)

// Array pass-by-value: mutation inside callee must NOT affect the caller's array
CODEGEN_EXIT("array_byval_no_mutation",
    "fn zero_first(arr: i32[3]) -> void {\n"
    "    arr[0] = 0;\n"
    "}\n"
    "fn main() -> i32 {\n"
    "    nums: i32[3] = {42, 2, 3};\n"
    "    zero_first(nums);\n"
    "    return nums[0] - 42;\n"  // must still be 42 -> returns 0
    "}", 0)

// Array pass-by-value: each recursive call gets its own independent copy
CODEGEN_EXIT("array_byval_recursive",
    "fn try_set(arr: i32[4], depth: i32) -> i32 {\n"
    "    arr[0] = depth;\n"
    "    if (depth == 0) { return arr[0]; }\n"
    "    return try_set(arr, depth - 1);\n"
    "}\n"
    "fn main() -> i32 {\n"
    "    data: i32[4] = {0, 0, 0, 0};\n"
    "    result: i32 = try_set(data, 3);\n"
    "    if (data[0] != 0) { return 1; }\n"  // caller unchanged
    "    if (result != 0) { return 2; }\n"   // deepest call returned 0
    "    return 0;\n"
    "}", 0)
