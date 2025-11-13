#pragma once

#include<stdlib.h>

#include "object.h"

typedef struct LLNode ll_node_t;

struct LLNode {
    object_t *data;
    ll_node_t *next;
};

ll_node_t *new_ll_node(object_t *o);
void ll_free_node(ll_node_t *node);

void ll_insert(ll_node_t **head, object_t *o);
void ll_print(ll_node_t *head);
ll_node_t *ll_node_at(ll_node_t *head, int index);
void ll_insert_at(ll_node_t **head, int index, object_t *o);
void ll_delete_at(ll_node_t **head, int index);
int ll_length(ll_node_t *head);
ll_node_t *ll_copy(ll_node_t *head);
ll_node_t *ll_merge(ll_node_t *h1, ll_node_t *h2);
int ll_search_node(ll_node_t *head, object_t *o);
ll_node_t *ll_reverse(ll_node_t *head);
ll_node_t *ll_remove_tail(ll_node_t **head);
ll_node_t *ll_remove_head(ll_node_t **head);