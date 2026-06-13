// test/cases/abi_stress.inc

TEST_CASE("Codegen/ABI/LargeStructArg") {
    // 3 * 8 bytes = 24 bytes > 16 bytes limit. Must be passed by pointer (byval).
    const char *src = 
        "struct Large { a: i64; b: i64; c: i64; }\n"
        "fn take_large(l: Large) -> i64 {\n"
        "    return l.a + l.b + l.c;\n"
        "}\n"
        "fn main() -> i64 {\n"
        "    l: Large = Large { a: 1, b: 2, c: 3 };\n"
        "    return take_large(l);\n"
        "}";
    ASSERT_EQ_INT(test_run_and_get_exit_code(src), 6);
    return 1;
}

TEST_CASE("Codegen/ABI/LargeStructReturn") {
    // Return a struct > 16 bytes (must use sret)
    const char *src = 
        "struct Large { a: i64; b: i64; c: i64; }\n"
        "fn mk_large() -> Large {\n"
        "    return Large { a: 10, b: 20, c: 30 };\n"
        "}\n"
        "fn main() -> i64 {\n"
        "    l: Large = mk_large();\n"
        "    return l.a + l.b + l.c;\n"
        "}";
    ASSERT_EQ_INT(test_run_and_get_exit_code(src), 60);
    return 1;
}

TEST_CASE("Codegen/ABI/NestedLargeStruct") {
    const char *src = 
        "struct Large { a: i64; b: i64; c: i64; }\n"
        "struct Nested { l1: Large; l2: Large; }\n"
        "fn sum_nested(n: Nested) -> i64 {\n"
        "    return n.l1.a + n.l1.b + n.l1.c + n.l2.a + n.l2.b + n.l2.c;\n"
        "}\n"
        "fn main() -> i64 {\n"
        "    n: Nested = Nested { \n"
        "        l1: Large { a: 1, b: 2, c: 3 }, \n"
        "        l2: Large { a: 4, b: 5, c: 6 } \n"
        "    };\n"
        "    return sum_nested(n);\n"
        "}";
    ASSERT_EQ_INT(test_run_and_get_exit_code(src), 21);
    return 1;
}
