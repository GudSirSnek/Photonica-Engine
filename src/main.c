#include <engine.h>
#include "ecs.h"
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FALSE 0
#define TRUE 1

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)


///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
int game_is_running = FALSE;
int last_frame_time = 0;


///////////////////////////////////////////////////////////////////////////////
// Function to poll SDL events and process keyboard input
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Setup function that runs once at the beginning of our program
///////////////////////////////////////////////////////////////////////////////
void setup(void) {
    
    
}

///////////////////////////////////////////////////////////////////////////////
// Update function with a fixed time step
///////////////////////////////////////////////////////////////////////////////
void update(void) {
    // Calculate how much we have to wait until we reach the target frame time
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    // Only delay if we are too fast too update this frame
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    // Get a delta time factor converted to seconds to be used to update my objects
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;

    // Store the milliseconds of the current frame
    last_frame_time = SDL_GetTicks();
    //printf("\n");
}


//converts world coordinates to space coordinates
float SpaceToScreenSpace(int x, int y){
    return 0;
}

/*
position component

shader component(for now just solid colour shader)

*/


typedef struct{
    pe_vec2 position;
    pe_vec2 size;
}PositionComponent;

typedef struct{
    pe_vec4 color;
}ShaderSolidComponent;

void system_draw(){
    
    uint32_t i;
	QueryResult *qr = pe_ecs_query(2, 0, 1);
	for (i = 0; i < qr->count; ++i) {
		PositionComponent *pos = (PositionComponent*)pe_ecs_get(qr->list[i], 0);
		ShaderSolidComponent *spr = (ShaderSolidComponent*)pe_ecs_get(qr->list[i], 1);

		pe_drawRect(pos->position, pos->size, spr->color);
	}
}


///////////////////////////////////////////////////////////////////////////////
// Main function
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* args[]) {
    //game_is_running = initialize_window();
    game_is_running = 1;
    pe_init();
    pe_createWindow("A window", WINDOW_WIDTH, WINDOW_HEIGHT);
    pe_createRenderer();
    setup();
    SDL_Event event;
    
    pe_ecs_init(2, sizeof(PositionComponent), sizeof(ShaderSolidComponent));
    Entity player = pe_ecs_create();
    PositionComponent pos = {0};
    ShaderSolidComponent shad = {0};
    pos.position[0] = 400;
    pos.position[1] = 300;
    pos.size[0] = 50;
    pos.size[1] = 50;

    pe_ecs_add(player.id, 0, &pos);
    pe_vec4 color = {255,255,0,255};
    shad.color[0] = color[0];
    shad.color[1] = color[1];
    shad.color[2] = color[2];
    shad.color[3] = color[3];

    pe_ecs_add(player.id, 1, &shad);

    while (game_is_running) {
       
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                game_is_running = FALSE;
                break;
        }
        update();
        pe_clearScreen(0, 0, 0, 255);
        

        pe_startRender();
        system_draw();
        //render stuff here
       
        pe_endRender();
    }

    pe_uninit();

    return 0;
}
