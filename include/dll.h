// Doubly Linked List

#pragma once

#include "object.h"

typedef struct DLLNode dll_node_t;

struct DLLNode {
    dll_node_t *prev;
    object_t *data;
    dll_node_t *next;
};

dll_node_t *new_dll_node(object_t *o);
void dll_insert_at_tail(dll_node_t **head, object_t *o);
void dll_insert_at_head(dll_node_t **head, object_t *o);

void dll_print(dll_node_t *head);
dll_node_t *dll_node_at(dll_node_t *head, int index);
int dll_search_node(dll_node_t *head, object_t *o);
int dll_length(dll_node_t *head);

// void dll_insert_at(dll_node_t **head, int index, object_t *o);
// void dll_delete_at(dll_node_t **head, int index);
// dll_node_t *dll_copy(dll_node_t *head);
// dll_node_t *dll_merge(dll_node_t *h1, dll_node_t *h2);
// dll_node_t *dll_reverse(dll_node_t *head);

dll_node_t *dll_remove_at_tail(dll_node_t **head);
dll_node_t *dll_remove_at_head(dll_node_t **head);
void dll_free_node(dll_node_t *node);