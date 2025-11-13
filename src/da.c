// Dynamic Array

#include<stdio.h>

#include "object.h"
#include "da.h"

const float DA_CAPACITY_GROWTH_FACTOR = 1.5f;
const float DA_CAPACITY_SHRINK_THRESHOLD = 0.25f;
const float DA_CAPACITY_SHRINK_FACTOR = 0.5f;

da_t *new_da(size_t capacity) {
    da_t *new_da = (da_t *) malloc(sizeof(da_t));
    if(new_da == NULL) return NULL;

    new_da->size = 0;
    new_da->capacity = capacity;
    new_da->elements = malloc(capacity * sizeof(object_t *));
    if(new_da->elements == NULL) {
        free(new_da);
        return NULL;
    }

    for(size_t i = 0; i < capacity; i++) {
        new_da->elements[i] = (object_t *) malloc(sizeof(object_t));
        if(new_da->elements[i] == NULL) {
            printf("\n\tError: Failed to allocate memory for dynamic array element at index '%zu'\n", i);
            printf("\n\tFreeing memory allocated before index '%zu'\n", i);
            for(size_t j = 0; j < i; j++) {
                free(new_da->elements[j]);
            }
            free(new_da);
            return NULL;
        }
    }

    return new_da;
}

void da_free(da_t *da) {
    if(da == NULL) return;

    for(size_t i = 0; i < da->capacity; i++) {
        free_object(da->elements[i]);
    }
    free(da->elements);
    free(da);
}

/* Resizes (grows, shrinks) the dynamic array to given capacity, while allocating/deallocating memory when necessary. */
void da_resize(da_t *da, size_t new_capacity) {
    if(da == NULL || new_capacity == da->capacity) return;

    object_t **new_elements = realloc(da->elements, new_capacity * sizeof(object_t *));
    if(new_elements == NULL) {
        printf("\n\tError: Failed to re-allocate new memory when resizing dynamic array. Keeping original array.\n");
        return;
    } else {
        if(new_capacity > da->capacity) {
            for(size_t i = da->capacity; i < new_capacity; i++) {
                new_elements[i] = (object_t *) malloc(sizeof(object_t));
                if(new_elements[i] == NULL) {
                    printf("\n\tError: Failed to allocate memory for dynamic array element at index '%zu' in 'da_resize'\n", i);
                    printf("\n\tFreeing memory allocated before index '%zu'\n", i);
                    for(size_t j = 0; j < i; j++) {
                        free(new_elements[j]);
                    }
                    printf("\n\tKeeping original capacity %zu\n", da->capacity);
                    free(new_elements);
                    return;
                }
            }
        }
        da->elements = new_elements;
    }

    da->capacity = new_capacity;
}


/* Pretty prints the dynamic array to stdout */
void da_print(da_t *da) {
    if(da == NULL) return;
    printf(" [");
    for(size_t i = 0; i < da->capacity; i++) {
        printf(" ");
        print_object(da->elements[i]);
        printf(" ");
    }
    printf("] ");
}

/* Adds object to array, dynamically resizing when necessary. */
void da_add(da_t *da, object_t *o) {
    if(da->size < da->capacity)
        da->elements[da->size] = o;
    else {
        da_resize(da, da->capacity * DA_CAPACITY_GROWTH_FACTOR);
        da->elements[da->size] = o;
    }
    da->size++;
}

object_t *da_remove_at(da_t *da, size_t index) {
    if(da == NULL || da->size == 0 || index > da->capacity) {
        printf("\n\tInvalid operation at 'da_remove'\n");
        exit(-1);
    }

    object_t *o = da->elements[index];
    // da->elements[index] = NULL;
    for(size_t i = index + 1; i < da->capacity; i++) {
        da->elements[i - 1] = da->elements[i];
    }
    da->size--;

    if(da->size < da->capacity * DA_CAPACITY_SHRINK_THRESHOLD) {
        da_resize(da, da->capacity * DA_CAPACITY_SHRINK_FACTOR);
    }
    
    return o;
}

object_t *da_access(da_t *da, size_t index) {
    if(da == NULL || da->size == 0 || index > da->capacity) {
        printf("\n\tInvalid operation at 'da_access'\n");
        exit(-1);
    }

    return da->elements[index];
}

void da_update(da_t *da, size_t index, object_t *o) {
    if(da == NULL || da->size == 0 || index > da->capacity) {
        printf("\n\tInvalid operation at 'da_update'\n");
        exit(-1);
    }

    free_object(da->elements[index]);
    da->elements[index] = o;
}

void da_insert_at(da_t *da, size_t index, object_t *o) {
    object_t *prev = da->elements[index], *temp = NULL;
    if(da->size < da->capacity) {
        for(size_t i = index + 1; i < da->size + 1; i++) {
            temp = da->elements[i];
            da->elements[i] = prev;
            prev = temp;
        }
        da->elements[index] = o;
    } else {
        da_resize(da, da->capacity * DA_CAPACITY_GROWTH_FACTOR);
        for(size_t i = index + 1; i < da->size + 1; i++) {
            temp = da->elements[i];
            da->elements[i] = prev;
            prev = temp;
        }
        da->elements[index] = o;
    }
    da->size++;
}

int da_search(da_t *da, object_t *o) {
    // size_t index = 0;
    for(size_t i = 0; i < da->size; i++) {
        if(da->elements[i] == o)
            return i;
    }
    return -1;
}
