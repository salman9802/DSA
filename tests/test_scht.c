// Separate Chaining Hash Table

#include "munit.h"

#include "object.h"
#include "scht.h"

MunitResult test_scht_fnv_a1() {
   
    // printf("\n==============================================\n");
    // printf("OFFSET = %llu\n", (unsigned long long)SCHT_FNV_OFFSET_BASIS_64);
    // printf("PRIME  = %llu\n", (unsigned long long)SCHT_FNV_PRIME64);
    // printf("hash('a') = %llu\n", (unsigned long long)fnv_1a((const unsigned char*)"a"));
    // printf("\n==============================================\n");

    
    // Known test vectors (offical, published in the FNV docs)
    munit_assert_uint64(fnv_1a((const unsigned char *)""),==, 14695981039346656037ULL);
    munit_assert_uint64(fnv_1a((const unsigned char *)"a"),==, 12638187200555641996ULL);
    munit_assert_uint64(fnv_1a((const unsigned char *)"hello"),==, 11831194018420276491ULL);
    // munit_assert_uint64(fnv_1a((const unsigned char *)"Hello World!"),==, 11873506992876687039ULL);
    // munit_assert_uint64(fnv_1a((const unsigned char *)"Hello World!"),==, 8634993348086049511ULL);
    munit_assert_uint64(fnv_1a((const unsigned char *)"Hello World!"),==, 10092224619179044402ULL);


    // Determinism Test
    uint64_t h1 = fnv_1a((const unsigned char *)"abcdef");
    uint64_t h2 = fnv_1a((const unsigned char *)"abcdef");

    munit_assert_uint64(h1, ==, h2);


    // Distinctness (not equal for different strings)
    munit_assert_uint64(fnv_1a((const unsigned char *)"abc"), !=, fnv_1a((const unsigned char *)"abcd"));
    munit_assert_uint64(fnv_1a((const unsigned char *)"abc"), !=, fnv_1a((const unsigned char *)"abC"));
    munit_assert_uint64(fnv_1a((const unsigned char *)"abc"), !=, fnv_1a((const unsigned char *)"xyz"));

    // Empty string (offical)
    munit_assert_uint64(fnv_1a((const unsigned char *)""), ==, 14695981039346656037ULL);

    // Test for characters with high-bit set (unsigned char check)
    unsigned char s[] = { 0xFF, 0x00 };
    fnv_1a((const unsigned char *)s);   // should NOT crash and should match expected signed-safe behavior

    return MUNIT_OK;
}

MunitResult test_new_scht() {
    int n = 10;
    scht_t *scht = new_scht(n);

    munit_assert_size(scht->capacity, ==, (size_t) 1 << n);
    munit_assert_size(scht->element_count, ==, 0);
    munit_assert_size(scht->max_load_factor, ==, 0.75);

    for(size_t i = 0; i < scht->capacity; i++)
        munit_assert_ptr(scht->buckets[i], ==, NULL);
    
    return MUNIT_OK;
}

MunitResult test_scht_set() {
    int n = 10;
    scht_t *scht = new_scht(n);

    scht_set(scht, "Hello World!", new_int_object(1));
    
    return MUNIT_OK;
}

MunitResult test_scht_get() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    int n = 10;
    scht_t *scht = new_scht(n);
    
    scht_set(scht, "o1", o1);
    scht_set(scht, "o2", o2);
    scht_set(scht, "o3", o3);

    munit_assert_ptr(scht_get(scht, "o1"), ==, o1);
    munit_assert_ptr(scht_get(scht, "o2"), ==, o2);
    munit_assert_ptr(scht_get(scht, "o3"), ==, o3);
    
    munit_assert_size(scht->element_count, ==, 3);
    
    return MUNIT_OK;
}

MunitResult test_scht_remove() {
    int i1 = 1, i2 = 2, i3 = 3;
    object_t *o1, *o2, *o3;
    o1 = new_int_object(i1);
    o2 = new_int_object(i2);
    o3 = new_int_object(i3);

    int n = 10;
    scht_t *scht = new_scht(n);
    
    scht_set(scht, "o1", o1);
    scht_set(scht, "o2", o2);
    scht_set(scht, "o3", o3);

    munit_assert_ptr(scht_remove(scht, "o1"), ==, o1);
    munit_assert_ptr(scht_remove(scht, "o1"), ==, NULL);
    munit_assert_ptr(scht_remove(scht, "o2"), ==, o2);
    munit_assert_ptr(scht_remove(scht, "o2"), ==, NULL);
    munit_assert_ptr(scht_remove(scht, "o3"), ==, o3);
    munit_assert_ptr(scht_remove(scht, "o3"), ==, NULL);
    munit_assert_ptr(scht_remove(scht, "o2"), ==, NULL);
    munit_assert_ptr(scht_remove(scht, "o1"), ==, NULL);
    munit_assert_ptr(scht_remove(scht, "anything-else"), ==, NULL);
    
    munit_assert_size(scht->element_count, ==, 0);
    
    return MUNIT_OK;
}

MunitSuite *test_scht_suite() {
    // int foo = 3, bar = 3;
    // munit_assert_int(foo, ==, bar);
    static MunitTest scht_tests[] = {
    {
        "/test_scht_fnv_a1", /* name */
        test_scht_fnv_a1, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_new_scht", /* name */
        test_new_scht, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_scht_set", /* name */
        test_scht_set, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_scht_get", /* name */
        test_scht_get, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
    {
        "/test_scht_remove", /* name */
        test_scht_remove, /* test */
        NULL, /* setup */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL /* parameters */
    },
   /* Mark the end of the array with an entry where the test
    * function is NULL */
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }    };

    static MunitSuite suite = {
        "/separate_chaining_hash_table", /* name */
        scht_tests, /* tests */
        NULL, /* suites */
        1, /* iterations */
        MUNIT_SUITE_OPTION_NONE /* options */
    };
    return &suite;
}