#include "test_harness.h"
#include <time.h>
#include <stdarg.h>

#define MAX_TESTS 2048
#define LOG_BUFFER_SIZE 16384

typedef struct {
    const char *name;
    TestFunc func;
} TestEntry;

static TestEntry g_registry[MAX_TESTS];
static int g_registry_count = 0;

static int g_tests_run = 0;
static int g_tests_passed = 0;
static int g_tests_failed = 0;

static char g_log_buffer[LOG_BUFFER_SIZE];
static size_t g_log_len = 0;

void test_clear_log(void) {
    g_log_len = 0;
    g_log_buffer[0] = '\0';
}

void test_log(const char *fmt, ...) {
    if (g_log_len >= LOG_BUFFER_SIZE - 1) return;
    
    va_list args;
    va_start(args, fmt);
    int written = vsnprintf(g_log_buffer + g_log_len, LOG_BUFFER_SIZE - g_log_len, fmt, args);
    va_end(args);
    
    if (written > 0) {
        g_log_len += (size_t)written;
    }
}

void test_registry_add(const char *name, TestFunc func) {
    if (g_registry_count < MAX_TESTS) {
        g_registry[g_registry_count++] = (TestEntry){name, func};
    } else {
        fprintf(stderr, "Error: Test registry overflow\n");
    }
}

static void run_single_test(const char *name, TestFunc func) {
    g_tests_run++;
    test_clear_log();

    const char *sub = name;
    const char *slash = strchr(name, '/');
    if (slash) sub = slash + 1;

    fprintf(stderr, "      %-50s", sub);
    fflush(stderr);
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    int result = func();
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double diff_ms = (double)(end.tv_sec - start.tv_sec) * 1000.0 + 
                     (double)(end.tv_nsec - start.tv_nsec) / 1e6;

    if (result) {
        g_tests_passed++;
        fprintf(stderr, "\r\033[K    %s✓%s %-50s %s%8.3fms%s\n", 
            COL_GREEN, COL_RESET, sub, COL_CYAN, diff_ms, COL_RESET);
    } else {
        g_tests_failed++;
        fprintf(stderr, "\r\033[K    %s✗%s %-50s\n", COL_RED, COL_RESET, sub);
    }

    if (g_log_len > 0) {
        fprintf(stderr, "%s", g_log_buffer);
        if (g_log_buffer[g_log_len - 1] != '\n') fprintf(stderr, "\n");
    }
}

int run_all_registered_tests(int argc, char **argv) {
    const char *filter = NULL;
    bool list_only = false;
    bool fail_fast = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--filter") == 0 && i + 1 < argc) {
            filter = argv[++i];
        } else if (strcmp(argv[i], "--list") == 0) {
            list_only = true;
        } else if (strcmp(argv[i], "--fail-fast") == 0) {
            fail_fast = true;
        }
    }

    if (list_only) {
        printf("Available tests:\n");
        for (int i = 0; i < g_registry_count; i++) {
            printf("  %s\n", g_registry[i].name);
        }
        return 0;
    }

    fprintf(stderr, "\n%s=== Compiler Test Suite ===%s\n", COL_BOLD, COL_RESET);
    
    const char *current_cat = NULL;
    for (int i = 0; i < g_registry_count; i++) {
        if (filter && strstr(g_registry[i].name, filter) == NULL) {
            continue;
        }

        // Detect category change
        char cat[64] = {0};
        const char *slash = strchr(g_registry[i].name, '/');
        if (slash) {
            size_t len = (size_t)(slash - g_registry[i].name);
            if (len < sizeof(cat)) memcpy(cat, g_registry[i].name, len);
        } else {
            strcpy(cat, "General");
        }

        if (current_cat == NULL || strcmp(cat, current_cat) != 0) {
            fprintf(stderr, "\n %s[%s]%s\n", COL_BOLD, cat, COL_RESET);
            if (current_cat) free((void*)current_cat);
            current_cat = strdup(cat);
        }
        
        run_single_test(g_registry[i].name, g_registry[i].func);
        
        if (fail_fast && g_tests_failed > 0) {
            fprintf(stderr, "\n%sStopping early due to failure%s\n", COL_RED, COL_RESET);
            break;
        }
    }

    if (current_cat) free((void*)current_cat);

    fprintf(stderr, "\n%s=== Summary ===%s\n", COL_BOLD, COL_RESET);
    fprintf(stderr, "  Total:  %d\n", g_tests_run);
    fprintf(stderr, "  Passed: %s%d%s\n", COL_GREEN, g_tests_passed, COL_RESET);
    fprintf(stderr, "  Failed: %s%d%s\n", g_tests_failed ? COL_RED : COL_GREEN, g_tests_failed, COL_RESET);
    fprintf(stderr, "%s===============%s\n", COL_BOLD, COL_RESET);
    
    return g_tests_failed > 0 ? 1 : 0;
}
