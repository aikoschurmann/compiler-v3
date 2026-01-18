var1: i32[] = {{1, 2}, {3, 4}};
var2: i64[] = {{1, 2}, {3, 4}};
var3: f32[] = {{1.1, 2.2}, {3.3, 4.4}};
var4: f64[] = {{1.1, 2.2}, {3.3, 4.4}};
//var4: f64[] = {{1.1, 2.2}, {3.3, 4.4}};

fn partition(a: i32[], lo: i32, hi: i32) -> i32 {
    pivot: i32 = a[hi];
    return partition_rec(a, lo, hi, lo, lo - 1, pivot);
}

fn partition_rec(a: i32[], lo: i32, hi: i32, j: i32, i: i32, pivot: i32) -> i32 {

    if (j >= hi) {
        tmp: i32 = a[i + 1];
        a[i + 1] = a[hi];
        a[hi] = tmp;
        return i + 1;
    }

    if (a[j] < pivot) {
        i2: i32 = i + 1;

        tmp2: i32 = a[i2];
        a[i2] = a[j];
        a[j] = tmp2;

        return partition_rec(a, lo, hi, j + 1, i2, pivot);
    } else {
        return partition_rec(a, lo, hi, j + 1, i, pivot);
    }
}

fn quicksort(a: i32[], lo: i32, hi: i32) {
    if (lo < hi) {
        p: i32 = partition(a, lo, hi);
        quicksort(a, lo, p - 1);
        quicksort(a, p + 1, hi);
    }
}

fn fib_iter(n: i32) -> i32 {
    if (n <= 1) { return n; }
    a: i32 = 0;
    b: i32 = 1;
    i: i32 = 2;
    while (i <= n) {
        temp: i32 = a + b;
        a = b;
        b = temp;
        i++;
    }
    return b;
}

fn test_float_math(start: f32) -> f32 {
    val: f32 = start;
    count: i32 = 0;
    while (count < 10) {
        val += 1.5;
        if (val > 100.0) { break; }
        count++;
    }
    return val;
}

fn test_operators() {
    x: i32 = 10;
    x += 5; // 15
    x *= 2; // 30
    x--;    // 29
    
    y: i32 = 0;
    while (y < 10) {
        y++;
        if (y % 2 == 0) { continue; }
        // odd numbers logic
    }
}

fn main() {
    // Array & Quicksort Test
    arr: i32[9] = { 30, 3, 4, 20, 5, 1, 17, 12, 9 };
    quicksort(arr, 0, 8);

    // Iterative Logic & Math Test
    fib_res: i32 = fib_iter(10);
    
    // Float Logic
    f_res: f32 = test_float_math(10.5);
    
    // Operators & Control Flow
    test_operators();
}
