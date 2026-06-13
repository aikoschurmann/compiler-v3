#include "../harness/test_harness.h"
#include "../helpers/compiler_helpers.h"

#define PARSE_VALID(name, src) \
    TEST_CASE("Parser/Valid/" name) { ASSERT(test_is_parse_valid(src)); return 1; }
#include "parser_cases.inc"
#include "parser_stress.inc"
#undef PARSE_VALID

TEST_CASE("Parser: Invalid Syntax") {
    ASSERT(!test_is_parse_valid("fn main() { x: i32 = ; }"));
    ASSERT(!test_is_parse_valid("fn main() { if true return 1; }")); // missing parens
    return 1;
}
