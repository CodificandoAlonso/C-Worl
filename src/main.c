/**
 * @file main.c
 * @brief Tests for dynamic_array and linked_list implementations
 */

#include "dynamic_array.h"
#include "linked_list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* ============================================
 *          HELPER FUNCTIONS
 * ============================================ */

static int *make_int(int value)
{
    int *ptr = malloc(sizeof(int));
    assert(ptr != NULL);
    *ptr = value;
    return ptr;
}

/* ============================================
 *          DYNAMIC ARRAY TESTS
 * ============================================ */

static void test_da_init_and_destroy(void)
{
    printf("Test: DA init and destroy... ");
    dynamic_array_t *arr = dynarray_init();
    assert(arr != NULL);
    assert(dynarray_size(arr) == 0);
    assert(dynarray_is_empty(arr) == true);
    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_push_and_get(void)
{
    printf("Test: DA push and get... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;
    int b = 20;
    int c = 30;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    assert(dynarray_size(arr) == 3);
    assert(*(int *) dynarray_get(arr, 0) == 10);
    assert(*(int *) dynarray_get(arr, 1) == 20);
    assert(*(int *) dynarray_get(arr, 2) == 30);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_push_single(void)
{
    printf("Test: DA push single element... ");
    dynamic_array_t *arr = dynarray_init();

    int  x      = 42;
    bool result = dynarray_push(arr, &x);

    assert(result == true);
    assert(dynarray_size(arr) == 1);
    assert(*(int *) dynarray_get(arr, 0) == 42);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_pop(void)
{
    printf("Test: DA pop... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 100;
    int b = 200;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);

    int *popped = (int *) dynarray_pop(arr);
    assert(*popped == 200);
    assert(dynarray_size(arr) == 1);

    popped = (int *) dynarray_pop(arr);
    assert(*popped == 100);
    assert(dynarray_size(arr) == 0);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_pop_empty(void)
{
    printf("Test: DA pop from empty... ");
    dynamic_array_t *arr = dynarray_init();

    void *result = dynarray_pop(arr);

    assert(result == NULL);
    assert(dynarray_size(arr) == 0);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_pop_until_empty(void)
{
    printf("Test: DA pop until empty... ");
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

static void test_da_growth(void)
{
    printf("Test: DA growth beyond initial capacity... ");
    dynamic_array_t *arr = dynarray_init();

    int values[50];
    for (int i = 0; i < 50; i++)
    {
        values[i]   = i * 10;
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
        int *val = (int *) dynarray_get(arr, (size_t) i);
        assert(*val == i * 10);
    }

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_growth_large(void)
{
    printf("Test: DA growth to 1000 elements... ");
    dynamic_array_t *arr = dynarray_init();

    int *values = malloc(1000 * sizeof(int));
    assert(values != NULL);

    for (int i = 0; i < 1000; i++)
    {
        values[i]   = i;
        bool result = dynarray_push(arr, &values[i]);
        assert(result == true);
    }

    assert(dynarray_size(arr) == 1000);

    for (int i = 0; i < 1000; i++)
    {
        int *val = (int *) dynarray_get(arr, (size_t) i);
        assert(*val == i);
    }

    dynarray_destroy(arr);
    free(values);
    printf("PASSED\n");
}

static void test_da_set_replace(void)
{
    printf("Test: DA set replaces existing element... ");
    dynamic_array_t *arr = dynarray_init();

    int a           = 1;
    int b           = 2;
    int c           = 3;
    int replacement = 999;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    dynarray_set(arr, 1, &replacement);

    assert(*(int *) dynarray_get(arr, 0) == 1);
    assert(*(int *) dynarray_get(arr, 1) == 999);
    assert(*(int *) dynarray_get(arr, 2) == 2);
    assert(dynarray_size(arr) == 4);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_set_first(void)
{
    printf("Test: DA set first element... ");
    dynamic_array_t *arr = dynarray_init();

    int a           = 10;
    int b           = 20;
    int replacement = 555;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);

    dynarray_set(arr, 0, &replacement);

    assert(*(int *) dynarray_get(arr, 0) == 555);
    assert(*(int *) dynarray_get(arr, 1) == 10);
    assert(dynarray_size(arr) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_set_last(void)
{
    printf("Test: DA set last element... ");
    dynamic_array_t *arr = dynarray_init();

    int a           = 10;
    int b           = 20;
    int c           = 30;
    int replacement = 777;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    dynarray_set(arr, 2, &replacement);

    assert(*(int *) dynarray_get(arr, 2) == 777);
    assert(dynarray_size(arr) == 4);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_set_append(void)
{
    printf("Test: DA set at size appends... ");
    dynamic_array_t *arr = dynarray_init();

    int a           = 10;
    int b           = 20;
    int new_element = 30;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);

    bool result = dynarray_set(arr, 2, &new_element);

    assert(result == true);
    assert(dynarray_size(arr) == 3);
    assert(*(int *) dynarray_get(arr, 2) == 30);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_get_empty(void)
{
    printf("Test: DA get from empty array... ");
    dynamic_array_t *arr = dynarray_init();

    void *result = dynarray_get(arr, 0);

    assert(result == NULL);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_get_boundaries(void)
{
    printf("Test: DA get at boundaries... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 100;
    int b = 200;
    int c = 300;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);

    assert(*(int *) dynarray_get(arr, 0) == 100);
    assert(*(int *) dynarray_get(arr, 2) == 300);

    void *out_of_bounds = dynarray_get(arr, 3);
    assert(out_of_bounds == NULL);

    void *way_out = dynarray_get(arr, 100);
    assert(way_out == NULL);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_is_empty(void)
{
    printf("Test: DA is_empty... ");
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

static void test_da_size_tracking(void)
{
    printf("Test: DA size tracking... ");
    dynamic_array_t *arr = dynarray_init();

    assert(dynarray_size(arr) == 0);

    int values[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        dynarray_push(arr, &values[i]);
        assert(dynarray_size(arr) == (size_t) (i + 1));
    }

    for (int i = 4; i >= 0; i--)
    {
        dynarray_pop(arr);
        assert(dynarray_size(arr) == (size_t) i);
    }

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_mixed_types(void)
{
    printf("Test: DA mixed pointer types... ");
    dynamic_array_t *arr = dynarray_init();

    int    integer   = 42;
    double floating  = 3.14159;
    char   character = 'X';
    char   string[6] = "hello";

    dynarray_push(arr, &integer);
    dynarray_push(arr, &floating);
    dynarray_push(arr, &character);
    dynarray_push(arr, string);

    assert(*(int *) dynarray_get(arr, 0) == 42);
    assert(*(double *) dynarray_get(arr, 1) == 3.14159);
    assert(*(char *) dynarray_get(arr, 2) == 'X');
    assert((char *) dynarray_get(arr, 3) == string);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_null_elements(void)
{
    printf("Test: DA storing NULL pointers... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 10;

    dynarray_push(arr, &a);
    dynarray_push(arr, NULL);
    dynarray_push(arr, &a);

    assert(*(int *) dynarray_get(arr, 0) == 10);
    assert(dynarray_get(arr, 1) == NULL);
    assert(*(int *) dynarray_get(arr, 2) == 10);
    assert(dynarray_size(arr) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_lifo_order(void)
{
    printf("Test: DA LIFO order (stack behavior)... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    dynarray_push(arr, &c);
    dynarray_push(arr, &d);

    assert(*(int *) dynarray_pop(arr) == 4);
    assert(*(int *) dynarray_pop(arr) == 3);
    assert(*(int *) dynarray_pop(arr) == 2);
    assert(*(int *) dynarray_pop(arr) == 1);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

static void test_da_push_pop_interleaved(void)
{
    printf("Test: DA interleaved push and pop... ");
    dynamic_array_t *arr = dynarray_init();

    int a = 1;
    int b = 2;
    int c = 3;

    dynarray_push(arr, &a);
    dynarray_push(arr, &b);
    assert(*(int *) dynarray_pop(arr) == 2);

    dynarray_push(arr, &c);
    assert(dynarray_size(arr) == 2);
    assert(*(int *) dynarray_get(arr, 0) == 1);
    assert(*(int *) dynarray_get(arr, 1) == 3);

    dynarray_destroy(arr);
    printf("PASSED\n");
}

/* ============================================
 *          LINKED LIST TESTS
 * ============================================ */

static void test_ll_init_and_delete(void)
{
    printf("Test: LL init and delete... ");
    linked_list_t *list = init_linkedlist();
    assert(list != NULL);
    assert(get_linked_list_size(list) == 0);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_delete_null(void)
{
    printf("Test: LL delete NULL list... ");
    delete_linkedlist(NULL);
    printf("PASSED\n");
}

static void test_ll_push_single(void)
{
    printf("Test: LL push single element... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(42));

    assert(get_linked_list_size(list) == 1);
    assert(*(int *) get_element(list, 0) == 42);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_push_multiple(void)
{
    printf("Test: LL push multiple elements... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(10));
    push_node(list, make_int(20));
    push_node(list, make_int(30));

    assert(get_linked_list_size(list) == 3);
    assert(*(int *) get_element(list, 0) == 10);
    assert(*(int *) get_element(list, 1) == 20);
    assert(*(int *) get_element(list, 2) == 30);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_pop_head_single(void)
{
    printf("Test: LL pop head from single element list... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(99));

    int *popped = (int *) pop_head(list);
    assert(*popped == 99);
    assert(get_linked_list_size(list) == 0);

    free(popped);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_pop_head_multiple(void)
{
    printf("Test: LL pop head from multiple elements... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    int *popped = (int *) pop_head(list);
    assert(*popped == 1);
    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 0) == 2);

    free(popped);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_pop_tail_single(void)
{
    printf("Test: LL pop tail from single element list... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(77));

    int *popped = (int *) pop_tail(list);
    assert(*popped == 77);
    assert(get_linked_list_size(list) == 0);

    free(popped);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_pop_tail_multiple(void)
{
    printf("Test: LL pop tail from multiple elements... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    int *popped = (int *) pop_tail(list);
    assert(*popped == 3);
    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 1) == 2);

    free(popped);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_pop_all_head(void)
{
    printf("Test: LL pop all elements from head... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    int *p1 = (int *) pop_head(list);
    int *p2 = (int *) pop_head(list);
    int *p3 = (int *) pop_head(list);

    assert(*p1 == 1);
    assert(*p2 == 2);
    assert(*p3 == 3);
    assert(get_linked_list_size(list) == 0);

    free(p1);
    free(p2);
    free(p3);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_pop_all_tail(void)
{
    printf("Test: LL pop all elements from tail... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    int *p1 = (int *) pop_tail(list);
    int *p2 = (int *) pop_tail(list);
    int *p3 = (int *) pop_tail(list);

    assert(*p1 == 3);
    assert(*p2 == 2);
    assert(*p3 == 1);
    assert(get_linked_list_size(list) == 0);

    free(p1);
    free(p2);
    free(p3);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_empty_list(void)
{
    printf("Test: LL insert into empty list at index 0... ");
    linked_list_t *list = init_linkedlist();

    insert_node(list, 0, make_int(100));

    assert(get_linked_list_size(list) == 1);
    assert(*(int *) get_element(list, 0) == 100);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_at_head(void)
{
    printf("Test: LL insert at head (index 0)... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    insert_node(list, 0, make_int(99));

    assert(get_linked_list_size(list) == 3);
    assert(*(int *) get_element(list, 0) == 99);
    assert(*(int *) get_element(list, 1) == 1);
    assert(*(int *) get_element(list, 2) == 2);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_at_tail(void)
{
    printf("Test: LL insert at tail... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    insert_node(list, 2, make_int(99));

    assert(get_linked_list_size(list) == 3);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 2);
    assert(*(int *) get_element(list, 2) == 99);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_middle(void)
{
    printf("Test: LL insert in middle... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(3));
    insert_node(list, 1, make_int(2));

    assert(get_linked_list_size(list) == 3);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 2);
    assert(*(int *) get_element(list, 2) == 3);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_multiple_middle(void)
{
    printf("Test: LL multiple inserts in middle... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(5));
    insert_node(list, 1, make_int(2));
    insert_node(list, 2, make_int(3));
    insert_node(list, 3, make_int(4));

    assert(get_linked_list_size(list) == 5);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 2);
    assert(*(int *) get_element(list, 2) == 3);
    assert(*(int *) get_element(list, 3) == 4);
    assert(*(int *) get_element(list, 4) == 5);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_remove_head(void)
{
    printf("Test: LL remove head... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    remove_node(list, 0);

    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 0) == 2);
    assert(*(int *) get_element(list, 1) == 3);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_remove_tail(void)
{
    printf("Test: LL remove tail... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    remove_node(list, 2);

    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 2);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_remove_middle(void)
{
    printf("Test: LL remove middle... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    remove_node(list, 1);

    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 3);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_remove_single(void)
{
    printf("Test: LL remove single element... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(42));

    remove_node(list, 0);

    assert(get_linked_list_size(list) == 0);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_remove_all(void)
{
    printf("Test: LL remove all elements... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    remove_node(list, 1);
    remove_node(list, 1);
    remove_node(list, 0);

    assert(get_linked_list_size(list) == 0);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_get_element_head(void)
{
    printf("Test: LL get element at head... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(111));
    push_node(list, make_int(222));

    assert(*(int *) get_element(list, 0) == 111);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_get_element_tail(void)
{
    printf("Test: LL get element at tail... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(111));
    push_node(list, make_int(222));
    push_node(list, make_int(333));

    assert(*(int *) get_element(list, 2) == 333);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_get_element_middle(void)
{
    printf("Test: LL get element in middle... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(10));
    push_node(list, make_int(20));
    push_node(list, make_int(30));
    push_node(list, make_int(40));
    push_node(list, make_int(50));

    assert(*(int *) get_element(list, 2) == 30);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_size_tracking(void)
{
    printf("Test: LL size tracking through operations... ");
    linked_list_t *list = init_linkedlist();

    assert(get_linked_list_size(list) == 0);

    push_node(list, make_int(1));
    assert(get_linked_list_size(list) == 1);

    push_node(list, make_int(2));
    assert(get_linked_list_size(list) == 2);

    push_node(list, make_int(3));
    assert(get_linked_list_size(list) == 3);

    int *p = (int *) pop_head(list);
    free(p);
    assert(get_linked_list_size(list) == 2);

    p = (int *) pop_tail(list);
    free(p);
    assert(get_linked_list_size(list) == 1);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_mixed_operations(void)
{
    printf("Test: LL mixed push/pop operations... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));

    int *p = (int *) pop_head(list);
    free(p);

    push_node(list, make_int(3));
    push_node(list, make_int(4));

    p = (int *) pop_tail(list);
    free(p);

    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 0) == 2);
    assert(*(int *) get_element(list, 1) == 3);

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_doubly_linked_traversal(void)
{
    printf("Test: LL doubly linked structure integrity... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));

    int *p1 = (int *) pop_head(list);
    int *p2 = (int *) pop_tail(list);
    int *p3 = (int *) pop_head(list);

    assert(*p1 == 1);
    assert(*p2 == 3);
    assert(*p3 == 2);
    assert(get_linked_list_size(list) == 0);

    free(p1);
    free(p2);
    free(p3);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_large_list(void)
{
    printf("Test: LL large list (100 elements)... ");
    linked_list_t *list = init_linkedlist();

    for (int i = 0; i < 100; i++)
    {
        push_node(list, make_int(i * 10));
    }

    assert(get_linked_list_size(list) == 100);

    for (int i = 0; i < 100; i++)
    {
        assert(*(int *) get_element(list, (size_t) i) == i * 10);
    }

    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_preserves_links(void)
{
    printf("Test: LL insert preserves prev/next links... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(4));
    insert_node(list, 1, make_int(2));
    insert_node(list, 2, make_int(3));

    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 2);
    assert(*(int *) get_element(list, 2) == 3);
    assert(*(int *) get_element(list, 3) == 4);

    int *p1 = (int *) pop_tail(list);
    int *p2 = (int *) pop_tail(list);
    int *p3 = (int *) pop_tail(list);
    int *p4 = (int *) pop_tail(list);

    assert(*p1 == 4);
    assert(*p2 == 3);
    assert(*p3 == 2);
    assert(*p4 == 1);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_remove_preserves_links(void)
{
    printf("Test: LL remove preserves prev/next links... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(2));
    push_node(list, make_int(3));
    push_node(list, make_int(4));
    push_node(list, make_int(5));

    remove_node(list, 2);

    assert(get_linked_list_size(list) == 4);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 2);
    assert(*(int *) get_element(list, 2) == 4);
    assert(*(int *) get_element(list, 3) == 5);

    int *p1 = (int *) pop_tail(list);
    int *p2 = (int *) pop_tail(list);

    assert(*p1 == 5);
    assert(*p2 == 4);

    free(p1);
    free(p2);
    delete_linkedlist(list);
    printf("PASSED\n");
}

static void test_ll_insert_then_remove(void)
{
    printf("Test: LL insert then remove... ");
    linked_list_t *list = init_linkedlist();

    push_node(list, make_int(1));
    push_node(list, make_int(3));
    insert_node(list, 1, make_int(2));

    assert(get_linked_list_size(list) == 3);

    remove_node(list, 1);

    assert(get_linked_list_size(list) == 2);
    assert(*(int *) get_element(list, 0) == 1);
    assert(*(int *) get_element(list, 1) == 3);

    delete_linkedlist(list);
    printf("PASSED\n");
}

/* ============================================
 *               MAIN
 * ============================================ */

int main(void)
{
    printf("\n========================================\n");
    printf("         DYNAMIC ARRAY TESTS\n");
    printf("========================================\n\n");

    test_da_init_and_destroy();
    test_da_push_single();
    test_da_push_and_get();
    test_da_pop();
    test_da_pop_empty();
    test_da_pop_until_empty();
    test_da_is_empty();
    test_da_size_tracking();
    test_da_growth();
    test_da_growth_large();
    test_da_get_empty();
    test_da_get_boundaries();
    test_da_set_replace();
    test_da_set_first();
    test_da_set_last();
    test_da_set_append();
    test_da_mixed_types();
    test_da_null_elements();
    test_da_lifo_order();
    test_da_push_pop_interleaved();

    printf("\n========================================\n");
    printf("          LINKED LIST TESTS\n");
    printf("========================================\n\n");

    test_ll_init_and_delete();
    test_ll_delete_null();
    test_ll_push_single();
    test_ll_push_multiple();
    test_ll_pop_head_single();
    test_ll_pop_head_multiple();
    test_ll_pop_tail_single();
    test_ll_pop_tail_multiple();
    test_ll_pop_all_head();
    test_ll_pop_all_tail();
    test_ll_insert_empty_list();
    test_ll_insert_at_head();
    test_ll_insert_at_tail();
    test_ll_insert_middle();
    test_ll_insert_multiple_middle();
    test_ll_remove_head();
    test_ll_remove_tail();
    test_ll_remove_middle();
    test_ll_remove_single();
    test_ll_remove_all();
    test_ll_get_element_head();
    test_ll_get_element_tail();
    test_ll_get_element_middle();
    test_ll_size_tracking();
    test_ll_mixed_operations();
    test_ll_doubly_linked_traversal();
    test_ll_large_list();
    test_ll_insert_preserves_links();
    test_ll_remove_preserves_links();
    test_ll_insert_then_remove();

    printf("\n========================================\n");
    printf("    All 50 tests completed\n");
    printf("========================================\n\n");

    return EXIT_SUCCESS;
}
