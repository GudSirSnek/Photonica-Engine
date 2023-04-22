#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "util.h"
#include "maths.h"
#include "shader.h"



void pe_init(void);

void pe_createWindow(const char *name, int width, int height);

void pe_createRenderer(void);

void pe_clearScreen(int r, int g, int b, int a);

void pe_startRender(void);

void pe_endRender(void);

void pe_drawCircle(float cx, float cy, float r, int num_segments);

void pe_drawRect(SDL_Rect* rect, int r, int g, int b, int a);

void pe_getInput(void);

void pe_uninit(void);