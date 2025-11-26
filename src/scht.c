// Separate Chaining Hash Table

// #include<math.h>

#include "scht.h"

// extern const unsigned long SCHT_FNV_OFFSET_BASIS = 14695981039346656037;
// extern const unsigned long SCHT_FNV_PRIME = 1099511628211;

// extern const uint64_t SCHT_FNV_OFFSET_BASIS = 14695981039346656037;
// extern const uint64_t SCHT_FNV_PRIME = 1099511628211;
// extern const uint64_t SCHT_FNV_OFFSET_BASIS_64 = 14695981039346656037ULL;
// extern const uint64_t SCHT_FNV_PRIME = 1099511628211ULL;


uint64_t fnv_1a(const unsigned char *key) {
    uint64_t h = SCHT_FNV_OFFSET_BASIS_64;
    const unsigned char *b = key;

    // printf("\nUsing prime INSIDE = %llu\n", (unsigned long long)SCHT_FNV_PRIME64);


    while((*b) != '\0') {
        h = h ^ (*b);
        h = h * SCHT_FNV_PRIME64;
        b++;
    }
    return h;
    
    // for(int i = 0; i < strlen(key); i++) {
    //     h = h ^ key[i];
    //     h = h * SCHT_FNV_PRIME;
    // }
    // return h;
}


scht_t *new_scht(int n) {
    scht_t *new_scht = malloc(sizeof(scht_t));
    if(new_scht == NULL) return NULL;

    // size_t capacity = pow(2.0, n);
    size_t capacity = (size_t) 1 << n;
    new_scht->buckets = calloc(capacity, sizeof(ll_node_t *));
    if(new_scht->buckets == NULL) return NULL; // TODO: free already allocated buckets

    /* for(int i = 0; i < n; i++) {
        printf("\n ==================== Bucket: %d ==================== \n", i);
        if(new_scht->buckets[i] == NULL) printf("NULL");
        else ll_print(new_scht->buckets[i]);
        printf("\n ==================================================== \n");
    } */
    
    new_scht->capacity = capacity;
    new_scht->element_count = 0;
    new_scht->max_load_factor = 0.75;

    return new_scht;
}

object_t *scht_get(scht_t *scht, const char *key) {
    if(scht == NULL || key == NULL) return NULL;

    uint64_t computed_hash = fnv_1a((const unsigned char *)key);
    int bucket_index = computed_hash & (scht->capacity - 1); // mask instead of modulo
    ll_node_t *ll = scht->buckets[bucket_index];

    scht_entry_t *entry;
    while(ll != NULL) {
        entry = ll->data->value.v_ptr;
        if(entry->hash == computed_hash) {
            if(strcmp(entry->key, key) == 0) {
                return entry->value;
            }
        }
        
        ll = ll->next;
    }

    return NULL;
}


void scht_set(scht_t *scht, const char *key, object_t *value) {
    if(scht == NULL || key == NULL) return;

    uint64_t computed_hash = fnv_1a((const unsigned char *)key);
    int bucket_index = computed_hash & (scht->capacity - 1); // mask instead of modulo
    ll_node_t *ll = scht->buckets[bucket_index];
    ll_node_t *prev = ll;
    while(ll != NULL) {
        scht_entry_t *entry = ll->data->value.v_ptr;
        if(entry->hash == computed_hash) {
            if(strcmp(entry->key, key) == 0) { // if present, update
                entry->value = value;
                return;
            }
        }
        prev = ll;
        ll = ll->next;
    }
    
    scht_entry_t *scht_entry = calloc(1, sizeof(scht_entry_t));
    if(scht_entry == NULL) return;
    
    scht_entry->hash = computed_hash;
    scht_entry->key = calloc(strlen(key) + 1, sizeof(char));
    if(scht_entry->key == NULL) return;
    
    strcpy(scht_entry->key, key);
    scht_entry->value = value;
    
    object_t *node_object = new_ptr_object(scht_entry);
    if(node_object == NULL) return;
    
    ll_node_t *new_node = new_ll_node(node_object);
    if(new_node == NULL) return;
    
    if(prev == NULL) {
        scht->buckets[bucket_index] = new_node;
    } else {
        prev->next = new_node;
    }

    new_node->next = NULL;

    scht->element_count++;
}

object_t *scht_remove(scht_t *scht, const char *key) {
    if(scht == NULL || key == NULL) return NULL;

    uint64_t computed_hash = fnv_1a((const unsigned char *)key);
    int bucket_index = computed_hash & (scht->capacity - 1); // mask instead of modulo
    ll_node_t *ll = scht->buckets[bucket_index];
    ll_node_t *prev = ll;

    scht_entry_t *entry;
    while(ll != NULL) {
        if(ll->data == NULL) break;

        entry = ll->data->value.v_ptr;
        if(entry->hash == computed_hash) {
            if(strcmp(entry->key, key) == 0) {
                prev->next = ll->next;
                ll->next = NULL;

                /* if(ll == scht->buckets[bucket_index]) {
                    // ll->data = NULL;
                    // ll->next = NULL;
                    free(ll->data);
                    // free(ll);
                    // ll = NULL;
                } else {
                    free(ll->data);
                    free(ll);
                } */

                free(ll->data);
                ll->data = NULL;
                if(ll != scht->buckets[bucket_index]) free(ll);
                
                
                // printf("\n [DEBUGGER]\n");
                
                object_t *value = entry->value;
                scht_free_entry(entry);

                scht->element_count--;

                return value;
            }
        }
        prev = ll;
        ll = ll->next;
    }

    return NULL;
}

void scht_free(scht_t *scht);

void scht_free_entry(scht_entry_t *scht_entry) {
    if(scht_entry == NULL) return;

    free(scht_entry->key);
    free(scht_entry);
}
