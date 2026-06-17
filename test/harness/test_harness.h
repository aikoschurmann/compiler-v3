#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

// Colors for the terminal
#define COL_RED "\033[31m"
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE "\033[34m"
#define COL_CYAN "\033[36m"
#define COL_BOLD "\033[1m"
#define COL_RESET "\033[0m"

typedef int (*TestFunc)(void);

// Property testing support
uint32_t test_get_seed(void);
void test_set_seed(uint32_t seed);

// Self-registration macro helpers
#define CONCAT_INTERNAL(a, b) a ## b
#define CONCAT(a, b) CONCAT_INTERNAL(a, b)

#define TEST_CASE_PRIO_INTERNAL(name, priority, count) \
    static int CONCAT(_test_func_, count)(void); \
    __attribute__((constructor)) \
    static void CONCAT(_test_reg_, count)(void) { \
        test_registry_add(name, CONCAT(_test_func_, count), priority); \
    } \
    static int CONCAT(_test_func_, count)(void)

#define TEST_CASE_PRIO(display_name, priority) TEST_CASE_PRIO_INTERNAL(display_name, priority, __COUNTER__)
#define TEST_CASE(display_name) TEST_CASE_PRIO(display_name, 100)

#define PROPERTY_CASE_PRIO_INTERNAL(name, iterations, priority, count) \
    static int CONCAT(_prop_logic_, count)(uint32_t seed); \
    TEST_CASE_PRIO(name, priority) { \
        uint32_t base_seed = (uint32_t)time(NULL); \
        for (int i = 0; i < iterations; i++) { \
            uint32_t current_seed = base_seed + i; \
            test_set_seed(current_seed); \
            if (!CONCAT(_prop_logic_, count)(current_seed)) { \
                test_log("      %sFAILED at seed:%s %u (iteration %d)\n", COL_RED, COL_RESET, current_seed, i); \
                return 0; \
            } \
        } \
        return 1; \
    } \
    static int CONCAT(_prop_logic_, count)(uint32_t seed)

#define PROPERTY_CASE_PRIO(display_name, iterations, priority) PROPERTY_CASE_PRIO_INTERNAL(display_name, iterations, priority, __COUNTER__)
#define PROPERTY_CASE(display_name, iterations) PROPERTY_CASE_PRIO(display_name, iterations, 100)

// Registry functions
void test_registry_add(const char *name, TestFunc func, int priority);
int run_all_registered_tests(int argc, char **argv);

// Buffered logging for detailed results
void test_log(const char *fmt, ...);
void test_clear_log(void);

// Assertions
#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            test_log("      %sFAILED:%s %s\n      at %s:%d\n", COL_RED, COL_RESET, #cond, __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)

#define ASSERT_SEED(cond, seed) \
    do { \
        if (!(cond)) { \
            test_log("      %sFAILED:%s %s\n      at %s:%d (seed: %u)\n", COL_RED, COL_RESET, #cond, __FILE__, __LINE__, seed); \
            return 0; \
        } \
    } while(0)

#define ASSERT_EQ_INT(actual, expected) \
    do { \
        long long _a = (long long)(actual); \
        long long _e = (long long)(expected); \
        if (_a != _e) { \
            test_log("      %sFAILED:%s Expected %lld, got %lld\n      at %s:%d\n", COL_RED, COL_RESET, _e, _a, __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)

#define ASSERT_STR_EQ(actual, expected) \
    do { \
        if (strcmp((actual), (expected)) != 0) { \
            test_log("      %sFAILED:%s Expected '%s', got '%s'\n      at %s:%d\n", COL_RED, COL_RESET, (expected), (actual), __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)
