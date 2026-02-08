// ============================================================================
// COMPILER STRESS TEST SUITE
// Covers: Promotions, Pointers, Arrays (N-Dim), Function Types, Control Flow
// ============================================================================

// ----------------------------------------------------------------------------
// 1. Global Constants & Primitives
// ----------------------------------------------------------------------------
const GLOBAL_X: i32 = 10;
const GLOBAL_PI: f64 = 3.14159;
const IS_DEBUG: bool = true;

// ----------------------------------------------------------------------------
// 2. Helper Functions
// ----------------------------------------------------------------------------
fn add_i32(a: i32, b: i32) -> i32 { 
    return a + b; 
}

fn add_f64(a: f64, b: f64) -> f64 { 
    return a + b; 
}

// Function taking a function pointer as an argument
fn apply_op(a: i32, b: i32, op: fn(i32, i32) -> i32) -> i32 {
    return op(a, b);
}

fn get_magic_number() -> i32 {
    return 42;
}

// ----------------------------------------------------------------------------
// 3. Test: Numeric Promotions (Implicit Casts)
// ----------------------------------------------------------------------------
fn test_promotions() {
    // A. Assignment Promotion
    val_i64: i64 = 100;         // i32 literal -> i64
    val_f32: f32 = 123;         // i32 literal -> f32
    val_f64: f64 = 456.5;       // f64 literal
    val_f64_2: f64 = 789;       // i32 literal -> f64

    // B. Binary Operator Promotion
    // i32 + f64 -> f64
    res_mix_1: f64 = 10 + 20.5; 
    
    // f32 + f64 -> f64
    f_small: f32 = 1.0;
    f_large: f64 = 2.0;
    res_mix_2: f64 = f_small + f_large;

    // i32 + i64 -> i64
    i_small: i32 = 10;
    i_large: i64 = 20;
    res_mix_3: i64 = i_small + i_large;

    // C. Function Argument Promotion
    // Calling add_f64(f64, f64) with (i32, f32) -> Both promote to f64
    res_call: f64 = add_f64(10, 2.5); 
}

// ----------------------------------------------------------------------------
// 4. Test: Pointers & References
// ----------------------------------------------------------------------------
fn test_pointers() {
    val: i32 = 50;
    
    // A. Reference Operator (&)
    ptr: i32* = &val;
    
    // B. Dereference Operator (*)
    read_val: i32 = *ptr;
    
    // C. Pointer to Pointer
    ptr_ptr: i32** = &ptr;
    deep_val: i32 = **ptr_ptr;
    
    // D. Assigning via Dereference
    *ptr = 100;
}

// ----------------------------------------------------------------------------
// 5. Test: Arrays (1D, Multi-Dim, Inferred)
// ----------------------------------------------------------------------------
fn test_arrays() {
    // A. 1D Fixed Size
    arr_fixed: i32[3] = {1, 2, 3};
    
    // B. 1D Inferred Size
    arr_inf: i32[] = {10, 20, 30, 40};
    
    // C. 2D Array (Matrix)
    // Inferred as i32[2][3]
    matrix: i32[][] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    // D. 3D Array (Cube) with Promotion inside List
    // {1, 2} (i32) promotes to f64 elements
    cube: f64[][][] = {
        { {1, 2}, {3, 4} },
        { {5, 6}, {7, 8} }
    };
    
    // E. Indexing & Math in Index
    val: f64 = cube[1][0][1]; // Should be 6.0
    val_complex: f64 = cube[1-1][0][1+0]; // 2.0
}

// ----------------------------------------------------------------------------
// 6. Test: Complex Types (Arrays of Functions/Pointers)
// ----------------------------------------------------------------------------
fn test_complex_types() {
    // A. Array of Function Pointers
    // Explicit size: (fn(i32, i32) -> i32)[1]
    ops: (fn(i32, i32) -> i32)[1] = { add_i32 };
    
    // B. Call function from array
    res: i32 = ops[0](10, 20); // 30
    
    // C. Array of Pointers
    a: i32 = 1;
    b: i32 = 2;
    ptr_arr: (i32*)[] = { &a, &b };
    
    deref: i32 = *ptr_arr[1]; // 2
}

// ----------------------------------------------------------------------------
// 7. Test: Scope Shadowing & Control Flow
// ----------------------------------------------------------------------------
fn test_logic(n: i32) -> i32 {
    res: i32 = 0;
    
    // Scope 1
    if (n > 0) {
        // Shadow 'res'
        res: i32 = 10;
        
        // Scope 2 (Nested)
        if (n > 5) {
            // Shadow 'res' again
            res: i32 = 20;
            return res; // Returns 20
        }
        return res; // Returns 10
    } else {
        return -1;
    }
    
    // While Loop
    count: i32 = 0;
    while (count < 5) {
        // Operator assignment
        count = count + 1;
    }
    
    return res; // Returns 0 (original)
}

// ----------------------------------------------------------------------------
// 8. Test: Recursion (Fibonacci)
// ----------------------------------------------------------------------------
fn fib(n: i64) -> i64 {
    if (n <= 1) { 
        return n; 
    }
    return fib(n - 1) + fib(n - 2);
}

// ----------------------------------------------------------------------------
// Main Entry
// ----------------------------------------------------------------------------
fn main() {
    // Execute all tests
    test_promotions();
    test_pointers();
    test_arrays();
    test_complex_types();
    
    // Verify Logic
    logic_res: i32 = test_logic(6); // Should be 20
    
    // Verify Recursion
    fib_res: i64 = fib(10); // Should be 55
    
    // Constant usage in expression
    calc: i32 = GLOBAL_X * 2;
}