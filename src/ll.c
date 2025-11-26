#include<stdio.h>

#include "ll.h"

/* Creates a new node with next as NULL and data as the specified object */
ll_node_t *new_ll_node(object_t *o) {
    ll_node_t *new_node = (ll_node_t *) malloc(sizeof(ll_node_t));
    if(new_node == NULL) return NULL;
    
    new_node->data = o;
    new_node->next = NULL;
    return new_node;
}

/* Frees linked list node */
void ll_free_node(ll_node_t *node) {
    if(node == NULL) return;

    free_object(node->data);
    free(node);
}


/* Inserts a new node at the end of the linked list */
void ll_insert(ll_node_t **head, object_t *o) {
    if(*head == NULL) {
        ll_node_t *new_node = new_ll_node(o);
        if(new_node == NULL) {
            printf("\n\tError: Failed to allocate memory for new node\n");
            exit(-1);
        }
        
        new_node->next = NULL;
        *head = new_node;
    } else {
        ll_node_t *last_node = *head;
        while(last_node->next != NULL) last_node = last_node->next;

        ll_node_t *new_node = new_ll_node(o);
        if(new_node == NULL) {
            printf("\n\tError: Failed to allocate memory for new node\n");
            exit(-1);
        }

        new_node->next = NULL;
        last_node->next = new_node;
    }
}

/* Pretty prints the linked list to stdout */
void ll_print(ll_node_t *head) {
    while(head != NULL) {
        printf(" ");
        print_object(head->data);
        if(head->next != NULL) printf(" ->");
        else printf(" ");
        head = head->next;
    }
}

ll_node_t *ll_node_at(ll_node_t *head, int index) {
    int i = 0;
    while(i <= index && head != NULL) {
        if(i == index) return head;
        
        head = head->next;
        i++;
    }

    return NULL;
}

void ll_insert_at(ll_node_t **head, int index, object_t *o) {
    if(*head == NULL) {
        ll_node_t *new_node = new_ll_node(o);
        if(new_node == NULL) {
            printf("\n\tError: Failed to allocate memory for new node\n");
            exit(-1);
        }
        
        new_node->next = NULL;
        *head = new_node;
        return;
    }
    if(index < 0) return;
    
    ll_node_t *prev = NULL, *next = NULL;

    prev = *head;
    next = (*head)->next;
    int i = 0;
    while(i <= index - 1 && next != NULL) {
        if(i == index - 1) {
            ll_node_t *new_node = new_ll_node(o);
            if(new_node == NULL) {
                printf("\n\tError: Failed to allocate memory for new node\n");
                exit(-1);
            }
            
            prev->next = new_node;
            new_node->next = next;
            return;
        }
        
        i++;
        prev = next;
        next = next->next;
    }

    ll_node_t *new_node = new_ll_node(o);
    if(new_node == NULL) {
        printf("\n\tError: Failed to allocate memory for new node\n");
        exit(-1);
    }

    if(index == 0) {
        new_node->next = prev;
        *head = new_node;
    } else {
        prev->next = new_node;
        new_node->next = next;
    }
}

void ll_delete_at(ll_node_t **head, int index) {
    if(*head == NULL) return;

    ll_node_t *prev = NULL, *curr = NULL;
    // prev = *head;
    curr = *head;
    int i = 0;
    // ll_node_t *curr = *head;
    while(i <= index && curr != NULL) {
        if(i == index) {
            if(prev == NULL)
                *head = curr->next;
            else
                prev->next = curr->next;
            
            ll_free_node(curr);

            return;
        }
        i++;
        prev = curr;
        curr = curr->next;
    }
    // return;
}

int ll_length(ll_node_t *head) {
    int c = 0;
    while(head != NULL) {
        c++;
        head = head->next;
    }
    return c;
}

ll_node_t *ll_copy(ll_node_t *head) {
    // int ll_len = ll_length(head);

    ll_node_t *new_head = NULL;
    ll_node_t *curr = NULL, *new_node = NULL;
    int i = 0;
    while(head != NULL) {
        new_node = new_ll_node(head->data);

        if(i == 0) new_head = curr = new_node;
        else{
            curr->next = new_node;
            curr = new_node;
        }

        i++;
        head = head->next;
    }

    return new_head;
}

ll_node_t *ll_merge(ll_node_t *h1, ll_node_t *h2) {
    if(h1 == NULL) return ll_copy(h2);
    if(h2 == NULL) return ll_copy(h1);
    
    ll_node_t *h1_copy = ll_copy(h1);
    ll_node_t *h2_copy = ll_copy(h2);

    ll_node_t *curr= h1_copy;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = h2_copy;

    return h1_copy;
}

int ll_search_node(ll_node_t *head, object_t *o) {
    int index = 0;
    while(head != NULL) {
        if(head->data == o) {
            return index;
        }

        index++;
        head = head->next;
    }
    return -1;
}

ll_node_t *ll_reverse(ll_node_t *head) {
    if(head == NULL) return NULL;
    
    ll_node_t *prev = NULL, *curr = NULL, *next = NULL;
    prev = NULL;
    curr = head;
    next = curr->next;

    while(curr != NULL) {
        curr->next = prev;
        prev = curr;
        curr = next;
        if(next != NULL) next = next->next;
    }
    
    return prev;
}

ll_node_t *ll_remove_tail(ll_node_t **head) {
    if(*head == NULL) return NULL;
    ll_node_t *tail = *head, *new_tail = *head;
    while(tail->next != NULL) {
        new_tail = tail;
        tail = tail->next;
    }
    new_tail->next = NULL;

    if(tail == *head)
        *head = NULL;

    return tail;
}

ll_node_t *ll_remove_head(ll_node_t **head) {
    if(*head == NULL) return NULL;
    ll_node_t *node = NULL;
    node = *head;
    *head = (*head)->next;
    return node;
}
