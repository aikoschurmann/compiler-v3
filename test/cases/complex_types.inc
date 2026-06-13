CODEGEN_EXIT("multi_dim_array", "fn main() -> i32 { arr: i32[2][3] = {{1,2,3},{4,5,6}}; return arr[1][1]; }", 5)
CODEGEN_EXIT("triple_ptr", "fn main() -> i32 { x: i32 = 42; p: *i32 = &x; pp: **i32 = &p; ppp: ***i32 = &pp; return ***ppp; }", 42)
CODEGEN_EXIT("nested_struct_array", "struct S { a: i32[2]; } fn main() -> i32 { s: S; s.a[1] = 10; return s.a[1]; }", 10)
CODEGEN_EXIT("deep_struct", "struct A { x: i32; } struct B { a: A; } struct C { b: B; } fn main() -> i32 { c: C; c.b.a.x = 7; return c.b.a.x; }", 7)
