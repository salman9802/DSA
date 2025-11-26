// Queue (dynamic)

#pragma once

#include "object.h"
#include "dll.h"

typedef struct Queue {
    dll_node_t *front;
    dll_node_t *rear;
} q_t;

q_t *new_q();

size_t q_length(q_t *q);

void q_enqueue(q_t *q, object_t *o);
object_t *q_dequeue(q_t *q);

void q_free();