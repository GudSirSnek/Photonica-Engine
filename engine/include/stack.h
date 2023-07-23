#pragma once

#include <stdint.h>
/* a stack data structure
*/


typedef struct {
	size_t size;
	uint32_t count;
	uint32_t cap;
	void* data;
} ArrayStack;


ArrayStack *pe_stack_create(size_t size); //creates a stack of a certain size in bytes

void pe_stack_destroy(ArrayStack *as); //destroys stack

void *pe_stack_pop(ArrayStack *as); //pop the stack

void pe_stack_push(ArrayStack *as, void* data); //push data to stack

