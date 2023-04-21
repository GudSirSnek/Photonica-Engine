#include <engine.h>
#include <stdio.h>
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

uint32_t w_flags = 0;

void pe_init(void){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        pe_printError("Failed to Initialize SDL: %s", SDL_GetError());
    }

    pe_printInfo("successfully initialized Photonica Engine", NULL);
}

void pe_uninit(void){
    pe_printNeutral("uniniting renderer, window, SDL", NULL);
    SDL_DestroyRenderer(renderer);
    pe_printNeutral("renderer uninitialized",NULL);
    SDL_DestroyWindow(window);
    pe_printNeutral("window uninitialized",NULL);
    SDL_Quit();
    pe_printNeutral("SDL uninitialized",NULL);

    pe_printInfo("Photonica Engine successfully uninitialized",NULL);
}

void pe_createWindow(const char *title, int width, int height){
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, w_flags);
    if (!window){
        pe_printFatalError("ERROR INITIALIZING WINDOW.", SDL_GetError());
    }
}


void pe_createRenderer(void){
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        pe_printFatalError("ERROR INITIALIZING RENDERER.", SDL_GetError());
    }
}

void pe_clearScreen(int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void pe_startRender(void){
    SDL_RenderClear(renderer);
}

void pe_endRender(void){
    SDL_RenderPresent(renderer);
}

void pe_drawCircle(int centerX, int centerY, int radius){
       const int diameter = (radius * 2);

       int x = (radius - 1);
       int y = 0;
       int tx = 1;
       int ty = 1;
       int error = (tx - diameter);

       while (x >= y) {
	
	  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	  /*  Each of the following renders an octant of the circle */
	  SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
	  SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
	  SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
	  SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
	  SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
	  SDL_RenderDrawPoint(renderer,centerX + y, centerY + x);
	  SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
	  SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);

	  if (error <= 0) {
	     ++y;
	     error += ty;
	     ty += 2;
	  }

	  if (error > 0) {
	     --x;
	     tx += 2;
	     error += (tx - diameter);
	  }
    }
}

void pe_drawRect(SDL_Rect* rect, int r, int g, int b, int a){
    SDL_SetRenderDrawColor(renderer, r, g ,b, a);
    SDL_RenderDrawRect(renderer, rect);

}

void pe_getInput(void){

}
