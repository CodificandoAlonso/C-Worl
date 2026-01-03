/**
 * @file dynamic_array.h
 * @brief Generic dynamic array implementation
 *
 * A growable array that doubles capacity on overflow.
 * Time: O(1) amortized append, O(1) access
 * Space: O(n)
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

#define DYNARRAY_INITIAL_CAPACITY 16
#define DYNARRAY_GROWTH_FACTOR    2


typedef struct dynamic_array_t
{
    void   **data;
    size_t   size;
    size_t   capacity;
} dynamic_array_t;

/**
 * @brief Initialize a new dynamic array
 * @param arr Pointer to array structure
 * @return true on success, false on allocation failure
 */
bool dynarray_init(dynamic_array_t *arr);

/**
 * @brief Free all memory associated with the array
 * @param arr Pointer to array structure
 */
void dynarray_destroy(dynamic_array_t *arr);

/**
 * @brief Append an element to the end
 * @param arr Pointer to array structure
 * @param element Element to append
 * @return true on success, false on allocation failure
 */
bool dynarray_push(dynamic_array_t *arr, void *element);

/**
 * @brief Remove and return the last element
 * @param arr Pointer to array structure
 * @return Last element, or NULL if empty
 */
void *dynarray_pop(dynamic_array_t *arr);

/**
 * @brief Get element at index
 * @param arr Pointer to array structure
 * @param index Index to access
 * @return Element at index, or NULL if out of bounds
 */
void *dynarray_get(const dynamic_array_t *arr, size_t index);

/**
 * @brief Set element at index
 * @param arr Pointer to array structure
 * @param index Index to set
 * @param element Element to store
 * @return true on success, false if out of bounds
 */
bool dynarray_set(dynamic_array_t *arr, size_t index, void *element);

/**
 * @brief Get current size
 * @param arr Pointer to array structure
 * @return Number of elements
 */
size_t dynarray_size(const dynamic_array_t *arr);

/**
 * @brief Check if array is empty
 * @param arr Pointer to array structure
 * @return true if empty
 */
bool dynarray_is_empty(const dynamic_array_t *arr);

#endif /* DYNAMIC_ARRAY_H */
