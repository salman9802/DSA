#include<stdio.h>
#include<stdlib.h>

#include "munit.h"

#include "ll.h"

MunitResult test_ll_insert() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    
    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);
    ll_insert(&head, o3);

    munit_assert_int(head->data->value.v_int, ==, i1);
    munit_assert_int(head->next->data->value.v_int, ==, i2);
    munit_assert_int(head->next->next->data->value.v_int, ==, i3);

    return MUNIT_OK;
}

MunitResult test_ll_traverse() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    
    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);
    ll_insert(&head, o3);

    // printf(" [");
    // ll_print(head);
    // printf("] ");

    return MUNIT_OK;
}

MunitResult test_ll_node_at() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);
    ll_insert(&head, o3);

    // If head is NULL
    munit_assert_ptr(ll_node_at(NULL, 0), ==, NULL);
    
    // If index is -ve
    munit_assert_ptr(ll_node_at(head, -1), ==, NULL);

    // If not present
    munit_assert_ptr(ll_node_at(head, 3), ==, NULL);
    
    // If present
    munit_assert_ptr(ll_node_at(head, 0), ==, head);
    munit_assert_ptr(ll_node_at(head, 1), ==, head->next);
    munit_assert_ptr(ll_node_at(head, 2), ==, head->next->next);

    return MUNIT_OK;
}

MunitResult test_ll_insert_at() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *head = NULL;
    // head is NULL
    ll_insert_at(&head, 0, o3);
    munit_assert_ptr(head->data, ==, o3);
    
    // index is -ve
    ll_insert_at(&head, -1, o3);
    munit_assert_ptr(head->next, ==, NULL);
    
    // insert at start
    ll_insert_at(&head, 0, o1);
    munit_assert_ptr(head->data, ==, o1);
    munit_assert_ptr(head->next->data, ==, o3);

    // insert beyond index
    ll_insert_at(&head, 123, o4);
    munit_assert_ptr(head->next->next->data, ==, o4);
    munit_assert_ptr(head->next->next->next, ==, NULL);

    // proper insert
    ll_insert_at(&head, 1, o2);
    munit_assert_ptr(head->next->data, ==, o2);


    munit_assert_ptr(head->data, ==, o1);
    munit_assert_ptr(head->next->data, ==, o2);
    munit_assert_ptr(head->next->next->data, ==, o3);
    munit_assert_ptr(head->next->next->next->data, ==, o4);

    return MUNIT_OK;
}

MunitResult test_ll_delete_at() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);
    ll_insert(&head, o3);
    ll_insert(&head, o4);

    // delete first
    ll_delete_at(&head, 0);
    munit_assert_ptr(head->data, ==, o2);
    
    // printf("\n================================\n");
    // ll_print(head);
    // printf("\n================================\n");
    // delete at index
    ll_delete_at(&head, 1);
    munit_assert_ptr(head->next->next, ==, NULL);
    munit_assert_ptr(head->next->data, ==, o4);

    
    // delete last
    ll_delete_at(&head, 1);
    munit_assert_ptr(head->next, ==, NULL);
    munit_assert_ptr(head->data, ==, o2);
    
    return MUNIT_OK;
}

MunitResult test_ll_length() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    munit_assert_int(ll_length(head), ==, 1);
    
    ll_insert(&head, o2);
    munit_assert_int(ll_length(head), ==, 2);

    ll_insert(&head, o3);
    munit_assert_int(ll_length(head), ==, 3);
    
    ll_insert(&head, o4);
    munit_assert_int(ll_length(head), ==, 4);
    
    return MUNIT_OK;
}

MunitResult test_ll_copy() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);
    ll_insert(&head, o3);
    ll_insert(&head, o4);

    ll_node_t *new_head = ll_copy(head);
    munit_assert_ptr(new_head->data, ==, o1);
    munit_assert_ptr(new_head->next->data, ==, o2);
    munit_assert_ptr(new_head->next->next->data, ==, o3);
    munit_assert_ptr(new_head->next->next->next->data, ==, o4);
    munit_assert_ptr(new_head->next->next->next->next, ==, NULL);

    return MUNIT_OK;
}

