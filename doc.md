# photonica documentation



## Photonica ECS

### Intro
The Photonica ECS (Entity Component System) is a large datastructure method for handling many different types of data for entity systems.

The ECS structure has 3 primary concepts:

1. Entities
2. Components
3. Systems

The ECS structure contains the entities and components while the systems are functions that are user declared that act on the components.

#### Entities
Entities are used as indexes to allow systems for accessing component data, an Entity is simply a C struct that contains an unsigned 32 bit integer.

#### Components
Components are arrays that contain a specific component data for all entities (position data for example). The data inside each component can be accessed using an entity ID.

#### Systems
Systems are functions that acts and modifies on the component data, typically a system will iterate through an entire component list.


## structure

The ECS structure starts with the ECS state structure which contains the following properties:
2. Component_Store Struct that contains an integer telling how many components are in the structure and as well as a dynamic double array containing all component data
3. query_Results structure which contains the results from an ECS query
4. Entity_pool list that is a stack that contains all the free entity IDs

#### EntityStore
This is a struct that contains the number of entities in use, the entity cap, the flag and mask arrays. 

The flag array is a simple 8 bit integer array whos values are either 1 or 0, it is simply there to flag which entities are currently alive/active. 

The mask array contains bitmasks for each entity which outlines what components each entity has.

#### Component_Store

This C structure holds all of the component data, the number of components present as well as an array which contains the bytesizes for each component.

The component data is a double void* array, each "Row" is a component array which contains the data for all entities regarding said component





