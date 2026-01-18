#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Colors
#define COL_RED "\033[31m"
#define COL_GREEN "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_RESET "\033[0m"

typedef int (*TestFunc)();

void run_test(const char *name, TestFunc func);
int print_test_summary();

// Assert macros
#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "%sFAILED%s: %s (at %s:%d)\n", COL_RED, COL_RESET, #cond, __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)

#define ASSERT_EQ_INT(actual, expected) \
    do { \
        long long _a = (long long)(actual); \
        long long _e = (long long)(expected); \
        if (_a != _e) { \
            fprintf(stderr, "%sFAILED%s: Expected %lld, got %lld (at %s:%d)\n", COL_RED, COL_RESET, _e, _a, __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)

#define ASSERT_NOT_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "%sFAILED%s: Expected non-NULL pointer (at %s:%d)\n", COL_RED, COL_RESET, __FILE__, __LINE__); \
            return 0; \
        } \
    } while(0)
