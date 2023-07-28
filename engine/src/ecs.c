
#include "ecs.h"
#include "stack.h"
#include "util.h"
#include <stdarg.h>

#define INITIAL_CAPACITY 32


static State ecs_state = {0};

void pe_ecs_init(uint32_t component_count, uint32_t bitmask){
	ecs_state.entity_pool = pe_stack_create(sizeof(uint32_t));

	for (int i = INITIAL_CAPACITY; i> 0; i--){
		pe_stack_push(ecs_state.entity_pool, &i);
	}

	ecs_state.entity_store.count = 0;
	ecs_state.entity_store.cap = INITIAL_CAPACITY;
	ecs_state.entity_store.flag_array = calloc(INITIAL_CAPACITY, 1); //1 bit per entity

	ecs_state.entity_store.mask_array = calloc(INITIAL_CAPACITY, sizeof(uint32_t));
	
	ecs_state.component_store.space_components = calloc(INITIAL_CAPACITY, sizeof(SpaceComponent));
	ecs_state.component_store.color_components = calloc(INITIAL_CAPACITY, sizeof(ColorComponent));

	ecs_state.query_results = calloc(2, sizeof(QueryResult));
	
	
}

Entity pe_ecs_create(){ 

	/*Returns an entity object that the user can assign stuff to
	this should:
		pop an ID from the entity_pool,
		increase the entity count
		change entity flag to true
		set entity mask to 0 
		set entity id to id popped from pool

	
	
	
	*/
	Entity entity;
	uint32_t id;
	printf("%d\n", ecs_state.entity_pool->count);
	id = *(uint32_t*)pe_stack_pop(ecs_state.entity_pool);

	ecs_state.entity_store.count++;
	ecs_state.entity_store.flag_array[id] = 1;
	ecs_state.entity_store.mask_array[id] = 0;
	entity.id = id;
	return entity;
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

	for(int i = 0; i < ecs_state.entity_store.cap; i++){
		if (ecs_state.entity_store.mask_array[i] == 0b00){
			ecs_state.query_results[0].list[ecs_state.query_results[0].count++] = i;
		}

		if (ecs_state.entity_store.mask_array[i] == 0b01){
			ecs_state.query_results[1].list[ecs_state.query_results[1].count++] = i;
		}
	}

}