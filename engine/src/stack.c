#include "stack.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
ArrayStack *pe_stack_create(size_t size){
    ArrayStack *as = (ArrayStack*)malloc(sizeof(ArrayStack));

    as->size = size;
    as->data = malloc(size);
    as->cap = 1;
    as->count = 0;
    return as;
}

void pe_stack_destroy(ArrayStack *as){
    free(as->data);
    free(as);
}



void *pe_stack_pop(ArrayStack *as){
    uint8_t *ret = (uint8_t*)as->data;
    ret += (--as->count) * as->size;
    return ret;
}


void pe_stack_push(ArrayStack *as, void* data){
    uint8_t *ptr;
    if (as->count == as->cap){
        void *data = realloc(as->data , as->cap * 2 * as->size);
        if (NULL == data){
            pe_printError("Failed to reallocate memory", "stack reallocation error");
            exit(1);
        }
        else{
            as->data = data;
            as->cap *= 2;
        }
    }

    ptr = (uint8_t*)as->data;
    ptr += (as->count++)*as->size;
    memcpy(ptr, data, as->size);
}