// test/cases/allocator_tests.inc

// Test invalid Allocator struct definitions
SEMA_ERROR("alloc_bad_fields", "struct Allocator { ctx: *i8; } fn main() {}", TE_INCOMPLETE_TYPE)
SEMA_ERROR("alloc_bad_names", "struct Allocator { c: *i8; a: fn(*i8, i64) -> *i8; f: fn(*i8, *i8) -> void; } fn main() {}", TE_INCOMPLETE_TYPE)
SEMA_ERROR("alloc_bad_sig", "struct Allocator { ctx: *i8; alloc: fn(i32) -> *i8; free: fn(*i8, *i8) -> void; } fn main() {}", TE_TYPE_MISMATCH)
