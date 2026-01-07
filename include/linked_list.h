//
// Created by hectoralv22 on 1/4/26.
//

#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef C_WORL_LINKED_LIST_H
#define C_WORL_LINKED_LIST_H

typedef struct node_t
{
    void *prev;
    void *value;
    void *next;
} node_t;

typedef struct linked_list_t
{
    node_t *head;
    node_t *tail;
    size_t  len;
} linked_list_t;

linked_list_t *init_linkedlist(void);

node_t *create_node(void *data);

void delete_linkedlist(linked_list_t *list);

void push_node(linked_list_t *list, void *data);

void *pop_head(linked_list_t *list);

void *pop_tail(linked_list_t *list);

void insert_node(linked_list_t *list, size_t index, void *data);

void remove_node(linked_list_t *list, size_t index);

size_t get_linked_list_size(const linked_list_t *list);

void *get_element(linked_list_t *list, size_t index);

void *rec_get_element(node_t *actual, size_t index);

#endif // C_WORL_LINKED_LIST_H
