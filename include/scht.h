// Separate Chaining Hash Table

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#include "object.h"
#include "ll.h"

// extern const uint64_t SCHT_FNV_OFFSET_BASIS_64;
// extern const uint64_t SCHT_FNV_PRIME;

#define SCHT_FNV_OFFSET_BASIS_64 14695981039346656037ULL
#define SCHT_FNV_PRIME64         1099511628211ULL

// hash function
uint64_t fnv_1a(const unsigned char *key);


typedef struct SeparateChainingHashTableEntry {
    char *key;
    object_t *value;
    uint64_t hash;
} scht_entry_t;

typedef struct SeparateChainingHashTable {
    size_t capacity;
    ll_node_t **buckets; // length = capacity
    size_t element_count;
    float max_load_factor; // usually 0.75
} scht_t;

scht_t *new_scht(int n);

object_t *scht_get(scht_t *scht, const char *key);
// const char **scht_keys();
const char * const *scht_keys();
object_t **scht_values();

void scht_set(scht_t *scht, const char *key, object_t *value);
object_t *scht_remove(scht_t *scht, const char *key);

void scht_free(scht_t *scht);
void scht_free_entry(scht_entry_t *scht_entry);
