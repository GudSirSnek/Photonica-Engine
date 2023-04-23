#pragma once
#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "util.h"
#include "maths.h"
#include "shader.h"

typedef struct{
        unsigned int VBO,VAO, EBO;
        int vertices;
        int indices;
} primitive;

//primitive pe_rect = {0,0,0,12,6}; //want to have this as like a global variable that any draw call can access
//somehow triggers a "multiple def error"


void pe_init_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo);

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