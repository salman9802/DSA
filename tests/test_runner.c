#include <stdio.h>

#include "munit.h"


void test_stack_basic();
MunitTest *test_object_main();


int main(int argc, char** argv) {
    // printf("Running DSA tests...\n");
    // test_stack_basic();
     MunitTest *object_tests = test_object_main();

     MunitSuite suite = {
        "/object_tests", /* name */
        object_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    // printf("All tests completed.\n");
    return munit_suite_main(&suite, NULL, argc, argv);
}
