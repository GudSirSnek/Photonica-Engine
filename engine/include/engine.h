#pragma once
#include <glad/glad.h>
#include "SDL2/SDL.h"
#include <stdio.h>
#include "util.h"
#include "maths.h"
#include "shader.h"
#include "stb_image.h"

typedef struct primitive {
  unsigned int VBO, VAO, EBO;
  int vertices;
  int indices;
} primitive;

typedef struct Texture{
  primitive Text_obj;
  unsigned int Texture;
  GLuint Shader;
}Texture;

typedef struct screen {
  int width, height;
  M4x4 projection;
} ScreenSpace;



void pe_init_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo);

void pe_init_texture(Texture *Texture_object);

void pe_create_texture(Texture *Texture_object, const char * Texture_path, const char * VertexPath, const char * FragPath);

void pe_init(void);

void pe_createWindow(const char *name, int width, int height);

void pe_createRenderer(void);

void pe_clearScreen(int r, int g, int b, int a);

void pe_startRender(void);

void pe_endRender(void);

void pe_drawCircle(float cx, float cy, float r, int num_segments);

void pe_drawRect(pe_vec2 position, pe_vec2 size, pe_vec4 color);

void pe_DrawTexture(Texture *Texture_object, pe_vec2  position, pe_vec2 size);

void pe_getInput(void);

void pe_uninit(void);