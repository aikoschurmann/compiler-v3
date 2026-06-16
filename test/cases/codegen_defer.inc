// test/cases/codegen_defer.inc

CODEGEN_EXIT("defer_while_continue",
    "fn main() -> i32 {\n"
    "    res: i32 = 0;\n"
    "    i: i32 = 0;\n"
    "    while (i < 5) {\n"
    "        i = i + 1;\n"
    "        defer { res = res + 1; }\n"
    "        if (i < 3) { continue; }\n"
    "    }\n"
    "    return res;\n"
    "}", 5)

CODEGEN_EXIT("defer_nested_early_return",
    "fn test_defer(x: i32) -> i32 {\n"
    "    defer { return 10; }\n"
    "    if (x > 0) {\n"
    "        defer { return 20; }\n"
    "        return 1;\n"
    "    }\n"
    "    return 0;\n"
    "}\n"
    "fn main() -> i32 {\n"
    "   return test_defer(1);\n"
    "}", 10)

CODEGEN_EXIT("defer_nested_scopes",
    "fn main() -> i32 {\n"
    "    res: i32 = 0;\n"
    "    {\n"
    "        defer { res = res + 100; }\n"
    "        if (res == 0) {\n"
    "            defer { res = res + 10; }\n"
    "            return res + 1; // Should execute both defers\n"
    "        }\n"
    "    }\n"
    "    return res;\n"
    "}", 1) 

CODEGEN_EXIT("defer_in_for_loop",
    "fn main() -> i32 {\n"
    "    sum: i32 = 0;\n"
    "    for(i: i32 = 0; i < 3; i = i + 1) {\n"
    "        defer { sum = sum + 10; }\n"
    "        sum = sum + 1;\n"
    "    }\n"
    "    return sum;\n"
    "}", 33)

CODEGEN_EXIT("defer_shadowing_var",
    "fn main() -> i32 {\n"
    "    val: i32 = 5;\n"
    "    {\n"
    "        val: i32 = 10;\n"
    "        defer { val = val + 1; }\n"
    "    }\n"
    "    return val;\n"
    "}", 5)

CODEGEN_EXIT("defer_break_double_exec",
    "fn main() -> i32 {\n"
    "    res: i32 = 0;\n"
    "    while (true) {\n"
    "        defer { res = res + 1; }\n"
    "        break;\n"
    "    }\n"
    "    // Should only execute once (during break)\n"
    "    return res;\n"
    "}", 1)

CODEGEN_EXIT("defer_break_double_exec_if",
    "fn main() -> i32 {\n"
    "    res: i32 = 0;\n"
    "    while (true) {\n"
    "        defer { res = res + 1; }\n"
    "        if (true) {\n"
    "            break;\n"
    "        }\n"
    "    }\n"
    "    return res;\n"
    "}", 1)

CODEGEN_EXIT("defer_lifo_order",
    "fn main() -> i32 {\n"
    "    // Test that we can mutate a variable, return it, but defers don't affect the returned value if it's already computed unless they explicitly return a new value. Wait, our `return` statement evaluates the expression, saves it to `ret_val`, runs defers, then returns `ret_val`. If a defer returns a NEW value, it overrides it.\n"
    "    defer { return 12; }\n"
    "    defer { return 5; }\n"
    "    return 1;\n"
    "}", 12)

CODEGEN_EXIT("defer_continue_complex",
    "fn main() -> i32 {\n"
    "    res: i32 = 0;\n"
    "    i: i32 = 0;\n"
    "    while (i < 3) {\n"
    "        defer { res = res + 1; }\n"
    "        if (i == 1) {\n"
    "            defer { res = res + 10; }\n"
    "            i = i + 1;\n"
    "            continue;\n"
    "        }\n"
    "        i = i + 1;\n"
    "    }\n"
    "    // i=0: res=0. natural exit -> res=1\n"
    "    // i=1: res=1. inner defer, then outer defer -> res=1+10+1 = 12\n"
    "    // i=2: res=12. natural exit -> res=13\n"
    "    return res;\n"
    "}", 13)

CODEGEN_EXIT("defer_return_override",
    "fn test_override() -> i32 {\n"
    "    defer { return 99; }\n"
    "    return 42;\n"
    "}\n"
    "fn main() -> i32 {\n"
    "    return test_override();\n"
    "}", 99)
