// Doubly Linked List

#include<stdio.h>
#include<stdlib.h>

#include "dll.h"


dll_node_t *new_dll_node(object_t *o) {
    dll_node_t *new_node = (dll_node_t *) malloc(sizeof(dll_node_t));
    if(new_node == NULL) return NULL;
    
    new_node->data = o;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void dll_insert_at_tail(dll_node_t **head, object_t *o) {
    if(*head == NULL) {
        dll_node_t *new_node = new_dll_node(o);
        if(new_node == NULL) {
            printf("\n\tError: Failed to allocate memory for new node at 'dll_insert_at_tail'\n");
            exit(-1);
        }

        new_node->prev = new_node->next = NULL;
        *head = new_node;
    } else {
        dll_node_t *last = *head;
        while(last->next != NULL) last = last->next;

        dll_node_t *new_node = new_dll_node(o);
        if(new_node == NULL) {
            printf("\n\tError: Failed to allocate memory for new node at 'dll_insert_at_tail'\n");
            exit(-1);
        }
        last->next = new_node;
        new_node->prev = last;
        new_node->next = NULL;
    }
}

void dll_insert_at_head(dll_node_t **head, object_t *o) {
    dll_node_t *new_node = new_dll_node(o);
    if(new_node == NULL) {
        printf("\n\tError: Failed to allocate memory for new node at 'dll_insert_at_tail'\n");
        exit(-1);
    }

    if(*head == NULL) {
        new_node->prev = new_node->next = NULL;
        *head = new_node;
    } else {
        (*head)->prev = new_node;
        new_node->prev = NULL;
        new_node->next = *head;
        *head = new_node;
    }
}


void dll_print(dll_node_t *head) {
    while(head != NULL) {
        printf(" ");
        print_object(head->data);
        if(head->next != NULL) printf(" <->");
        else printf(" ");
        head = head->next;
    }
}

dll_node_t *dll_node_at(dll_node_t *head, int index) {
    int i = 0;
    while(i <= index && head != NULL) {
        if(i == index) return head;

        head = head->next;
        i++;
    }

    return NULL;
}

int dll_search_node(dll_node_t *head, object_t *o) {
    int index = 0;
    while(head != NULL) {
        if(head->data == o) return index;
        
        index++;
        head = head->next;
    }
    return -1;
}

int dll_length(dll_node_t *head) {
    int l = 0;
    while(head != NULL) {
        l++;
        head = head->next;
    }
    return l;
}


// void dll_insert_at(dll_node_t **head, int index, object_t *o);
// void dll_delete_at(dll_node_t **head, int index);
// dll_node_t *dll_copy(dll_node_t *head);
// dll_node_t *dll_merge(dll_node_t *h1, dll_node_t *h2);
// dll_node_t *dll_reverse(dll_node_t *head);

dll_node_t *dll_remove_at_tail(dll_node_t **head) {
    if(*head == NULL) return NULL;
    dll_node_t *last = *head;
    while(last->next != NULL) {
        last = last->next;
    }
    if(last->prev != NULL) last->prev->next = NULL;
    last->prev = NULL;
    last->next = NULL;
    return last;
}

dll_node_t *dll_remove_at_head(dll_node_t **head) {
    if(*head == NULL) return NULL;
    dll_node_t *first = *head;
    if((*head)->next != NULL) *head = (*head)->next;
    (*head)->prev = NULL;
    first->next = NULL;
    return first;
}

void dll_free_node(dll_node_t *node) {
    if(node == NULL) return;
    free_object(node->data);
    free(node);
}
