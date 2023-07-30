

/* Loads the content of a GLSL Shader file into a char* variable */
#include "shader.h"
#include "util.h"
#include "IO.h"


GLuint pe_CreateShaderProg(const char* vertexShaderPath, const char* fragmentShaderPath){
    const char *vertexShaderSource = io_read_file(vertexShaderPath);
    const char *fragmentShaderSource = io_read_file(fragmentShaderPath);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        pe_printError("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        pe_printError("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
    }

    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        pe_printError("ERROR::SHADER::PROGRAM::LINKING_FAILED: %s\n", infoLog);
    }
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    pe_free_mem((char*)vertexShaderSource);
    pe_free_mem((char*)fragmentShaderSource);

    return shaderProgram;
}


void pe_UseShaderProgram(GLuint program){
    glUseProgram(program);
}