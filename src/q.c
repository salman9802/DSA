// Queue (dynamic)

#include<stdio.h>
#include<stdlib.h>

#include "dll.h"
#include "q.h"

q_t *new_q() {
    q_t *new_q = malloc(sizeof(q_t));
    if(new_q == NULL) return NULL;

    new_q->front = new_q->rear = NULL;
    
    return new_q;
}


size_t q_length(q_t *q) {
    return dll_length(q->front);
}


/* The following enqueue & dequeue implementations were my first and they are correct though the standard for enqueuing is at the rear and dequeuing at the front.

void q_enqueue(q_t *q, object_t *o) {
    if(q == NULL || o == NULL) return;

    dll_insert_at_head(&(q->front), o);
    if(q->front->next == NULL) q->rear = q->front;
}

object_t *q_dequeue(q_t *q) {
    if(q == NULL) return NULL;
    else if(q->rear == NULL) return NULL;
    
    dll_node_t *rear = q->rear;
    q->rear = rear->prev;
    if(q->rear == NULL) q->front = q->rear;
    
    rear->prev = rear->next = NULL;
    return rear->data;
}
*/
void q_enqueue(q_t *q, object_t *o) {
    if(q == NULL || o == NULL) return;

    dll_node_t *node = new_dll_node(o);
    if(q->front == NULL) {
        q->front = q->rear = node;
    } else {
        node->prev = q->rear;
        q->rear->next = node;
        q->rear = node;
    }
}

object_t *q_dequeue(q_t *q) {
    if(q == NULL || q->front == NULL) return NULL;

    dll_node_t *node = q->front;
    if(node == q->rear) q->front = q->rear = NULL;
    else q->front = q->front->next;

    node->prev = node->next = NULL;
    return node->data;
}


void q_free(q_t *q) {
    if(q == NULL) return;
    dll_node_t *curr = q->front, *temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        dll_free_node(temp);
    }

    free(q);
}
