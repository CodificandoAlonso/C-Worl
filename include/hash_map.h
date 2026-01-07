//
// Created by hectoralv22 on 1/7/26.
//

#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef C_WORL_HASH_MAP_H
#define C_WORL_HASH_MAP_H

#define HASH_MAP_THRESHOLD 0.75

typedef struct entry_t
{
    u32_t           key;
    void           *data;
    struct entry_t *prev;
    struct entry_t *next;
} entry_t;

/*
 * @brief Struct to implement a linked QUEUE with only allows to pop/push the head/tail. Super basic
 *
 *
 */
typedef struct mod_ll_t
{
    entry_t *head;
    entry_t *tail;
    size_t   len;
} mod_ll_t;


// CASE SEPARATE CHAINING
typedef struct hash_map_sc_t
{
    mod_ll_t **buckets;
    size_t     capacity;
    size_t     size;
    float      load_factor;
} hash_map_sc_t;

// CASE OPEN ADDRESSING
typedef struct hash_map_oa_t
{
    mod_ll_t **buckets;
    size_t     capacity;
    size_t     size;
    float      load_factor;
} hash_map_oa_t;

/* ================================================================================================
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
 * FUNCTIONS FOR AUXILIAR LL.
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
 * ================================================================================================
 */

mod_ll_t *mod_init_linked_list(void);

void mod_delete_linked_list(mod_ll_t *list);

void mod_push_entry(mod_ll_t *list, void *data);

void mod_pop_head(mod_ll_t *list);

void mod_pop_tail(mod_ll_t *list);

void mod_remove_entry(mod_ll_t *list, size_t index);

void *mod_get_element(mod_ll_t *list, size_t index);

void *rec_mod_get_element(entry_t *actual, size_t index);

entry_t *create_entry(void *data);





void load_value_sc(hash_map_sc_t *hash_map);

hash_map_sc_t *init_hash_map(void);

void delete_hash_map_sc(hash_map_sc_t *hash_map);

void add_entry_sc(hash_map_sc_t *hash_map, void *data);

#endif // C_WORL_HASH_MAP_H
