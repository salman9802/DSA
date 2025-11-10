#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "object.h"

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
        default:
            printf("\n\tError: Unknown object kind at 'free_object'\n");
            exit(-1);
    }
}
