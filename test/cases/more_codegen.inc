CODEGEN_EXIT("array_ptr_math", "fn main() -> i32 { arr: i32[2] = {10, 20}; p: *i32 = &arr[0]; if (*p != 10) { return 1; } return 0; }", 0)
CODEGEN_EXIT("slice_from_struct", "struct S { a: i32[3]; } fn main() -> i32 { s: S = S{ a: {1, 2, 3} }; sl: i32[] = s.a; return sl[1]; }", 2)
CODEGEN_EXIT("recursive_fn_ptr", "fn f(n: i32) -> i32 { if (n == 0) { return 42; } return f(n - 1); } fn main() -> i32 { return f(5); }", 42)
