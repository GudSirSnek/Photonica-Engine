#include <engine.h>
#include <stdio.h>
#include <StateManager.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FALSE 0
#define TRUE 1

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

unsigned int initState1() {
  printf("state 1 created\n");
  return 0;
}

unsigned int destroyState1() {
  printf("state 1 destroyed\n");
  return 0;
}

unsigned int initState2() {
  printf("state 2 created\n");
  return 0;
}

unsigned int updateState2(float deltatime) {
  printf("state 2 update %f\n", deltatime);
  return 0;
}

unsigned int destroyState2() {
  printf("state 2 destroyed\n");
  return 0;
}

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
    
    pe_vec2 position = {0,0};
    pe_vec2 size = {0.5, 0.5};
    pe_vec4 color = {1,1,0,1};
    StateManager statemanager;
    STATEMANAGER_init(&statemanager);

    State state1 = {0};
    state1.init = initState1;
    state1.destroy = destroyState1;

    State state2 = {0};
    state2.init = initState2;
    state2.update = updateState2;;
    state2.destroy = destroyState2;

    STATEMANAGER_push(&statemanager, &state1);
    STATEMANAGER_update(&statemanager, 10.0f);

    STATEMANAGER_push(&statemanager, &state2);
    STATEMANAGER_update(&statemanager, 10.0f);

    STATEMANAGER_pop(&statemanager);
    STATEMANAGER_update(&statemanager, 10.0f);

    STATEMANAGER_free(&statemanager);

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
