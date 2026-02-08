#include "test_utils.h"

int test_sema_arg_mismatch_regression() {
    // Regression test for "Argument count mismatch" error span fix
    const char *src = 
        "fn dummy() -> i64 { return 0; }\n"
        "arr: (fn(i64) -> i64)[2] = {dummy, dummy};\n" 
        "fn fib(n: i64) -> i64 { return n; }\n"
        "arr2: (fn(i64)->i64)[1] = {fib};\n"
        "res: i64 = arr2[0]();"; // Error here

    CompileResult res = compile_source(src);
    
    ASSERT(!res.parse_failed);
    ASSERT_NOT_NULL(res.ctx.errors);
    
    bool found = false;
    for (size_t i = 0; i < res.ctx.errors->count; i++) {
        TypeError *err = (TypeError*)dynarray_get(res.ctx.errors, i);
        if (err->kind == TE_ARG_COUNT_MISMATCH) {
             found = true;
        }
    }
    ASSERT(found);

    cleanup_compilation(&res);
    return 1;
}

int test_sema_type_mismatch() {
    const char *src = "x: i32 = \"string\";";
    CompileResult res = compile_source(src);
    
    // Should pass parsing but fail type check
    ASSERT(!res.parse_failed);
    ASSERT(res.ctx.errors->count > 0);
    
    bool found = false;
    for(size_t i=0; i<res.ctx.errors->count; i++) {
        TypeError *err = (TypeError*)dynarray_get(res.ctx.errors, i);
        if (err->kind == TE_TYPE_MISMATCH) found = true;
    }
    ASSERT(found);
    
    cleanup_compilation(&res);
    return 1;
}

int test_sema_undeclared() {
    const char *src = "x: i32 = y;";
    CompileResult res = compile_source(src);
    
    ASSERT(!res.parse_failed);
    ASSERT(res.ctx.errors->count > 0);
    
    bool found = false;
    for(size_t i=0; i<res.ctx.errors->count; i++) {
        TypeError *err = (TypeError*)dynarray_get(res.ctx.errors, i);
        if (err->kind == TE_UNDECLARED) found = true;
    }
    ASSERT(found);
    
    cleanup_compilation(&res);
    return 1;
}

int test_sema_valid_program() {
    const char *src = 
        "fn add(a: i64, b: i64) -> i64 { return a + b; }\n"
        "x: i64 = add(10, 20);";
        
    CompileResult res = compile_source(src);
    ASSERT(!res.parse_failed);
    
    if (res.ctx.errors && res.ctx.errors->count > 0) {
         TypeError *err = (TypeError*)dynarray_get(res.ctx.errors, 0);
         fprintf(stderr, "Unexpected error in valid program: kind %d\n", err->kind);
         cleanup_compilation(&res);
         return 0;
    }

    cleanup_compilation(&res);
    return 1;
}


int test_sema_call_arg_count() {
    // Global call with wrong arg count
    const char *src = 
        "fn add(a: i32, b: i32) -> i32 { return 0; }\n"
        "val: i32 = add(1);"; 
    CompileResult res = compile_source(src);
    ASSERT(!res.parse_failed);
    ASSERT(res.ctx.errors && res.ctx.errors->count > 0);
    cleanup_compilation(&res);
    return 1;
}

int test_sema_call_arg_type() {
    // Global call with wrong arg type
    const char *src = 
        "fn inc(a: i32) -> i32 { return 0; }\n"
        "val: i32 = inc(true);"; 
    CompileResult res = compile_source(src);
    ASSERT(!res.parse_failed);
    ASSERT(res.ctx.errors && res.ctx.errors->count > 0);
    cleanup_compilation(&res);
    return 1;
}

