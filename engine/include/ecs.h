#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "maths.h"
#include "stack.h"
#define ENT_FLAG_ALIVE 1

/* an ECS system

theres an array for each component
entity ID is used to index the arrays
a bitmask can be used to store what components each entity has 
a query function would be useful to reduce the amount of entities each system has to iterate through 
-> the query function will probably be O(n) complexity
->the query function could fill in the query requests for all systems in one pass (aka with one pass, query render components, position, etc)
-> multiple query result arrays would be needed
->keep a stack pool to hold what IDs have not been used
each component is a struct
*/


typedef struct{ //space component holds position and size
    pe_vec2 position;
    pe_vec2 size;
}SpaceComponent;

typedef struct{//holds color data for the basic rendering
    pe_vec4 color;
}ColorComponent;

typedef struct {
    uint32_t Component_count;
    size_t *sizes;
    SpaceComponent *space_components;
    ColorComponent *color_components;

    void **Components;

} ComponentStore;

typedef struct{
    uint8_t *flag_array;
    uint32_t *mask_array;
    uint32_t count;
    uint32_t cap;
} EntityStore;

typedef struct {
	uint32_t id;
} Entity;


typedef struct{
    uint32_t count;
    uint32_t cap;
    uint32_t *list;
} QueryResult;

typedef struct{
    EntityStore entity_store;
    ComponentStore component_store;
    QueryResult *query_results;
    ArrayStack *entity_pool;

}State;


void pe_ecs_init(uint32_t component_count, ...); //init ecs system, takes in N number of components and a bitmask showing what components are used

Entity pe_ecs_create(); //create an entity


void * pe_ecs_GetComponent(uint32_t entity_id, uint8_t component_id);

void pe_ecs_AddComponent(uint32_t entity_id, uint8_t component_id, void * data);

SpaceComponent * pe_ecs_GetSpaceComp(uint32_t entity_id);

ColorComponent * pe_ecs_GetColorComp(uint32_t entity_id);

void pe_ecs_AddSpaceComp(uint32_t entity_id, SpaceComponent *space);

void pe_ecs_AddColorComp(uint32_t entity_id, ColorComponent *color);

void pe_ecs_kill(Entity entity); //kills an entity

uint8_t pe_ecs_getFlag(uint32_t entity_id);

/**
 * Find all entities which have components with IDs.
 */

QueryResult *pe_ecs_query(uint32_t component_count, ...); 


void pe_ecs_getQuery();