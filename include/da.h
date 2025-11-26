// Dynamic Array

#pragma once

#include<stdlib.h>

#include "object.h"

extern const float DA_CAPACITY_GROWTH_FACTOR;
extern const float DA_CAPACITY_SHRINK_THRESHOLD;
extern const float DA_CAPACITY_SHRINK_FACTOR;

typedef struct DynamicArray {
    size_t size; /* No. of elements currently stored */
    size_t capacity; /* Current total size allocated */
    object_t **elements; /* Pointer/Reference to allocated memory */
} da_t;

da_t *new_da(size_t capacity);
void da_free(da_t *da);
void da_resize(da_t *da, size_t capacity);

// void da_add(da_t *da, size_t index, object_t *o);
void da_print(da_t *da);
void da_add(da_t *da, object_t *o);
object_t *da_remove_at(da_t *da, size_t index);
object_t *da_access(da_t *da, size_t index);
void da_update(da_t *da, size_t index, object_t *o);
void da_insert_at(da_t *da, size_t index, object_t *o);
// void da_remove_at(da_t *da, size_t index);
int da_search(da_t *da, object_t *o);