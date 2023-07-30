#include <engine.h>
#include <stdio.h>
#include "ecs.h"

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


void system_draw()
{    
    uint8_t flag;
    for(uint32_t i = 0; i < 32; ++i){
        flag = pe_ecs_getFlag(i);
        if (flag){
            SpaceComponent * pos = pe_ecs_GetComponent(i, 0);
            ColorComponent * col = pe_ecs_GetComponent(i, 1);
            pe_drawRect(pos->position, pos->size, col->color);
        }
        
    }
}

void update_systems(){
    
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

    pe_ecs_init(2, sizeof(SpaceComponent), sizeof(ColorComponent));
    setup();
    SDL_Event event;
    Entity player = pe_ecs_create();

    SpaceComponent space = {{400.0, 300.0}, {50.0, 50.0}};
    ColorComponent color = {{255, 0, 255, 255}};

    pe_ecs_AddComponent(player.id, 0, (void*)&space);
    pe_ecs_AddComponent(player.id, 1, (void*)&color);
    printf("player id: %d\n", player.id);


    
   
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
        
        //update_systems();
        //pe_drawRect(space1.position, space1.size, color1.color);

        system_draw();
        //render stuff here
       
        pe_endRender();
    }

    pe_uninit();

    return 0;
}
