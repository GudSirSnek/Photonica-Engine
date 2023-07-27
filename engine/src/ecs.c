
#include "ecs.h"
#include "stack.h"
#include "util.h"
#include <stdarg.h>

#define INITIAL_CAPACITY 32

typedef struct {
	uint32_t type_count;
	uint32_t cap;
	size_t size;
	size_t *data_size_array;
	size_t *data_offset_array;
	void *data;
} ComponentStore;

typedef struct {
	uint32_t *mask_array;
	uint32_t *flag_array;
	uint32_t count;
	uint32_t cap;
} EntityStore;


typedef struct {
	ComponentStore component_store;
	EntityStore entity_store;
	QueryResult query_result;
	ArrayStack *entity_pool;
} ecs_State;

static ecs_State ecs_state = {0};

void pe_ecs_init(uint32_t component_count, ...){
    uint32_t i;
	va_list ap;
	size_t sizes[32];
	size_t offsets[32];
	size_t size = 0;

	va_start(ap, component_count);
	for (i = 0; i < component_count; ++i) {
		sizes[i] = va_arg(ap, size_t);
		offsets[i] = size;
		size += sizes[i];
	}
	va_end(ap);

	ecs_state.entity_pool = pe_stack_create(sizeof(uint32_t));
    ecs_state.component_store.type_count = component_count;
    ecs_state.component_store.cap = INITIAL_CAPACITY;
    ecs_state.component_store.data = calloc(INITIAL_CAPACITY, size);
    ecs_state.component_store.data_size_array = malloc(component_count*sizeof(size_t));
    ecs_state.component_store.data_offset_array = malloc(component_count*sizeof(size_t));
    ecs_state.component_store.size = size;
    memcpy(ecs_state.component_store.data_size_array, sizes, component_count * sizeof(size_t));
	memcpy(ecs_state.component_store.data_offset_array, offsets, component_count * sizeof(size_t));

	ecs_state.query_result.list = calloc(INITIAL_CAPACITY, sizeof(uint32_t));
	ecs_state.entity_store.count = 0;
	ecs_state.entity_store.cap = INITIAL_CAPACITY;
	ecs_state.entity_store.mask_array = malloc(INITIAL_CAPACITY * sizeof(uint32_t));
	ecs_state.entity_store.flag_array = malloc(INITIAL_CAPACITY * sizeof(uint32_t));

	
}

Entity pe_ecs_create(){
    Entity entity;
    uint32_t id;
	printf("entity here 1.");
    if (ecs_state.entity_pool->count > 0)
        {
        id = *(uint32_t*)pe_stack_pop(ecs_state.entity_pool);
		printf("entity here 2.");
        }
    else
        {
        id = ecs_state.entity_store.count++;
        if (ecs_state.entity_store.cap == id){
			printf("entity here 3.");
            uint32_t *new_flag_array = realloc(ecs_state.entity_store.flag_array, ecs_state.entity_store.cap * 2 * sizeof(uint32_t));
            uint32_t *new_mask_array = realloc(ecs_state.entity_store.mask_array, ecs_state.entity_store.cap * 2 * sizeof(uint32_t));
			void *new_data = realloc(ecs_state.component_store.data, ecs_state.component_store.cap * 2 * ecs_state.component_store.size);
			uint32_t *new_query_result_list = realloc(ecs_state.query_result.list, ecs_state.entity_store.cap * 2 * sizeof(uint32_t));
			if (NULL == new_flag_array || NULL == new_mask_array || NULL == new_data || NULL == new_query_result_list) {
                pe_printError("Realloc fail: ", __FILE__, __LINE__);
				exit(1);
			} 
            else {
				printf("entity here 4.");
				ecs_state.entity_store.flag_array = new_flag_array;
				ecs_state.entity_store.mask_array = new_mask_array;
				ecs_state.query_result.list = new_query_result_list;
				ecs_state.entity_store.cap *= 2;

				ecs_state.component_store.data = new_data;
				ecs_state.component_store.cap *= 2;

            }
        }
    }
    ecs_state.entity_store.mask_array[id] = 0;
	ecs_state.entity_store.flag_array[id] = ENT_FLAG_ALIVE;
	entity.id = id;
	return entity;

}

void *pe_ecs_get(uint32_t entity_id, uint32_t component_id){
    
    return (uint8_t*)ecs_state.component_store.data + (entity_id * ecs_state.component_store.size + ecs_state.component_store.data_offset_array[component_id]);
}
    


void pe_ecs_add(uint32_t entity_id, uint32_t component_id, void *data){
    size_t size = ecs_state.component_store.data_size_array[component_id];
	void *ptr = pe_ecs_get(entity_id, component_id);
	ecs_state.entity_store.mask_array[entity_id] |= (1 << component_id);
	memcpy(ptr, data, size);
}

void pe_ecs_remove(uint32_t entity_id, uint32_t component_id){
    ecs_state.entity_store.mask_array[entity_id] &= ~(1 << component_id);
}

uint32_t pe_ecs_has(uint32_t entity_id, uint32_t component_id){
    return 0 != (ecs_state.entity_store.mask_array[entity_id] & (1 << component_id));
}

void pe_ecs_kill(uint32_t entity_id){
    if (0 != (ecs_state.entity_store.flag_array[entity_id] & ENT_FLAG_ALIVE)) {
		ecs_state.entity_store.flag_array[entity_id] &= ~ENT_FLAG_ALIVE;
		ecs_state.entity_store.mask_array[entity_id] = 0;
		pe_stack_push(ecs_state.entity_pool, &entity_id);
	}

}


QueryResult *pe_ecs_query(uint32_t component_count, ...){
	va_list ap;
	uint32_t i, mask = 0;

	ecs_state.query_result.count = 0;

	va_start(ap, component_count);
	for (i = 0; i < component_count; ++i) {
		mask |= (1 << va_arg(ap, uint32_t));
	}
	va_end(ap);

	for (i = 0; i < ecs_state.entity_store.count; ++i) {
		if (0 != (ecs_state.entity_store.flag_array[i] & ENT_FLAG_ALIVE) && mask == (ecs_state.entity_store.mask_array[i] & mask)) {
			ecs_state.query_result.list[ecs_state.query_result.count++] = i;
		}
	}

	int loop;

	for(loop = 0; loop < 10; loop++)
		printf("%d ", ecs_state.query_result.list[loop]);
		
	return &ecs_state.query_result;
}
