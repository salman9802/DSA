// Priority Queue (dynamic)

#pragma once

#include "object.h"
#include "dll.h"

typedef enum PriorityQueuePriority {
    PQ_LOW,
    PQ_HIGH,
    PQ_CRITICAL
} pq_priority_t;

typedef struct PriorityQueueItem {
    object_t *data;
    pq_priority_t priority;
} pq_item_t;

typedef struct PriorityQueue {
    dll_node_t *front;
    dll_node_t *rear;
} pq_t;

pq_t *new_pq();

void pq_print(pq_t *pq);
const char* pq_priority_to_string(pq_priority_t p);

void pq_enqueue(pq_t *pq, object_t *o, pq_priority_t priority);
pq_item_t *pq_dequeue_by_priority(pq_t *pq, pq_priority_t priority);
pq_item_t *pq_dequeue(pq_t *pq);


void pq_free_item(pq_item_t *item);
void pq_free_items(pq_t *pq);
void pq_free(pq_t **pq);