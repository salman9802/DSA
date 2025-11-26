// Priority Queue (dynamic)

#include<stdio.h>

#include "munit.h"

#include "object.h"
#include "dll.h"
#include "pq.h"

MunitResult test_pq_new() {
    pq_t *pq = new_pq();

    if(pq != NULL) {
        munit_assert_ptr(pq->front, ==, NULL);
        munit_assert_ptr(pq->rear, ==, NULL);
    }

    return MUNIT_OK;
}

MunitResult test_pq_enqueue_and_dequeue() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    
    // dll_node_t *head = NULL;
    // dll_insert_at_tail(&head, o1);
    // dll_insert_at_tail(&head, o2);
    // dll_insert_at_tail(&head, o3);

    pq_t *pq = new_pq();

    // munit_assert_ptr(q_dequeue(q), ==, NULL);
    
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o2, PQ_LOW);
    
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o1, PQ_HIGH);
    
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o2, PQ_LOW);
    
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o1, PQ_HIGH);

    // printf("\n===============================\n");
    // pq_print(pq);
    // printf("\n===============================\n");
    
    
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_CRITICAL);

    
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_HIGH);

    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_LOW);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_LOW);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_LOW);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_LOW);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_LOW);
    munit_assert_int(pq_dequeue(pq)->priority, ==, PQ_LOW);

    return MUNIT_OK;
}

MunitResult test_pq_enqueue_and_dequeue_by_priority() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    pq_t *pq = new_pq();

    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o2, PQ_LOW);
    
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o1, PQ_HIGH);
    
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o2, PQ_LOW);
    
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o1, PQ_HIGH);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    
    pq_enqueue(pq, o2, PQ_LOW);
    pq_enqueue(pq, o3, PQ_CRITICAL);
    pq_enqueue(pq, o1, PQ_HIGH);

    // printf("\n===============================\n");
    // pq_print(pq);
    // printf("\n===============================\n");

    
    // printf("\n===============================\n");
    // pq_print(pq);
    // printf("\n===============================\n");
    
    
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_CRITICAL)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_HIGH)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_LOW)->priority, ==, PQ_LOW);
    
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_CRITICAL)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_HIGH)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_LOW)->priority, ==, PQ_LOW);

    munit_assert_int(pq_dequeue_by_priority(pq, PQ_CRITICAL)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_HIGH)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_LOW)->priority, ==, PQ_LOW);

    munit_assert_int(pq_dequeue_by_priority(pq, PQ_CRITICAL)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_HIGH)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_LOW)->priority, ==, PQ_LOW);

    munit_assert_int(pq_dequeue_by_priority(pq, PQ_CRITICAL)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_HIGH)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_LOW)->priority, ==, PQ_LOW);

    munit_assert_int(pq_dequeue_by_priority(pq, PQ_CRITICAL)->priority, ==, PQ_CRITICAL);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_HIGH)->priority, ==, PQ_HIGH);
    munit_assert_int(pq_dequeue_by_priority(pq, PQ_LOW)->priority, ==, PQ_LOW);

    munit_assert_ptr(pq_dequeue_by_priority(pq, PQ_CRITICAL), ==, NULL);
    munit_assert_ptr(pq_dequeue_by_priority(pq, PQ_HIGH), ==, NULL);
    munit_assert_ptr(pq_dequeue_by_priority(pq, PQ_LOW), ==, NULL);

    pq_free(&pq);

    munit_assert_ptr(pq, ==, NULL);

    return MUNIT_OK;
}

MunitSuite *test_pq_suite() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest pq_tests[] = {
    {
        "/test_pq_new", /* name */
        test_pq_new, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_pq_enqueue_and_dequeue", /* name */
        test_pq_enqueue_and_dequeue, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_pq_enqueue_and_dequeue_by_priority", /* name */
        test_pq_enqueue_and_dequeue_by_priority, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
   /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };

    static MunitSuite suite = {
        "/priority_queue", /* name */
        pq_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    return &suite;
}