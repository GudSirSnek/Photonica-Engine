#include "engine.h"



static SDL_Window *window = NULL;
static SDL_GLContext maincontext;
uint32_t w_flags = 0;
GLuint shader_default;

M4x4 r_proj;

primitive pe_rect = {0,0,0,12,6};

primitive Texture_rect = {0,0,0,20,6};

ScreenSpace screen = {0};

void pe_init_rect(unsigned int *vao, unsigned int *vbo, unsigned int *ebo){
    //	 x,	y, z, u, v
	float vertices[] = {
		 0.5,  0.5, 0,
		 0.5, -0.5, 0,
		-0.5, -0.5, 0,
		-0.5,  0.5, 0,
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);
	glGenBuffers(1, ebo);

	glBindVertexArray(*vao);

	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// xyz
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0);
}

void pe_init_texture(Texture *Texture_object){
    // configure VAO/VBO
    float vertices[] = { 
        // pos              // tex
        1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,  0.0f, 1.0f 
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Texture_object->Text_obj.vertices = sizeof(vertices)/sizeof(vertices[0]);

    glGenVertexArrays(1, &Texture_object->Text_obj.VAO);
    glGenBuffers(1, &Texture_object->Text_obj.VBO);
    glGenBuffers(1, &Texture_object->Text_obj.EBO);
    glBindVertexArray(Texture_object->Text_obj.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Texture_object->Text_obj.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Texture_object->Text_obj.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void pe_create_texture(Texture *Texture_object, const char * Texture_path, const char * VertexPath, const char * FragPath){

    Texture_object->Shader = pe_CreateShaderProg(VertexPath, FragPath);
    // ---------
    glGenTextures(1, &Texture_object->Texture);
    glBindTexture(GL_TEXTURE_2D, Texture_object->Texture); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(1); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(Texture_path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        pe_printError("Failed to load texture: %s", Texture_path);
    }
    stbi_image_free(data);
    pe_UseShaderProgram(Texture_object->Shader);
    glUniform1i(glGetUniformLocation(Texture_object->Shader, "image"), 0);
}

void pe_init(void){
    /*
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        pe_printError("Failed to Initialize SDL: %s", SDL_GetError());
    }

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    pe_printInfo("successfully initialized Photonica Engine", NULL);
    */
   // Initialize SDL 
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        pe_printError("Failed to Initialize SDL: %s", SDL_GetError());
    }

    atexit (SDL_Quit);
    SDL_GL_LoadLibrary(NULL); // Default OpenGL is fine.

    // Request an OpenGL 4.5 context (should be core)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    pe_printInfo("successfully initialized SDL2", NULL);

    
}

void pe_uninit(void){

    pe_printInfo("uninitalizing renderer, window, SDL", NULL);
    //SDL_DestroyRenderer(renderer);
    pe_printInfo("renderer uninitialized",NULL);
    SDL_DestroyWindow(window);
    pe_printInfo("window uninitialized",NULL);
    SDL_Quit();
    pe_printInfo("SDL2 uninitialized",NULL);

    pe_printInfo("Photonica Engine successfully uninitialized",NULL);
}

void pe_createWindow(const char *title, int width, int height){
    // Create the window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window){
        pe_printFatalError("ERROR INITIALIZING WINDOW.", SDL_GetError());
    }
    screen.width = width;
    screen.height = height;

    pe_printInfo("successfully created Window", NULL);
}


void pe_createRenderer(void){

   // glad: load all OpenGL function pointers
    // ---------------------------------------
    maincontext = SDL_GL_CreateContext(window);
    if (maincontext == NULL){
        pe_printFatalError("ERROR INITIALIZING OPENGL CONTEXT", SDL_GetError());
    }

    // Check OpenGL properties
    pe_printInfo("successfully loaded OpenGL", NULL);
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    pe_printNeutral("Vendor:   %s", glGetString(GL_VENDOR));
    pe_printNeutral("Renderer: %s", glGetString(GL_RENDERER));
    pe_printNeutral("Version:  %s", glGetString(GL_VERSION));

    // Use v-sync
    SDL_GL_SetSwapInterval(1);

    // Disable depth test and face culling.
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    int w,h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_default = pe_CreateShaderProg("../res/shaders/Vshader.s", "../res/shaders/Fshader.s");
    glUseProgram(shader_default);
    pe_init_rect(&pe_rect.VAO, &pe_rect.VBO, &pe_rect.EBO);
    M4x4_ortho(screen.projection, 0, 800, 600, 0, -1 ,1);  
    
    GLint proj_loc = glGetUniformLocation(shader_default, "projection");

    if (proj_loc == -1){
        pe_printFatalError("ERROR, uniform not found", SDL_GetError());
    }
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, *screen.projection);
}

void pe_clearScreen(int r, int g, int b, int a){
    //SDL_SetRenderDrawColor(renderer, r, g, b, a);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void pe_startRender(void){
    //SDL_RenderClear(renderer);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void pe_endRender(void){
    //SDL_RenderPresent(renderer);
    glFinish();
    SDL_GL_SwapWindow(window);
}

void pe_drawCircle(float cx, float cy, float r, int num_segments)
{

}

void pe_drawRect(pe_vec2  position, pe_vec2 size, pe_vec4 color){
    pe_vec4 GLcolor = {color[0]/255, color[1]/255, color[2]/255, color[3]/255};

    pe_UseShaderProgram(shader_default);
    M4x4 model;
    
    M4x4_identity(model);
    M4x4_translate(model, position[0], position[1], 0);
    //scale matrix
    M4x4_scale_aniso(model, model, size[0], size[1], 1);
    //printf("draw data: %f, %f, %f, %f, %f, %f, %f\n", position[0], position[1], size[0], size[1], color[0], color[1], color[2]);
    glUniformMatrix4fv(glGetUniformLocation(shader_default, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform4fv(glGetUniformLocation(shader_default, "color"), 1, GLcolor);
    glBindVertexArray(pe_rect.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void pe_DrawTexture(Texture *Texture_object, pe_vec2  position, pe_vec2 size){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture_object->Texture);

    pe_UseShaderProgram(Texture_object->Shader);

    M4x4 model;
    
    M4x4_identity(model);
    M4x4_translate(model, position[0], position[1], 0);
    //scale matrix
    M4x4_scale_aniso(model, model, size[0], size[1], 1);
    glUniformMatrix4fv(glGetUniformLocation(Texture_object->Shader, "model"), 1, GL_FALSE, &model[0][0]);
    
    glUniformMatrix4fv(glGetUniformLocation(Texture_object->Shader, "projection"), 1, GL_FALSE, *screen.projection);

    glBindVertexArray(Texture_object->Text_obj.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

};
void pe_getInput(void){

}