MunitResult test_ll_merge() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *h1 = NULL;
    ll_node_t *h2 = NULL;
    ll_insert(&h1, o1);
    ll_insert(&h1, o2);
    ll_insert(&h2, o3);
    ll_insert(&h2, o4);

    ll_node_t *merged_head = ll_merge(h1, h2);
    munit_assert_int(ll_length(h1), ==, 2);
    munit_assert_int(ll_length(h2), ==, 2);
    munit_assert_int(ll_length(merged_head), ==, 4);
    munit_assert_ptr(merged_head->data, ==, o1);
    munit_assert_ptr(merged_head->next->data, ==, o2);
    munit_assert_ptr(merged_head->next->next->data, ==, o3);
    munit_assert_ptr(merged_head->next->next->next->data, ==, o4);
    munit_assert_ptr(merged_head->next->next->next->next, ==, NULL);

    return MUNIT_OK;
}

MunitResult test_ll_search_node() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);
    ll_insert(&head, o3);
    ll_insert(&head, o4);

    munit_assert_int(ll_search_node(head, o1), ==, 0);
    munit_assert_int(ll_search_node(head, o2), ==, 1);
    munit_assert_int(ll_search_node(head, o3), ==, 2);
    munit_assert_int(ll_search_node(head, o4), ==, 3);

    return MUNIT_OK;
}

MunitResult test_ll_reverse() {
    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    object_t *o1, *o2, *o3, *o4;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    o4 = new_int_object(i4);

    ll_node_t *head = NULL;

    // If NULL
    munit_assert_ptr(ll_reverse(NULL), ==, NULL);

    // With one node
    ll_insert(&head, o1);
    munit_assert_ptr(ll_reverse(head), ==, head);
    
    // With multiple nodes
    ll_insert(&head, o2);
    munit_assert_ptr(ll_reverse(head)->data, ==, o2);
    ll_insert(&head, o3);
    munit_assert_ptr(ll_reverse(head)->data, ==, o3);
    ll_insert(&head, o4);
    munit_assert_ptr(ll_reverse(head)->data, ==, o4);

    return MUNIT_OK;
}

MunitResult test_ll_remove_tail() {
    int i1 = 1, i2 = 2;
    object_t *o1, *o2;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    
    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);

    munit_assert_ptr(ll_remove_tail(&head)->data, ==, o2);
    munit_assert_ptr(head->data, ==, o1);
    munit_assert_ptr(head->next, ==, NULL);

    munit_assert_ptr(ll_remove_tail(&head)->data, ==, o1);
    munit_assert_ptr(head, ==, NULL);

    return MUNIT_OK;
}

MunitResult test_ll_remove_head() {
    int i1 = 1, i2 = 2;
    object_t *o1, *o2;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    
    ll_node_t *head = NULL;
    ll_insert(&head, o1);
    ll_insert(&head, o2);

    munit_assert_ptr(ll_remove_head(&head)->data, ==, o1);
    munit_assert_ptr(head->data, ==, o2);
    munit_assert_ptr(head->next, ==, NULL);

    munit_assert_ptr(ll_remove_head(&head)->data, ==, o2);
    munit_assert_ptr(head, ==, NULL);

    return MUNIT_OK;
}


MunitSuite *test_ll_suite() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest ll_tests[] = {
    {
        "/test_ll_insert", /* name */
        test_ll_insert, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_traverse", /* name */
        test_ll_traverse, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_node_at", /* name */
        test_ll_node_at, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_insert_at", /* name */
        test_ll_insert_at, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_delete_at", /* name */
        test_ll_delete_at, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_length", /* name */
        test_ll_length, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_copy", /* name */
        test_ll_copy, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_merge", /* name */
        test_ll_merge, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_search_node", /* name */
        test_ll_search_node, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_reverse", /* name */
        test_ll_reverse, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_remove_tail", /* name */
        test_ll_remove_tail, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_ll_remove_head", /* name */
        test_ll_remove_head, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
   /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };

    static MunitSuite suite = {
        "/linked_list", /* name */
        ll_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    return &suite;
}