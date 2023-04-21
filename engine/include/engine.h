#pragma once

#include <SDL2/SDL.h>
#include "util.h"
#include "maths.h"



void pe_init(void);

void pe_createWindow(const char *name, int width, int height);

void pe_createRenderer(void);

void pe_clearScreen(int r, int g, int b, int a);

void pe_startRender(void);

void pe_endRender(void);

void pe_drawCircle(int centerX, int centerY, int radius);

void pe_drawRect(SDL_Rect* rect, int r, int g, int b, int a);

void pe_getInput(void);

void pe_uninit(void);