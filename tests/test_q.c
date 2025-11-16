// Queue (dynamic)

#include "munit.h"

#include "object.h"
#include "dll.h"
#include "q.h"

MunitResult test_q_enqueue_and_dequeue() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    
    // dll_node_t *head = NULL;
    // dll_insert_at_tail(&head, o1);
    // dll_insert_at_tail(&head, o2);
    // dll_insert_at_tail(&head, o3);

    q_t *q = new_q();

    munit_assert_ptr(q_dequeue(q), ==, NULL);
    
    q_enqueue(q, o1);
    q_enqueue(q, o2);
    q_enqueue(q, o3);
    
    munit_assert_ptr(q_dequeue(q), ==, o1);
    munit_assert_ptr(q_dequeue(q), ==, o2);
    munit_assert_ptr(q_dequeue(q), ==, o3);
    munit_assert_ptr(q_dequeue(q), ==, NULL);

    return MUNIT_OK;
}

MunitSuite *test_q_suite() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest q_tests[] = {
    {
        "/test_q_enqueue_and_dequeue", /* name */
        test_q_enqueue_and_dequeue, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
   /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };

    static MunitSuite suite = {
        "/queue", /* name */
        q_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    return &suite;
}