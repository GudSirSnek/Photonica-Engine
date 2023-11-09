#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>


GLuint pe_CreateShaderProg(const char* vertexShaderPath, const char* fragmentShaderPath);

void pe_UseShaderProgram(GLuint program);


#endif