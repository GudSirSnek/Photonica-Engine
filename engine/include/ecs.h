#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ENT_FLAG_ALIVE 1

/* an ECS system
things needed:
    entity struct: holds just an ID
    a query struct which holds data on a query
    an entity store struct to hold the entity structs
    a component store struct to hold the components
    a state struct that holds the component store, entity store and query structs as well as a stack that holds all unused entity IDs
    functions:
        init function, takes in the number of components and a variable parameter that takes in the size of the component structs required
        entity create function, creates an entity and returns a handle 
        get function, get component data from an entity
        add function, adds components to an entity
        remove function, remove components from an entity
        has function, returns true if an entity has a certain component
        kill function, destroys entity
        query function, returns a query struct that holds all the IDs that have a certain component
*/


typedef struct{
    uint32_t id;
} Entity;

typedef struct{
    uint32_t count;
    uint32_t cap;
    uint32_t *list;
} QueryResult;


void pe_ecs_init(uint32_t component_count, ...); //init ecs system, takes in N number of components and a variable amount of the components memory size

Entity pe_ecs_create(); //create an entity

void *pe_ecs_get(uint32_t entity_id, uint32_t component_id); //get component data from entity returns a pointer to the data

void pe_ecs_add(uint32_t entity_id, uint32_t component_id, void *data); //adds component, takes in the entity id and component id as well as the component data

void pe_ecs_remove(uint32_t entity_id, uint32_t component_id); //removes a component  from an entity

uint32_t pe_ecs_has(uint32_t entity_id, uint32_t component_id); //returns true if an entity has a component

void pe_ecs_kill(uint32_t entity_id); //kills an entity

/**
 * Find all entities which have components with IDs.
 */

QueryResult *pe_ecs_query(uint32_t component_count, ...); 
