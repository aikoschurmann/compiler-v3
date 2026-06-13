#include "../harness/test_harness.h"
#include "../helpers/compiler_helpers.h"

TEST_CASE("Codegen: Basic Arithmetic") {
    ASSERT_EQ_INT(test_run_and_get_exit_code("fn main() -> i32 { return 10 + 20; }"), 30);
    return 1;
}

TEST_CASE("Codegen: If-Else") {
    const char *src = "fn main() -> i32 { if (1 < 2) { return 1; } else { return 2; } }";
    ASSERT_EQ_INT(test_run_and_get_exit_code(src), 1);
    return 1;
}

TEST_CASE("Codegen: Loops") {
    const char *src = 
        "fn main() -> i32 {\n"
        "    sum: i32 = 0;\n"
        "    for (i: i32 = 0; i < 10; i = i + 1) {\n"
        "        sum = sum + i;\n"
        "    }\n"
        "    return sum;\n"
        "}";
    ASSERT_EQ_INT(test_run_and_get_exit_code(src), 45);
    return 1;
}

#define CODEGEN_EXIT(name, src, expected) \
    TEST_CASE("Codegen/Complex/" name) { ASSERT_EQ_INT(test_run_and_get_exit_code(src), expected); return 1; }
#include "complex_types.inc"
#undef CODEGEN_EXIT

#define CODEGEN_EXIT(name, src, expected) \
    TEST_CASE("Codegen/Stress/" name) { ASSERT_EQ_INT(test_run_and_get_exit_code(src), expected); return 1; }
#include "codegen_stress.inc"
#include "more_codegen.inc"
#include "deep_stress.inc"
#include "abi_stress.inc"
#undef CODEGEN_EXIT
