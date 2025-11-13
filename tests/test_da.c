// Dynamic Array Tests

#include<stdio.h>
#include<stdlib.h>

#include "munit.h"

#include "da.h"

MunitResult test_new_da() {
    size_t capacity = 5;
    da_t *da = new_da(capacity);
    munit_assert_size(da->size, ==, 0);
    munit_assert_size(da->capacity, ==, capacity);
    munit_assert_size(sizeof(da->elements), ==, sizeof(object_t *));

    return MUNIT_OK;
}

MunitResult test_da_resize() {
    size_t original_capacity = 2;
    da_t *da = new_da(original_capacity);
    
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    da_add(da, o1);
    da_add(da, o2);

    munit_assert_ptr(da->elements[0], ==, o1);
    munit_assert_ptr(da->elements[1], ==, o2);
    
    // printf("\n===============================\n");
    // da_print(da);
    // printf("\n===============================\n");

    size_t new_capacity = 5;
    da_resize(da, new_capacity);
    munit_assert_size(da->capacity, ==, new_capacity);
    da_add(da, o3);
    
    munit_assert_ptr(da->elements[0], ==, o1);
    munit_assert_ptr(da->elements[1], ==, o2);
    munit_assert_ptr(da->elements[2], ==, o3);

    return MUNIT_OK;
}

MunitResult test_da_add() {
    size_t capacity = 2;
    da_t *da = new_da(capacity);

    munit_assert_size(da->size, ==, 0);

    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);
    
    da_add(da, o1);
    munit_assert_size(da->size, ==, 1);
    munit_assert_ptr(da->elements[0], ==, o1);
    
    da_add(da, o2);
    munit_assert_size(da->size, ==, 2);
    munit_assert_ptr(da->elements[1], ==, o2);
    

    da_add(da, o3);
    munit_assert_size(da->size, ==, 3);
    munit_assert_ptr(da->elements[2], ==, o3);

    
    return MUNIT_OK;
}

MunitResult test_da_remove_at() {
    size_t capacity = 10;
    da_t *da = new_da(capacity);

    for(size_t i = 0; i < capacity; i++)
        da_add(da, new_int_object(i));

    munit_assert_size(da->size, ==, 10);

    for(size_t i = 0; i < capacity - 2; i++)
        munit_assert_int(da_remove_at(da, 0)->value.v_int, ==, i);

    // auto shrink
    munit_assert_size(da->size, ==, 2);

    return MUNIT_OK;
}

MunitResult test_da_access() {
    size_t capacity = 10;
    da_t *da = new_da(capacity);

    for(size_t i = 0; i < capacity; i++)
        da_add(da, new_int_object(i));

    munit_assert_size(da->size, ==, 10);

    for(size_t i = 0; i < capacity - 2; i++)
        munit_assert_int(da_access(da, i)->value.v_int, ==, i);

    // no auto shrink
    munit_assert_size(da->size, !=, 2);

    return MUNIT_OK;
}

MunitResult test_da_update() {
    size_t capacity = 10;
    da_t *da = new_da(capacity);

    for(size_t i = 0; i < capacity; i++)
        da_add(da, new_int_object(i));

    munit_assert_int(da_access(da, 3)->value.v_int, ==, 3);
    da_update(da, 3, new_int_object(12));
    munit_assert_int(da_access(da, 3)->value.v_int, ==, 12);

    return MUNIT_OK;
}

MunitResult test_da_insert_at() {
    // No Auto Resize
    size_t capacity = 10;
    da_t *da = new_da(capacity);

    for(size_t i = 0; i < capacity; i++)
        da_add(da, new_int_object(i));

    munit_assert_int(da_access(da, 3)->value.v_int, ==, 3);
    da_insert_at(da, 3, new_int_object(12));
    munit_assert_int(da_access(da, 3)->value.v_int, ==, 12);
    
    // values shifted
    for(size_t i = 4; i < capacity; i++)
        munit_assert_int(da_access(da, i)->value.v_int, ==, i - 1);
    munit_assert_int(da_access(da, 0)->value.v_int, ==, 0);
    munit_assert_int(da_access(da, 1)->value.v_int, ==, 1);
    munit_assert_int(da_access(da, 2)->value.v_int, ==, 2);

    da_free(da);
    
    // Auto Resize
    capacity = 10;
    da = new_da(capacity);

    for(size_t i = 0; i < capacity / 2; i++)
        da_add(da, new_int_object(i));

    munit_assert_int(da_access(da, 3)->value.v_int, ==, 3);
    da_insert_at(da, 3, new_int_object(12));
    munit_assert_int(da_access(da, 3)->value.v_int, ==, 12);
    
    // values shifted
    for(size_t i = 4; i < capacity / 2; i++)
        munit_assert_int(da_access(da, i)->value.v_int, ==, i - 1);
    munit_assert_int(da_access(da, 0)->value.v_int, ==, 0);
    munit_assert_int(da_access(da, 1)->value.v_int, ==, 1);
    munit_assert_int(da_access(da, 2)->value.v_int, ==, 2);

    return MUNIT_OK;
}

MunitResult test_da_search() {
    size_t capacity = 10;
    da_t *da = new_da(capacity);
    object_t **objects = malloc(capacity * sizeof(object_t));
    object_t *temp = NULL;

    for(size_t i = 0; i < capacity; i++) {
        temp = new_int_object(i);
        da_add(da, temp);
        objects[i] = temp;
    }
    
    for(size_t i = 0; i < capacity; i++)
        munit_assert_int(da_search(da, objects[i]), ==, i);
        
    return MUNIT_OK;
}

MunitSuite *test_da_suite() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest da_tests[] = {
    {
        "/test_new_da", /* name */
        test_new_da, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_resize", /* name */
        test_da_resize, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_add", /* name */
        test_da_add, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_remove_at", /* name */
        test_da_remove_at, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_access", /* name */
        test_da_access, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_update", /* name */
        test_da_update, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_insert_at", /* name */
        test_da_insert_at, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_da_search", /* name */
        test_da_search, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
   /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };

    static MunitSuite suite = {
        "/dynamic_array", /* name */
        da_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    return &suite;
}