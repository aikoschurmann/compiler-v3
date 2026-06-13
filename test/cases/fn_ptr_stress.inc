SEMA_VALID("fn_ptr_var", "fn f(x: i32) {} fn main() { ptr: fn(i32) = f; }")
SEMA_VALID("fn_ptr_call", "fn f() -> i32 { return 42; } fn main() { ptr: fn()->i32 = f; x: i32 = ptr(); }")
SEMA_ERROR("fn_ptr_mismatch", "fn f(a: i32) {} fn main() { ptr: fn(i64) = f; }", TE_TYPE_MISMATCH)
SEMA_VALID("fn_ptr_param", "fn exec(p: fn()) { p(); } fn my_fn() {} fn main() { exec(my_fn); }")
