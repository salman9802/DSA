#include <stdio.h>

#include "munit.h"

#include "object.h"
#include "ll.h"


void test_stack_basic();
MunitSuite *test_object_suite();
MunitSuite *test_ll_suite();
MunitSuite *test_da_suite();


int main(int argc, char** argv) {
    // printf("Running DSA tests...\n");
    // test_stack_basic();
    //  MunitTest *object_tests = test_object_main();

    static MunitSuite sub_suites[4];
    sub_suites[0] = *test_object_suite();
    sub_suites[1] = *test_ll_suite();
    sub_suites[2] = *test_da_suite();

    // static MunitSuite all_suites[] = {
    //     sub_suites,
    //     // *test_ll_suite(),
    //     // {NULL, NULL, NULL, 0, MUNIT_SUITE_OPTION_NONE}
    // };

    static MunitSuite main_suite = {
        "", NULL, sub_suites, 1, MUNIT_SUITE_OPTION_NONE
    };

// int i1 = 1, i2 = 2, i3 = 3;
//     object_t *o1, *o2, *o3;
//     o1 = new_int_object(i1);
//     o2 = new_int_object(i2);
//     o3 = new_int_object(i3);
    
//     ll_node_t *head = NULL;
//     ll_insert(&head, o1);
//     ll_insert(&head, o2);
//     ll_insert(&head, o3);

//     ll_print(head);


    // printf("All tests completed.\n");
    return munit_suite_main(&main_suite, NULL, argc, argv);
}
