#include "harness/test_harness.h"
#include "codegen/codegen.h"

int main(int argc, char **argv) {
    codegen_initialize();
    return run_all_registered_tests(argc, argv);
}
