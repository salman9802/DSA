// Stack (dynamic)

#pragma once

#include<stdlib.h>
#include<stdbool.h>

#include "object.h"
#include "ll.h"

typedef struct Stack {
    ll_node_t *top;
} st_t;


st_t *new_st();
void st_free(st_t *st);

void st_push(st_t *st, object_t *item);
object_t *st_pop(st_t *st);
object_t *st_peek(st_t *st);
bool st_is_empty(st_t *st);
st_t *st_reverse(st_t *st);