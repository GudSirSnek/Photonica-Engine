
#include "ecs.h"
#include "stack.h"
#include "util.h"
#include <stdarg.h>


#define INITIAL_CAPACITY 32-1


static State ecs_state = {0};

void pe_ecs_init(uint32_t component_count, ...){
	ecs_state.entity_pool = pe_stack_create(sizeof(uint32_t));

	for (int i = INITIAL_CAPACITY; i>= 0; i--){
		pe_stack_push(ecs_state.entity_pool, &i);
	}
	
	ecs_state.component_store.Component_count = component_count;
	ecs_state.entity_store.count = 0;
	ecs_state.entity_store.cap = INITIAL_CAPACITY;
	ecs_state.entity_store.flag_array = calloc(INITIAL_CAPACITY, 1); //1 bit per entity

	ecs_state.entity_store.mask_array = calloc(INITIAL_CAPACITY, sizeof(uint32_t));
	ecs_state.component_store.sizes = calloc(component_count, sizeof(size_t));
	ecs_state.component_store.Components = calloc(component_count, sizeof(void*));

	va_list ptr;

	va_start(ptr, component_count);
	size_t t;
	for(uint32_t i = 0; i < component_count; i++){
		t = va_arg(ptr, size_t);
		ecs_state.component_store.Components[i] = calloc(INITIAL_CAPACITY, t);
		ecs_state.component_store.sizes[i] = t;
	}
	va_end(ptr);

	ecs_state.query_results = calloc(2, sizeof(QueryResult));
	
	
}

Entity pe_ecs_create(){ 

	/*Returns an entity object that the user can assign stuff to
	this should:
		- if pool count is greater than 0
		pop an ID from the entity_pool,
		increase the entity count
		change entity flag to true
		set entity mask to 0 
		set entity id to id popped from pool
		- if pool count is 0
		reallocate the ECS system
		repeat for above

	
	
	
	*/
	Entity entity;
	uint32_t id;

	if (ecs_state.entity_store.count == ecs_state.entity_store.cap){
			//reallocate stuff
			ecs_state.component_store.Component_count *= 2;
			ecs_state.entity_store.cap *= 2;
			uint8_t *new_flag_array = realloc(ecs_state.entity_store.flag_array, ecs_state.entity_store.cap);
			if (new_flag_array == NULL){
				pe_printError("Cannot reallocate entity flag array", NULL);
			}
			for(uint32_t i = ecs_state.entity_store.cap/2 + 1; i < ecs_state.entity_store.cap; i++){
				new_flag_array[i] = 0;
			}
			uint32_t *new_mask_array = realloc(ecs_state.entity_store.mask_array, ecs_state.entity_store.cap*sizeof(uint32_t));
			if (new_mask_array == NULL){
				pe_printError("Cannot reallocate entity mask array", NULL);
			}
			for(uint32_t i = 0; i < ecs_state.component_store.Component_count; i++){
				void *new_realloc = realloc(ecs_state.component_store.Components[i], ecs_state.entity_store.cap*ecs_state.component_store.sizes[i]);
				if (new_realloc == NULL){
					pe_printError("Cannot reallocate component array, ID: ", i);
				}
				ecs_state.component_store.Components[i] = new_realloc;

			}

			ecs_state.entity_store.flag_array = new_flag_array;
			ecs_state.entity_store.mask_array = new_mask_array;
		}

	if (ecs_state.entity_pool->count > 0){
		id = *(uint32_t*)pe_stack_pop(ecs_state.entity_pool);
		ecs_state.entity_store.count++;
		printf("entity id: %d\n", id);	
	}
	else{
		id = ecs_state.entity_store.count++;
		printf("entity count: %d, cap: %d\n", ecs_state.entity_store.count, ecs_state.entity_store.cap);
		
	}
	
	
	
	ecs_state.entity_store.flag_array[id] = 1;
	ecs_state.entity_store.mask_array[id] = 0;
	entity.id = id;
	return entity;
}

void * pe_ecs_GetComponent(uint32_t entity_id, uint8_t component_id){

	return ((void*)ecs_state.component_store.Components[component_id] + entity_id*ecs_state.component_store.sizes[component_id]);

}

void pe_ecs_AddComponent(uint32_t entity_id, uint8_t component_id, void * data){

	void *ptr = pe_ecs_GetComponent(entity_id, component_id);

	size_t s = ecs_state.component_store.sizes[component_id];

	memcpy(ptr, data,s);


	
}

uint8_t pe_ecs_getFlag(uint32_t entity_id){
	return ecs_state.entity_store.flag_array[entity_id];
}

void pe_ecs_AddSpaceComp(uint32_t entity_id, SpaceComponent *space){
	ecs_state.component_store.space_components[entity_id] = *space;
}

SpaceComponent *pe_ecs_GetSpaceComp(uint32_t entity_id){
	return &ecs_state.component_store.space_components[entity_id];
}

void pe_ecs_AddColorComp(uint32_t entity_id, ColorComponent *color){
	ecs_state.component_store.color_components[entity_id] = *color;
}


ColorComponent * pe_ecs_GetColorComp(uint32_t entity_id){
	return &ecs_state.component_store.color_components[entity_id];
}


void pe_ecs_kill(Entity entity){
	pe_stack_push(ecs_state.entity_pool, &entity.id);
	ecs_state.entity_store.flag_array[entity.id] = 0;
	ecs_state.entity_store.count--;
	entity.id = 0;
}




void pe_ecs_getQuery(){
	ecs_state.query_results[0].count = 0;
	ecs_state.query_results[1].count = 0;

	for(uint32_t i = 0; i < ecs_state.entity_store.cap; i++){
		if (ecs_state.entity_store.mask_array[i] == 0b00){
			ecs_state.query_results[0].list[ecs_state.query_results[0].count++] = i;
		}

		if (ecs_state.entity_store.mask_array[i] == 0b01){
			ecs_state.query_results[1].list[ecs_state.query_results[1].count++] = i;
		}
	}

}