//
// Created by hectoralv22 on 1/3/26.
//


//LIFO ARRAY



#include "dynamic_array.h"
#include "utils.h"
#include "stdlib.h"
#include "stdio.h"
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
  free(arr);
}


bool dynarray_push(dynamic_array_t *arr, void *element){

  if (arr->size == arr ->capacity){
    fprintf(stderr, "WE ARE FUCKED IF THIS HAPPENSSSS");
    _exit(EXIT_FAILURE);
  }
  //Review size of the array, compare it to the initial capacity and see if it
  // is on the limit, if not realloc memory

  if (arr->size == arr ->capacity) //Capacity is initial capacity
  {
    //REALLOCATE
    void ** try_realloc = (void **)realloc(arr->data,
                  (arr->size + DYNARRAY_GROWTH_FACTOR) * sizeof(void *));
    if (try_realloc == NULL)
    {
      free((void *)arr->data);
      fprintf(stderr, "ERROR REALOCATING DATA");
      _exit(EXIT_FAILURE);
    }
    free((void *)try_realloc);
    arr->data[arr->size++] = element;
    return TRUE;
  }

  arr->data[arr->size++] = element;
  return TRUE;
}


void *dynarray_pop(dynamic_array_t *arr){

}


void *dynarray_get(const dynamic_array_t *arr, size_t index){

}



bool dynarray_set(dynamic_array_t *arr, size_t index, void *element){

}



size_t dynarray_size(const dynamic_array_t *arr){

}



bool dynarray_is_empty(const dynamic_array_t *arr){


}
