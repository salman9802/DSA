// Stack (dynamic) Tests

#include<stdio.h>
#include<stdlib.h>

#include "munit.h"

#include "st.h"

MunitResult test_new_st() {
    st_t *st = new_st();

    munit_assert_ptr(st->top, ==, NULL);

    return MUNIT_OK;
}

MunitResult test_st_push() {
    st_t *st = new_st();
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    st_push(st, o1);
    munit_assert_ptr(st->top->data, ==, o1);
    
    st_push(st, o2);
    munit_assert_ptr(st->top->data, ==, o2);
    munit_assert_ptr(st->top->next->data, ==, o1);
    
    st_push(st, o3);
    munit_assert_ptr(st->top->data, ==, o3);
    munit_assert_ptr(st->top->next->data, ==, o2);
    munit_assert_ptr(st->top->next->next->data, ==, o1);
    munit_assert_ptr(st->top->next->next->next, ==, NULL);

    return MUNIT_OK;
}

MunitResult test_st_pop() {
    st_t *st = new_st();
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    st_push(st, o1);
    st_push(st, o2);
    st_push(st, o3);


    munit_assert_ptr(st_pop(st), ==, o3);
    munit_assert_ptr(st_pop(st), ==, o2);
    munit_assert_ptr(st_pop(st), ==, o1);
    munit_assert_ptr(st_pop(st), ==, NULL);
    munit_assert_ptr(st, !=, NULL);

    return MUNIT_OK;
}

MunitResult test_st_peek() {
    st_t *st = new_st();
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    st_push(st, o1);
    munit_assert_ptr(st_peek(st), ==, o1);

    st_push(st, o2);
    munit_assert_ptr(st_peek(st), ==, o2);

    st_push(st, o3);
    munit_assert_ptr(st_peek(st), ==, o3);

    return MUNIT_OK;
}

MunitResult test_st_reverse() {
    st_t *st = new_st();
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    st_push(st, o1);
    st_push(st, o2);
    st_push(st, o3);

    st_t *reverse_st = st_reverse(st);
    munit_assert_ptr(st_pop(reverse_st), ==, o1);
    munit_assert_ptr(st_pop(reverse_st), ==, o2);
    munit_assert_ptr(st_pop(reverse_st), ==, o3);
    munit_assert_ptr(st_pop(reverse_st), ==, NULL);
    
    return MUNIT_OK;
}

MunitSuite *test_st_suite() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest st_tests[] = {
    {
        "/test_new_st", /* name */
        test_new_st, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_st_push", /* name */
        test_st_push, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_st_pop", /* name */
        test_st_pop, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_st_peek", /* name */
        test_st_peek, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_st_reverse", /* name */
        test_st_reverse, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
   /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };

    static MunitSuite suite = {
        "/stack", /* name */
        st_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    return &suite;
}