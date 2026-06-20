#include "../harness/test_harness.h"
#include "../helpers/compiler_helpers.h"

#define PARSE_VALID(name, src) \
    TEST_CASE_PRIO("Parser/Valid/" name, 20) { ASSERT(test_is_parse_valid(src)); return 1; }
#include "parser_cases.inc"
#include "parser_stress.inc"
#undef PARSE_VALID

#define PARSE_ERROR(name, src, msg) \
    TEST_CASE_PRIO("Parser/Error/" name, 20) { ASSERT(test_check_parse_error(src, msg)); return 1; }

PARSE_ERROR("missing_rhs", "fn main() { x: i32 = ; }", "expected primary expression")
PARSE_ERROR("missing_brace_if", "fn main() { if true return 1; }", "expected '{' at start of block")
PARSE_ERROR("missing_parens_for", "fn main() { for i: i32 = 0; i < 10; i = i + 1 { } }", "expected '(' after 'for'")
PARSE_ERROR("missing_brace", "fn main() { x: i32 = 1;", "expected '}'")
PARSE_ERROR("missing_type", "fn main() { x: = 1; }", "expected type name")
PARSE_ERROR("bad_alloc", "import std; fn main() { p: *i32 = @alloc(10, std.heap.allocator, 1); }", "expected type name")

#undef PARSE_ERROR
