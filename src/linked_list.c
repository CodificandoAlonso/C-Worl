//
// Created by hectoralv22 on 1/4/26.
//

#include "linked_list.h"

#include "dynamic_array.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

linked_list_t *init_linkedlist(void)
{
    // CREATE SPACE FOR THE STRUCT
    linked_list_t *ll = malloc(sizeof(linked_list_t));
    check_mem_alloc(ll, "Linked list init");
    // PARAMETERS
    ll->len  = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

void delete_linkedlist(linked_list_t *list)
{

    if (list == NULL)
    {
        return;
    }

    // Caso facil, no hay elementos en la lista. Free de la estructura
    if (list->len == 0)
    {
        free(list);
        return;
    }

    node_t *base = list->tail;

    while (base->prev != NULL)
    {
        node_t *new_base = base->prev;
        free(base);
        base = new_base;
    }
    free(base);
    free(list);
}

node_t *create_node(void *data)
{
    node_t *new_node = malloc(sizeof(node_t));
    check_mem_alloc(new_node, "Error creating Node");
    new_node->prev  = NULL;
    new_node->next  = NULL;
    new_node->value = data;
    return new_node;
}

void push_node(linked_list_t *list, void *data)
{
    node_t *new_node = create_node(data);
    if (list->len == 0)
    {
        list->head = new_node;
        list->tail = new_node;
        list->len++;
        return;
    }
    new_node->prev   = list->tail;
    list->tail->next = new_node;
    list->tail       = new_node;
    list->len++;
}

void *pop_head(linked_list_t *list)
{
    if (list->len == 0)
    {
        throw_error("No elements in linked list");
    }
    node_t *return_node = list->head;
    if (list->len == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        node_t *new_head = list->head->next;
        new_head->prev   = NULL;
        list->head       = new_head;
    }
    list->len--;
    void *value = return_node->value;
    free(return_node);
    return value;
}

void *pop_tail(linked_list_t *list)
{
    if (list->len == 0)
    {
        throw_error("No elements in linked list");
    }
    node_t *return_node = list->tail;
    if (list->len == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->tail       = return_node->prev;
        list->tail->next = NULL;
    }

    list->len--;
    void *return_value = return_node->value;
    free(return_node);
    return return_value;
}



bool insert_node(linked_list_t *list, size_t index, void *data){

    if (index > list->len)
    {
        throw_error("Too much index size for the ll");
    }

    if (index == 0)
    {

    }



}

bool remove_node(linked_list_t *list, size_t index){



}

size_t get_linked_list_size(const linked_list_t *list){
    return list->len;
}


void *get_element(linked_list_t *list, size_t index){

    if (list->len == 0)
    {
        throw_error("empty list");
    }
    if (index > list->len -1)
    {
        throw_error("No index in list");
    }
    if (index == 0)
    {
        return list->head->value;
    }
    return _get_element(list->head, index - (size_t)ONE);
}



void *_get_element(node_t *actual, size_t index)
{
    if (index == 0)
    {
        return actual->value;
    }
    return _get_element((node_t *)actual->next, index - (size_t)ONE);
}