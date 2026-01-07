//
// Created by hectoralv22 on 1/7/26.
//

#include "hash_map.h"

#include "utils.h"


entry_t *create_entry(void *data){
    entry_t *new_entry = malloc(sizeof(entry_t));
    check_mem_alloc(new_entry, "Error creating entry type struct");
    new_entry->prev = NULL;
    new_entry->next = NULL;
    new_entry->data = data;
    new_entry->key = 0;
    return new_entry;
}


mod_ll_t *mod_init_linked_list(void){
    // CREATE SPACE FOR THE STRUCT
    mod_ll_t *ll = malloc(sizeof(mod_ll_t));
    check_mem_alloc(ll, "Linked list mod init");
    // PARAMETERS
    ll->len  = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}



void mod_delete_linked_list(mod_ll_t *list){

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

    entry_t *base = list->tail;

    while (base->prev != NULL)
    {
        entry_t *new_base = base->prev;
        free(base->data);
        free(base);
        base = new_base;
    }

    free(base->data);
    free(base);
    free(list);
}

void mod_push_entry(mod_ll_t *list, void *data){
    entry_t *new_entry = create_entry(data);
    if (list->len == (size_t) ZERO)
    {
        list->head = new_entry;
        list->tail = new_entry;
        list->len++;
        return;
    }
    new_entry->prev   = list->tail;
    list->tail->next = new_entry;
    list->tail       = new_entry;
    list->len++;
}

void mod_pop_head(mod_ll_t *list){
    if (list->len == (size_t) ZERO)
    {
        throw_error("No elements in linked list");
    }
    entry_t *return_entry = list->head;
    if (list->len == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        entry_t *new_head = list->head->next;
        new_head->prev   = NULL;
        list->head       = new_head;
    }
    list->len--;
    free(return_entry->data);
    free(return_entry);
}

void mod_pop_tail(mod_ll_t *list){
    if (list->len == (size_t) ZERO)
    {
        throw_error("No elements in linked list");
    }
    entry_t *return_entry = list->tail;
    if (list->len == (size_t) ONE)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else
    {
        list->tail       = return_entry->prev;
        list->tail->next = NULL;
    }

    list->len--;
    free(return_entry->data);
    free(return_entry);
}

void mod_remove_entry(mod_ll_t *list, size_t index){
/* ================================================================================================
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
 * CAMBIAR LOGICA
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
     */
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
        mod_pop_head(list);
        return;
    }
    if (index == list->len - (size_t) ONE)
    {
        // Same as pop_head, but with the tail
        mod_pop_tail(list);
        return;
    }

    // General case. Navigate till the index of the element
    entry_t *index_entry= list->head;

    for (size_t i = 0; i < index; i++)
    {
        index_entry = index_entry->next;
    }
    index_entry->prev->next = index_entry->next;
    index_entry->next->prev = index_entry->prev;
    free(index_entry->data);
    free(index_entry);
    list->len--;

}



void *mod_get_element(mod_ll_t *list, size_t index){


}

void *rec_mod_get_element(entry_t *actual, size_t index){


}





void load_value_sc(hash_map_sc_t *hash_map){


}

hash_map_sc_t *init_hash_map(void){


}

void delete_hash_map_sc(hash_map_sc_t *hash_map){


}

void add_entry_sc(hash_map_sc_t *hash_map, void *data){


}