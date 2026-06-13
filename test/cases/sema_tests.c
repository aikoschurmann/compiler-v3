#include "../harness/test_harness.h"
#include "../helpers/compiler_helpers.h"

// 1. Basic Table-driven valid cases
#define SEMA_VALID(name, src) \
    TEST_CASE("Sema/Valid/" name) { ASSERT(test_is_sema_valid(src)); return 1; }
#include "sema_valid.inc"
#undef SEMA_VALID

// 2. Basic Table-driven error cases
#define SEMA_ERROR(name, src, kind) \
    TEST_CASE("Sema/Error/" name) { ASSERT(test_check_sema_error(src, kind)); return 1; }
#include "sema_errors.inc"
#include "allocator_tests.inc"
#undef SEMA_ERROR


// 3. Shadowing Stress Cases (Mix of VALID and ERROR)
#define SEMA_VALID(name, src) \
    TEST_CASE("Sema/Shadowing/Valid/" name) { ASSERT(test_is_sema_valid(src)); return 1; }
#define SEMA_ERROR(name, src, kind) \
    TEST_CASE("Sema/Shadowing/Error/" name) { ASSERT(test_check_sema_error(src, kind)); return 1; }
#include "shadowing_cases.inc"
#undef SEMA_VALID
#undef SEMA_ERROR

// 4. General Stress Cases
#define SEMA_VALID(name, src) \
    TEST_CASE("Sema/Stress/Valid/" name) { ASSERT(test_is_sema_valid(src)); return 1; }
#define SEMA_ERROR(name, src, kind) \
    TEST_CASE("Sema/Stress/Error/" name) { ASSERT(test_check_sema_error(src, kind)); return 1; }
#include "stress_cases.inc"
#include "casting_cases.inc"
#include "struct_stress.inc"
#include "fn_ptr_stress.inc"
#undef SEMA_VALID
#undef SEMA_ERROR
