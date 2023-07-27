#include <engine.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FALSE 0
#define TRUE 1

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)


typedef struct{
    int x, y;//position
    SDL_Rect rect;//hitbox
    //img texture
}Entity;
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
    
    Entity player;
    player.x = 400;
    player.y = 300;
    SDL_Rect temp = {400, 300, 100, 100};
    player.rect = temp;
    pe_vec2 position = {400, 300};
    pe_vec2 size = {50, 50};
    pe_vec4 color = {255,255,0,255};

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
        pe_drawRect(position, size, color);
        //render stuff here
       
        pe_endRender();
    }

    pe_uninit();

    return 0;
}
