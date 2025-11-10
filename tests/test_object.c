#include "munit.h"

#include "object.h"


// MunitResult test_int_object(const MunitParameter params[], void* user_data_or_fixture) {
MunitResult test_int_object() {
    int v = 3;
    object_t *o1 = new_int_object(v);

    // The object has the correct kind
    munit_assert_int(o1->kind, ==, INT);
    
    // The object has correct value
    munit_assert_int(o1->value.v_int, ==, v);

    // The value doesn't have the same address
    munit_assert_ptr(&o1->value.v_int, !=, &v);
    
    return MUNIT_OK;
}

MunitResult test_float_object() {
    float v = 3;
    object_t *o1 = new_float_object(v);

    // The object has the correct kind
    munit_assert_int(o1->kind, ==, FLOAT);

    // The object has correct value
    munit_assert_float(o1->value.v_float, ==, v);

    // The value doesn't have the same address
    munit_assert_ptr(&o1->value.v_float, !=, &v);
    
    return MUNIT_OK;
}

MunitResult test_str_object() {
    char *v = "Hello World!";
    object_t *o1 = new_str_object(v);

    // The object has the correct kind
    munit_assert_int(o1->kind, ==, STR);

    // The object has correct value
    munit_assert_string_equal(o1->value.v_str, v);

    // The value doesn't have the same address
    munit_assert_ptr(&o1->value.v_str, !=, v);
    
    return MUNIT_OK;
}

MunitResult test_object_compare() {
    // INT
    object_t *o1 = new_int_object(5);
    object_t *o2 = new_int_object(5);
    munit_assert_int(objcmp(o1, o2), ==, 0);
    free(o1);
    free(o2);

    o1 = new_int_object(5);
    o2 = new_int_object(6);
    munit_assert_int(objcmp(o1, o2), <, 0);
    free(o1);
    free(o2);

    o1 = new_int_object(5);
    o2 = new_int_object(4);
    munit_assert_int(objcmp(o1, o2), >, 0);
    free(o1);
    free(o2);
    
    // FLOAT
    o1 = new_int_object(5.0);
    o2 = new_int_object(5.0);
    munit_assert_int(objcmp(o1, o2), ==, 0);
    free(o1);
    free(o2);

    o1 = new_int_object(5.0);
    o2 = new_int_object(6.0);
    munit_assert_int(objcmp(o1, o2), <, 0);
    free(o1);
    free(o2);

    o1 = new_int_object(5.0);
    o2 = new_int_object(4.0);
    munit_assert_int(objcmp(o1, o2), >, 0);
    
    // STR
    o1 = new_str_object("Hello World!");
    o2 = new_str_object("Hello World!");
    munit_assert_int(objcmp(o1, o2), ==, 0);
    
    o1 = new_str_object("Hello World!");
    o2 = new_str_object("hello world!");
    munit_assert_int(objcmp(o1, o2), <, 0);
    
    o1 = new_str_object("hello world!");
    o2 = new_str_object("Hello World!");
    munit_assert_int(objcmp(o1, o2), >, 0);

    return MUNIT_OK;
}

MunitTest *test_object_main() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest object_tests[] = {
    {
        "/test_int_object", /* name */
        test_int_object, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_float_object",
        test_float_object,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/test_str_object",
        test_str_object,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    {
        "/test_object_compare",
        test_object_compare,
        NULL,
        NULL,
        MUNIT_TEST_OPTION_NONE,
        NULL
    },
    /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };
    return object_tests;
}


// munit_case(RUN, test_get_average, {
//   float result = get_average(3, 4, 5);
//   munit_assert_double_equal(result, 4.0, "Average of 3, 4, 5 is 4");
// });

// munit_case(RUN, test_non_integer, {
//   float result = get_average(3, 3, 5);
//   munit_assert_double_equal(result, 11.0 / 3.0, "Average of 3, 3, 5 is 3.66667");
// });

// munit_case(SUBMIT, test_average_of_same, {
//   float result2 = get_average(10, 10, 10);
//   munit_assert_double_equal(result2, 10.0, "Average of 10s... is 10");
// });

// munit_case(SUBMIT, test_average_of_big_numbers, {
//   float result3 = get_average(1050, 2050, 2075);
//   munit_assert_double_equal(
//       result3, 1725.0, "Bigger numbers can still get averaged, duh!"
//   );
// });

// int main() {
//   MunitTest tests[] = {
//       munit_test("/get_average", test_get_average),
//       munit_test("/get_average_float", test_non_integer),
//       munit_test("/get_average_same", test_average_of_same),
//       munit_test("/get_average_big", test_average_of_big_numbers),
//       munit_null_test,
//   };

//   MunitSuite suite = munit_suite("get_average", tests);

//   return munit_suite_main(&suite, NULL, 0, NULL);
// }
