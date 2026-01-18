#include "test_harness.h"
#include <time.h>

static int g_tests_run = 0;
static int g_tests_passed = 0;
static int g_tests_failed = 0;

void run_test(const char *name, TestFunc func) {
    g_tests_run++;
    fprintf(stderr, "Running %-40s ... ", name);
    // Flush to show running state
    fflush(stderr);
    
    clock_t start = clock();
    int result = func();
    clock_t end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if (result) {
        g_tests_passed++;
        fprintf(stderr, "%sPASSED%s (%.4fs)\n", COL_GREEN, COL_RESET, cpu_time_used);
    } else {
        g_tests_failed++;
        // Newline already printed by ASSERT failure mostly
    }
}

int print_test_summary() {
    fprintf(stderr, "\n%sTest Summary:%s\n", COL_YELLOW, COL_RESET);
    fprintf(stderr, "Total:  %d\n", g_tests_run);
    fprintf(stderr, "Passed: %s%d%s\n", COL_GREEN, g_tests_passed, COL_RESET);
    fprintf(stderr, "Failed: %s%d%s\n", g_tests_failed ? COL_RED : COL_GREEN, g_tests_failed, COL_RESET);
    
    return g_tests_failed > 0 ? 1 : 0;
}
