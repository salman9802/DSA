// Priority Queue (dynamic)

#include<stdio.h>
#include<stdlib.h>

#include "pq.h"

pq_t *new_pq() {
    pq_t *pq = malloc(sizeof(pq_t));
    if(pq == NULL) return NULL;

    pq->front = pq->rear = NULL;
    return pq;
}


void pq_print(pq_t *pq) {
    if(pq == NULL) return;

    dll_node_t *front = pq->front;
    pq_item_t *item;

    // item = ((pq_item_t *)pq->front->data->value.v_ptr);
    // printf("  Front: (%p, %s)\n", &(item->data), pq_priority_to_string(item->priority));
    // item = ((pq_item_t *)pq->rear->data->value.v_ptr);
    // printf("  Rear: (%p, %s)\n", &(item->data), pq_priority_to_string(item->priority));

    // printf(" ||\n");
    while(front != NULL) {
        // dll_print(rear);
        if(front == pq->front) printf("Front   |");
        else if(front == pq->rear) printf("Rear    |");
        else printf("\t|");

        item = ((pq_item_t *)front->data->value.v_ptr);
        // printf("(%p, %d)", &(item->data), item->priority);
        printf(" (%p, %s) ", &(item->data), pq_priority_to_string(item->priority));
        
        // if(front->next != NULL)
        printf(" |\n");
        front = front->next;
    }
    // printf(" ||\n");


}

const char* pq_priority_to_string(pq_priority_t p) {
    switch (p) {
        case PQ_CRITICAL: return "PQ_CRITICAL";
        case PQ_LOW:      return "PQ_LOW";
        case PQ_HIGH:     return "PQ_HIGH";
        default:          return "UNKNOWN_PRIORITY";
    }
}


void pq_enqueue(pq_t *pq, object_t *o, pq_priority_t priority) {
    if(pq == NULL || o == NULL) return;


    // create pq item
    pq_item_t *item = malloc(sizeof(pq_item_t));
    if(item == NULL) return;
    item->data = o;
    item->priority = priority;

    // add pq item to object
    object_t *node_object = new_ptr_object(item);
    if(node_object == NULL) return;
    
    // create node
    dll_node_t *new_node = new_dll_node(node_object);
    if(new_node == NULL) return;

    if(pq->front == NULL) {
        pq->front = pq->rear = new_node;
    } else {
        dll_node_t *curr = pq->rear;

        while(curr != NULL &&  priority > ((pq_item_t *)curr->data->value.v_ptr)->priority) {
            curr = curr->prev;
        }
        
        if(curr == NULL) {
            pq->front->prev = new_node;
            new_node->next = pq->front;
            pq->front = new_node;
        } else {
            dll_node_t *next = curr->next;
            curr->next = new_node;
            new_node->prev = curr;
            new_node->next = next;
            if(next != NULL) next->prev = new_node;
            // pq->rear = next;
            else pq->rear = new_node;
            // else pq->rear = curr;
        }
        
        // new_node->prev = pq->rear;
        // pq->rear->next = new_node;
        // pq->rear = new_node;
        // new_node->next = NULL;
    }
}

pq_item_t *pq_dequeue_by_priority(pq_t *pq, pq_priority_t priority) {
    if(pq == NULL || pq->front == NULL) return NULL;

    dll_node_t *node = pq->front;

    if(node == pq->rear) pq->front = pq->rear = NULL;
    // else {
        while(node->next != NULL && priority != ((pq_item_t *)node->data->value.v_ptr)->priority) node = node->next;
    // }
    
    if(((pq_item_t *)node->data->value.v_ptr)->priority == priority) {
        if(node->prev != NULL) node->prev->next = node->next;
        if(node->next != NULL) node->next->prev = node->prev;

        if(node == pq->front) pq->front = pq->front->next;
        else if(node == pq->rear) pq->rear = pq->rear->prev;
        
        node->prev = node->next = NULL;
        return ((pq_item_t *)node->data->value.v_ptr);
    } else return NULL;
}

pq_item_t *pq_dequeue(pq_t *pq) {
    if(pq == NULL || pq->front == NULL) return NULL;

    dll_node_t *node = pq->front;

    if(node == pq->rear) pq->front = pq->rear = NULL;
    else pq->front = pq->front->next;

    node->prev = node->next = NULL;
    return ((pq_item_t *)node->data->value.v_ptr);
}


void pq_free_item(pq_item_t *item) {
    if(item == NULL) return;
    free_object(item->data);
    free(item);
}

void pq_free_items(pq_t *pq) {
    if(pq == NULL) return;
    dll_node_t *next;
    while(pq->front != NULL) {
        pq_free_item(pq->front->data->value.v_ptr);
        next = pq->front->next;
        dll_free_node(pq->front);
        pq->front = next;
    }
    pq->front = pq->rear = NULL;
}

void pq_free(pq_t *pq) {
    if(pq == NULL) return;
    pq_free_items(pq);
    free(pq);
}
