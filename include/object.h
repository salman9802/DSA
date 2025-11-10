#include<stdbool.h>

typedef enum ObjectKind {
    INT,
    FLOAT,
    STR
} object_kind_t;

typedef union ObjectValue {
    int v_int;
    float v_float;
    char *v_str;
} object_value_t;

typedef struct Object {
    object_kind_t kind;
    object_value_t value;
} object_t;


object_t *new_int_object(int value);
object_t *new_float_object(float value);
object_t *new_str_object(char *value);
int object_compare(object_t *o1, object_t *o2);
bool set_int_object(object_t *o, int value);
bool set_float_object(object_t *o, float value);
bool set_str_object(object_t *o, char *value);
void free_object(object_t *o);