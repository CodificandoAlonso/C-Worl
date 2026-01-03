//
// Created by hectoralv22 on 1/3/26.
//


//LIFO ARRAY



#include "dynamic_array.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


dynamic_array_t *dynarray_init(void){

  dynamic_array_t *arr = malloc(sizeof(dynamic_array_t));
  if (arr == NULL)
  {
    fprintf(stderr, "ERROR CREATING DYNAMIC ARRAY");
    _exit(EXIT_FAILURE);
  }

  arr->data =(void **) malloc(DYNARRAY_INITIAL_CAPACITY * sizeof (void *));

  if (arr->data == NULL)
  {
    fprintf(stderr, "ERROR CREATING SPACE FOR DATA");
    _exit(EXIT_FAILURE);
  }

  arr->capacity = DYNARRAY_INITIAL_CAPACITY;
  arr->size = ZERO;
  return arr;
}



void dynarray_destroy(dynamic_array_t *arr){
  free((void *)arr->data);
  free(arr);
}


bool dynarray_push(dynamic_array_t *arr, void *element){

  if (arr->size > arr ->capacity){
    fprintf(stderr, "WE ARE FUCKED IF THIS HAPPENSSSS");
    return FALSE;
  }

  //Review size of the array, compare it to the initial capacity and see if it
  // is on the limit, if not realloc memory
  if (arr->size == arr ->capacity) //Capacity is initial capacity or the modified
  {
    //REALLOCATE
    void **test_realloc = (void **)realloc(arr->data,
                  (arr->capacity + DYNARRAY_GROWTH_FACTOR) * sizeof(void *));
    if (test_realloc == NULL)
    {
      free((void *)test_realloc);
      fprintf(stderr, "ERROR REALOCATING DATA");
      return FALSE;
    }
    arr->data = test_realloc;
    arr->data[arr->size++] = element;

    //As we make bigger the dynamic array
    arr->capacity += DYNARRAY_GROWTH_FACTOR;

    return TRUE;
  }
  arr->data[arr->size++] = element;
  return TRUE;
}



void *dynarray_pop(dynamic_array_t *arr){
  if (arr->size > 0) {
    return arr->data[arr->size-- - ONE];
  }
  return NULL;
}


void *dynarray_get(const dynamic_array_t *arr, size_t index){

  //Check the boundaries
  if (arr->size == 0) {
    return NULL;
  }
  if (index > arr->size - ONE) {
    return NULL;
  }
  return arr->data[index];
}



bool dynarray_set(dynamic_array_t *arr, size_t index, void *element){


  if (index == arr->size) {
    if (dynarray_push(arr, element) == TRUE) {
      return TRUE;
    }
    {
      return FALSE;
    }
  }

  if (index > arr->size) {
    fprintf(stderr, "There is no such index");
    _exit(EXIT_FAILURE);
  }

  //Tricky element, if the size == capacity, we need to realloc before inserting
  //otherwise will be segmentation fault
  if (arr->size == arr->capacity) {
    //REALLOCATE
    void **test_realloc = (void **)realloc(arr->data,
                  (arr->capacity + DYNARRAY_GROWTH_FACTOR) * sizeof(void *));
    if (test_realloc == NULL)
    {
      free(test_realloc);
      fprintf(stderr, "ERROR REALOCATING DATA");
      return FALSE;
    }
    arr->data = test_realloc;
  }

  //Base and easy case
  //Now Simply moves every index +1 element one more and insert the new
  for (size_t iter = arr->size; iter > index; iter --) {
    arr->data[iter] = arr->data[iter - 1];
  }
  arr->data[index] = element;
  arr->size ++;
  //In the other hand,


  return TRUE;
}



size_t dynarray_size(const dynamic_array_t *arr){
  return arr->size;
}



bool dynarray_is_empty(const dynamic_array_t *arr){
  if (arr->size == ZERO) {
    return TRUE;
  }
  return FALSE;
}
