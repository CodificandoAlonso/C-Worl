/**
 * @file main.c
 * @brief Tests for dynamic_array implementation
 */

#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void test_init_and_destroy(void)
{
    printf("Test: init and destroy... ");
    dynamic_array_t *arr = dynarray_init();
    assert(arr != NULL);
    assert(dynarray_size(arr) == 0);
    assert(dynarray_is_empty(arr) == true);
    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_push_and_get(void)
{
    printf("Test: push and get... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;
    int b = 20;
    int c = 30;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    assert(dynarray_size(arr) == 3);
    assert(*(int *)dynarray_get(arr, 0) == 10);
    assert(*(int *)dynarray_get(arr, 1) == 20);
    assert(*(int *)dynarray_get(arr, 2) == 30);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_push_single(void)
{
    printf("Test: push single element... ");
    dynamic_array_t *arr = dynarray_init();

    int x = 42;
    bool result = dynarray_push(arr, &x);

    assert(result == true);
    assert(dynarray_size(arr) == 1);
    assert(*(int *)dynarray_get(arr, 0) == 42);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_pop(void)
{
    printf("Test: pop... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 100;
    int b = 200;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);

    int *popped = (int *)dynarray_pop(arr);
    assert(*popped == 200);
    assert(dynarray_size(arr) == 1);

    popped = (int *)dynarray_pop(arr);
    assert(*popped == 100);
    assert(dynarray_size(arr) == 0);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_pop_empty(void)
{
    printf("Test: pop from empty... ");
    dynamic_array_t *arr = dynarray_init();

    void *result = dynarray_pop(arr);

    assert(result == NULL);
    assert(dynarray_size(arr) == 0);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_pop_until_empty(void)
{
    printf("Test: pop until empty... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 1;
    int b = 2;
    int c = 3;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    dynarray_pop(arr);
    dynarray_pop(arr);
    dynarray_pop(arr);

    assert(dynarray_is_empty(arr) == true);
    assert(dynarray_size(arr) == 0);

    void *result = dynarray_pop(arr);
    assert(result == NULL);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_growth(void)
{
    printf("Test: growth beyond initial capacity... ");
    dynamic_array_t *arr = dynarray_init();

    int values[50];
    for (int i = 0; i < 50; i++)
    {
        values[i] = i * 10;
        bool result = dynarray_push(arr, &values[i]);
        if (!result)
        {
            printf("FAILED at element %d\n", i);
            dynarray_destroy(arr);
            return;
        }
    }

    assert(dynarray_size(arr) == 50);

    for (int i = 0; i < 50; i++)
    {
        int *val = (int *)dynarray_get(arr, (size_t)i);
        assert(*val == i * 10);
    }

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_growth_large(void)
{
    printf("Test: growth to 1000 elements... ");
    dynamic_array_t *arr = dynarray_init();

    int *values = malloc(1000 * sizeof(int));
    assert(values != NULL);

    for (int i = 0; i < 1000; i++)
    {
        values[i] = i;
        bool result = dynarray_push(arr, &values[i]);
        assert(result == true);
    }

    assert(dynarray_size(arr) == 1000);

    for (int i = 0; i < 1000; i++)
    {
        int *val = (int *)dynarray_get(arr, (size_t)i);
        assert(*val == i);
    }

    dynarray_destroy(arr);
    free(values);
    printf("PASSED\n");
}

static void test_set_replace(void)
{
    printf("Test: set replaces existing element... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 1;
    int b = 2;
    int c = 3;
    int replacement = 999;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    dynarray_set(arr, 1, &replacement);

    assert(*(int *)dynarray_get(arr, 0) == 1);
    assert(*(int *)dynarray_get(arr, 1) == 999);
    assert(*(int *)dynarray_get(arr, 2) == 3);
    assert(dynarray_size(arr) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_set_first(void)
{
    printf("Test: set first element... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;
    int b = 20;
    int replacement = 555;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);

    dynarray_set(arr, 0, &replacement);

    assert(*(int *)dynarray_get(arr, 0) == 555);
    assert(*(int *)dynarray_get(arr, 1) == 20);
    assert(dynarray_size(arr) == 2);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_set_last(void)
{
    printf("Test: set last element... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;
    int b = 20;
    int c = 30;
    int replacement = 777;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    dynarray_set(arr, 2, &replacement);

    assert(*(int *)dynarray_get(arr, 2) == 777);
    assert(dynarray_size(arr) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_set_append(void)
{
    printf("Test: set at size appends... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;
    int b = 20;
    int new_element = 30;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);

    bool result = dynarray_set(arr, 2, &new_element);

    assert(result == true);
    assert(dynarray_size(arr) == 3);
    assert(*(int *)dynarray_get(arr, 2) == 30);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_get_empty(void)
{
    printf("Test: get from empty array... ");
    dynamic_array_t *arr = dynarray_init();

    void *result = dynarray_get(arr, 0);

    assert(result == NULL);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_get_boundaries(void)
{
    printf("Test: get at boundaries... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 100;
    int b = 200;
    int c = 300;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    assert(*(int *)dynarray_get(arr, 0) == 100);
    assert(*(int *)dynarray_get(arr, 2) == 300);

    void *out_of_bounds = dynarray_get(arr, 3);
    assert(out_of_bounds == NULL);

    void *way_out = dynarray_get(arr, 100);
    assert(way_out == NULL);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_is_empty(void)
{
    printf("Test: is_empty... ");
    dynamic_array_t *arr = dynarray_init();

    assert(dynarray_is_empty(arr) == true);

    int x = 42;
    dynarray_push(arr, &x);
    assert(dynarray_is_empty(arr) == false);

    dynarray_pop(arr);
    assert(dynarray_is_empty(arr) == true);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_size_tracking(void)
{
    printf("Test: size tracking... ");
    dynamic_array_t *arr = dynarray_init();

    assert(dynarray_size(arr) == 0);

    int values[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        dynarray_push(arr, &values[i]);
        assert(dynarray_size(arr) == (size_t)(i + 1));
    }

    for (int i = 4; i >= 0; i--)
    {
        dynarray_pop(arr);
        assert(dynarray_size(arr) == (size_t)i);
    }

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_mixed_types(void)
{
    printf("Test: mixed pointer types... ");
    dynamic_array_t *arr = dynarray_init();

    int integer = 42;
    double floating = 3.14159;
    char character = 'X';
    char string[6] = "hello";

    dynarray_push(arr, &integer);
    dynarray_push(arr, &floating);
    dynarray_push(arr, &character);
    dynarray_push(arr, string);

    assert(*(int *)dynarray_get(arr, 0) == 42);
    assert(*(double *)dynarray_get(arr, 1) == 3.14159);
    assert(*(char *)dynarray_get(arr, 2) == 'X');
    assert((char *)dynarray_get(arr, 3) == string);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_null_elements(void)
{
    printf("Test: storing NULL pointers... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;

    dynarray_push(arr, &a);
    dynarray_push(arr, NULL);
    dynarray_push(arr, &a);

    assert(*(int *)dynarray_get(arr, 0) == 10);
    assert(dynarray_get(arr, 1) == NULL);
    assert(*(int *)dynarray_get(arr, 2) == 10);
    assert(dynarray_size(arr) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_lifo_order(void)
{
    printf("Test: LIFO order (stack behavior)... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);
    dynarray_push(arr, &d);

    assert(*(int *)dynarray_pop(arr) == 4);
    assert(*(int *)dynarray_pop(arr) == 3);
    assert(*(int *)dynarray_pop(arr) == 2);
    assert(*(int *)dynarray_pop(arr) == 1);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_push_pop_interleaved(void)
{
    printf("Test: interleaved push and pop... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 1;
    int b = 2;
    int c = 3;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    assert(*(int *)dynarray_pop(arr) == 2);

    dynarray_push(arr, &c);
    assert(dynarray_size(arr) == 2);
    assert(*(int *)dynarray_get(arr, 0) == 1);
    assert(*(int *)dynarray_get(arr, 1) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

int main(void)
{
    printf("\n=== Dynamic Array Tests ===\n\n");

    test_init_and_destroy();
    test_push_single();
    test_push_and_get();
    test_pop();
    test_pop_empty();
    test_pop_until_empty();
    test_is_empty();
    test_size_tracking();
    test_growth();
    test_growth_large();
    test_get_empty();
    test_get_boundaries();
    test_set_replace();
    test_set_first();
    test_set_last();
    test_set_append();
    test_mixed_types();
    test_null_elements();
    test_lifo_order();
    test_push_pop_interleaved();

    printf("\n=== All %d tests completed ===\n\n", 20);
    return EXIT_SUCCESS;
}
