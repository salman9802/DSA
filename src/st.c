// Stack (dynamic)

#include<stdio.h>

#include "st.h"
#include "ll.h"


st_t *new_st() {
    st_t *stack = malloc(sizeof(st_t));
    stack->top = NULL;
    return stack;
}

void st_free(st_t *st) {
    if(st == NULL) return;
    ll_node_t *curr = st->top, *temp = NULL;
    while(curr != NULL) {
        temp = curr;
        curr = curr->next;
        ll_free_node(temp);
    }
}


void st_push(st_t *st, object_t *item) {
    if(st == NULL || item == NULL) return;
    ll_insert_at(&(st->top), 0, item);
}

object_t *st_pop(st_t *st) {
    if(st == NULL) return NULL;
    ll_node_t *item = ll_remove_head(&(st->top));
    if(item == NULL) return NULL;
    return item->data;
}

object_t *st_peek(st_t *st) {
    if(st == NULL) return NULL;
    return ll_node_at(st->top, 0)->data;
}

bool st_is_empty(st_t *st) {
    if(st->top == NULL) return true;
    else return false;
}

st_t *st_reverse(st_t *st) {
    if(st == NULL) return NULL;

    st_t *reverse_st = new_st();
    while(!st_is_empty(st)) {
        st_push(reverse_st, st_pop(st));
    }
    return reverse_st;
}
