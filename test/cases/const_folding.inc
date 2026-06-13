SEMA_VALID("const_arith", "const X: i32 = (1 + 2) * 3; fn main() { x: i32 = X; }")
SEMA_VALID("const_bit", "const X: i32 = (1 << 5) | 1; fn main() { x: i32 = X; }")
SEMA_VALID("array_size_const", "const SZ: i32 = 10; fn main() { arr: i32[SZ]; }")
SEMA_ERROR("array_size_non_const", "fn main() { x: i32 = 10; arr: i32[x]; }", TE_NOT_CONST)