int test_sema_full_features() {
    const char *src = 
        "var1: i32[][] = {{1, 2}, {3, 4}};\n"
        "var2: i64[][] = {{1, 2}, {3, 4}};\n"
        "var3: f32[][] = {{1.1, 2.2}, {3.3, 4.4}};\n"
        "var4: f64[][] = {{1.1, 2.2}, {3.3, 4.4}};\n"
        "\n"
        "fn partition(a: i32[], lo: i32, hi: i32) -> i32 {\n"
        "    pivot: i32 = a[hi];\n"
        "    return partition_rec(a, lo, hi, lo, lo - 1, pivot);\n"
        "}\n"
        "\n"
        "fn partition_rec(a: i32[], lo: i32, hi: i32, j: i32, i: i32, pivot: i32) -> i32 {\n"
        "\n"
        "    if (j >= hi) {\n"
        "        tmp: i32 = a[i + 1];\n"
        "        a[i + 1] = a[hi];\n"
        "        a[hi] = tmp;\n"
        "        return i + 1;\n"
        "    }\n"
        "\n"
        "    if (a[j] < pivot) {\n"
        "        i2: i32 = i + 1;\n"
        "\n"
        "        tmp2: i32 = a[i2];\n"
        "        a[i2] = a[j];\n"
        "        a[j] = tmp2;\n"
        "\n"
        "        return partition_rec(a, lo, hi, j + 1, i2, pivot);\n"
        "    } else {\n"
        "        return partition_rec(a, lo, hi, j + 1, i, pivot);\n"
        "    }\n"
        "}\n"
        "\n"
        "fn quicksort(a: i32[], lo: i32, hi: i32) {\n"
        "    if (lo < hi) {\n"
        "        p: i32 = partition(a, lo, hi);\n"
        "        quicksort(a, lo, p - 1);\n"
        "        quicksort(a, p + 1, hi);\n"
        "    }\n"
        "}\n"
        "\n"
        "fn fib_iter(n: i32) -> i32 {\n"
        "    if (n <= 1) { return n; }\n"
        "    a: i32 = 0;\n"
        "    b: i32 = 1;\n"
        "    i: i32 = 2;\n"
        "    while (i <= n) {\n"
        "        temp: i32 = a + b;\n"
        "        a = b;\n"
        "        b = temp;\n"
        "        i++;\n"
        "    }\n"
        "    return b;\n"
        "}\n"
        "\n"
        "fn test_float_math(start: f32) -> f32 {\n"
        "    val: f32 = start;\n"
        "    count: i32 = 0;\n"
        "    while (count < 10) {\n"
        "        val += 1.5;\n"
        "        if (val > 100.0) { break; }\n"
        "        count++;\n"
        "    }\n"
        "    return val;\n"
        "}\n"
        "\n"
        "fn test_operators() {\n"
        "    x: i32 = 10;\n"
        "    x += 5; // 15\n"
        "    x *= 2; // 30\n"
        "    x--;    // 29\n"
        "    \n"
        "    y: i32 = 0;\n"
        "    while (y < 10) {\n"
        "        y++;\n"
        "        if (y % 2 == 0) { continue; }\n"
        "        // odd numbers logic\n"
        "    }\n"
        "}\n"
        "\n"
        "fn main() {\n"
        "    // Array & Quicksort Test\n"
        "    arr: i32[9] = { 30, 3, 4, 20, 5, 1, 17, 12, 9 };\n"
        "    quicksort(arr, 0, 8);\n"
        "\n"
        "    // Iterative Logic & Math Test\n"
        "    fib_res: i32 = fib_iter(10);\n"
        "    \n"
        "    // Float Logic\n"
        "    f_res: f32 = test_float_math(10.5);\n"
        "    \n"
        "    // Operators & Control Flow\n"
        "    test_operators();\n"
        "}";

    CompileResult res = compile_source(src);
    if (res.parse_failed) {
        fprintf(stderr, "Parsing full feature test suite failed.\n");
        return 0;
    }
    
    // Check that globals are fine
    if (res.ctx.errors && res.ctx.errors->count > 0) {
        for (size_t i = 0; i < res.ctx.errors->count; i++) {
             TypeError *err = (TypeError*)dynarray_get(res.ctx.errors, i);
             print_type_error(err);
        }
        cleanup_compilation(&res);
        return 0;
    }
    
    cleanup_compilation(&res);
    return 1;
}
