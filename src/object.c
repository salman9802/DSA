#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "object.h"

void print_object(object_t *o) {
    switch(o->kind) {
        case INT: printf("%d", o->value.v_int); break;
        case FLOAT: printf("%f", o->value.v_float); break;
        case STR: printf("%s", o->value.v_str); break;
        case PTR: printf("%p", o->value.v_ptr); break;
        default: printf("%p", o); break;
    }
}

object_t *new_int_object(int value) {
    object_t *o = (object_t *) malloc(sizeof(object_t));
    if(o == NULL) return NULL;

    o->kind = INT;
    o->value.v_int = value;
    return o;
}

object_t *new_float_object(float value) {
    object_t *o = (object_t *) malloc(sizeof(object_t));
    if(o == NULL) return NULL;

    o->kind = FLOAT;
    o->value.v_float = value;
    return o;
}

object_t *new_str_object(char *value) {
    object_t *o = (object_t *) malloc(sizeof(object_t));
    if(o == NULL) return NULL;

    size_t v_len = strlen(value) + 1;    
    o->value.v_str = (char *) malloc(v_len * sizeof(char));
    if(o->value.v_str == NULL) {
        free_object(o);
        return NULL;
    }
    
    o->kind = STR;
    strcpy(o->value.v_str, value);
    return o;
}

object_t *new_ptr_object(void *value) {
    object_t *o = (object_t *) malloc(sizeof(object_t));
    if(o == NULL) return NULL;

    o->kind = PTR;
    o->value.v_ptr = value;
    return o;
}

int object_compare(object_t *o1, object_t *o2) {
    switch(o1->kind) {
        case INT:
            if(o2->kind == INT) return o1->value.v_int - o2->value.v_int;
            else if(o2->kind == FLOAT) return (int) (o1->value.v_int - o2->value.v_float);
            else {
                printf("\nInvalid operation at 'object_compare'\n");
                exit(-1);
            }
        case FLOAT:
            if(o2->kind == INT) return (int) (o1->value.v_float - o2->value.v_int);
            else if(o2->kind == FLOAT) return (int) (o1->value.v_float - o2->value.v_float);
            else {
                printf("\nInvalid operation at 'object_compare'\n");
                exit(-1);
            }
        case STR:
            if(o2->kind == STR) return strcmp(o1->value.v_str, o2->value.v_str);
            else {
                printf("\nInvalid operation at 'object_compare'\n");
                exit(-1);
            }
        case PTR:
            printf("\n\tError: Cannot compare object of kind 'PTR' at 'compare_object'.\n");
            exit(-1);
        default: return 0;
    }
}

bool set_int_object(object_t *o, int value) {
    if(o == NULL) return false;
    o->kind = INT;
    o->value.v_int = value;
    return true;
}

bool set_float_object(object_t *o, float value) {
    if(o == NULL) return false;
    o->kind = FLOAT;
    o->value.v_float = value;
    return true;
}

bool set_str_object(object_t *o, char *value) {
    if(o == NULL) return false;
    
    o->kind = STR;
    size_t v_len = strlen(value) + 1;    
    o->value.v_str = (char *) malloc(v_len * sizeof(char));
    if(o->value.v_str == NULL) {
        free_object(o);
        return false;
    }
    strcpy(o->value.v_str, value);    
    return true;
}

void free_object(object_t *o) {
    switch(o->kind) {
        case INT: free(o); break;
        case FLOAT: free(o); break;
        case STR:
            free(o->value.v_str);
            free(o);
            break;
        case PTR:
            printf("\n\tError: Cannot free object of kind 'PTR' at 'free_object'. Manually free the object value and object.\n");
            exit(-1);
        default:
            free(o);
            // printf("\n\tError: Unknown object kind at 'free_object'\n");
            // exit(-1);
    }
}

object_t *object_copy(object_t *o) {
    object_t *new_object = (object_t *) malloc(sizeof(object_t));
    switch(o->kind) {
        case INT:
            new_object->kind = INT;
            new_object->value.v_int = o->value.v_int;
            return new_object;
        case FLOAT:
            new_object->kind = FLOAT;
            new_object->value.v_float = o->value.v_float;
            return new_object;
        case STR:
            size_t v_len = strlen(o->value.v_str) + 1;
            new_object->value.v_str = (char *) malloc(v_len * sizeof(char));
            if(new_object->value.v_str == NULL) {
                free_object(new_object);
                return NULL;
            }
            
            new_object->kind = STR;
            strcpy(new_object->value.v_str, o->value.v_str);
            return new_object;
        case PTR:
            printf("\n\tError: Cannot copy object of kind 'PTR' at 'object_copy'.\n");
            exit(-1);
        default:
            printf("\nInvalid operation at 'object_copy'\n");
            exit(-1);
    }
}

void *object_value(object_t *o) {
    if(o == NULL) return NULL;

    switch(o->kind) {
        case INT: return &(o->value.v_int);
        case FLOAT: return &(o->value.v_float);
        case STR: return o->value.v_str;
        case PTR: return o->value.v_ptr;
        default:
            printf("\n\tError: Unknown object kind at 'object_value'.\n");
            exit(-1);
    }
}
