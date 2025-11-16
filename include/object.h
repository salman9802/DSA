#pragma once

#include<stdbool.h>

typedef enum ObjectKind {
    INT,
    FLOAT,
    STR,
    PTR
} object_kind_t;

typedef union ObjectValue {
    int v_int;
    float v_float;
    char *v_str;
    void *v_ptr;
} object_value_t;

typedef struct Object {
    object_kind_t kind;
    object_value_t value;
} object_t;

void print_object(object_t *o);

object_t *new_int_object(int value);
object_t *new_float_object(float value);
object_t *new_str_object(char *value);
object_t *new_ptr_object(void *value);

int object_compare(object_t *o1, object_t *o2);
object_t *object_copy(object_t *o);
void *object_value(object_t *o);

bool set_int_object(object_t *o, int value);
bool set_float_object(object_t *o, float value);
bool set_str_object(object_t *o, char *value);

void free_object(object_t *o);