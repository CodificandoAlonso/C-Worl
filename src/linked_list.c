//
// Created by hectoralv22 on 1/4/26.
//

#include "linked_list.h"

#include "dynamic_array.h"
#include "utils.h"

#include <stdlib.h>

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
        free(base->value);
        free(base);
        base = new_base;
    }
    free(base->value);
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
    if (list->len == (size_t) ZERO)
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
    if (list->len == (size_t) ZERO)
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
    if (list->len == (size_t) ZERO)
    {
        throw_error("No elements in linked list");
    }
    node_t *return_node = list->tail;
    if (list->len == (size_t) ONE)
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

void insert_node(linked_list_t *list, size_t index, void *data)
{

    if (index > list->len || (index > 0 && list->len == 0))
    {
        throw_error("Too much index size for the ll");
    }

    node_t *node_to_insert = create_node(data);

    // Case ll empty and insert in index 0(ALLOWED)
    if (list->len == 0 && index == 0)
    {
        list->head = node_to_insert;
        list->tail = node_to_insert;
        list->len++;
        return;
    }

    // Case push to head.
    if (index == 0)
    {
        list->head->prev     = node_to_insert;
        node_to_insert->next = list->head;
        list->head           = node_to_insert;
        list->len++;
        return;
    }

    // Case push to tail
    if (index == list->len)
    {
        node_to_insert->prev = list->tail;
        list->tail->next     = node_to_insert;
        list->tail           = node_to_insert;
        list->len++;
        return;
    }

    node_t *iter_node = list->head;
    node_t *next_node = list->head->next;
    // general case. Navigate till the element and insert it
    for (size_t i = 1; i < index; i++)
    {
        iter_node = iter_node->next;
        next_node = iter_node->next;
    }

    node_to_insert->next = iter_node->next;
    node_to_insert->prev = iter_node;
    next_node->prev      = node_to_insert;
    iter_node->next      = node_to_insert;
    list->len++;
}

void remove_node(linked_list_t *list, size_t index)
{

    if (list->len == 0)
    {
        throw_error("EMPTY LL");
    }

    // Check boundaries
    if (index > list->len - (size_t) ONE)
    {
        throw_error("INDEX OUT OF BOUNDARIES");
    }

    if (index == 0)
    {
        // As pop head return a pointer to the data, we save and free it
        void *data = pop_head(list);
        free(data);
        return;
    }
    if (index == list->len - (size_t) ONE)
    {
        // Same as pop_head, but with the tail
        void *data = pop_tail(list);
        free(data);
        return;
    }

    // General case. Navigate till the index of the element
    node_t *index_node = list->head;

    for (size_t i = 0; i < index; i++)
    {
        index_node = index_node->next;
    }
    ((node_t *) index_node->prev)->next = index_node->next;
    ((node_t *) index_node->next)->prev = index_node->prev;
    free(index_node->value);
    free(index_node);
    list->len--;
}

size_t get_linked_list_size(const linked_list_t *list)
{
    return list->len;
}

void *get_element(linked_list_t *list, size_t index)
{

    if (list->len == 0)
    {
        throw_error("empty list");
    }
    if (index > list->len - 1)
    {
        throw_error("No index in list");
    }
    if (index == 0)
    {
        return list->head->value;
    }
    return rec_get_element(list->head->next, index - (size_t) ONE);
}

void *rec_get_element(node_t *actual, size_t index)
{
    if (index == 0)
    {
        return actual->value;
    }
    return rec_get_element((node_t *) actual->next, index - (size_t) ONE);
}
