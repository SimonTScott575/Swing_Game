#include "../Defaults/grRendering_System.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <Game_Engine/include/glad/glad.h>
#include <Game_Engine/include/GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Game_Engine/include/stbi_image.h>

#include <Game_Engine/Graphics/Formats/grColours.h>
#include <Game_Engine/Graphics/Formats/grTypes.h>

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 800

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initalize_window() {

  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "UNIT_TEST", NULL, NULL);
  if (window == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return NULL;
  }
  // glfwMakeContextCurrent(window); //?
  glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

  glfwMakeContextCurrent(window);
  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    glfwTerminate();
  }

  return window;

}

struct mesh_IDs {
  uint32_t VAO;
  uint32_t VBO;
  uint32_t EBO;
};
struct mesh_IDs initialize_mesh(void* vertices, int32_t* indices, size_t vertices_size, size_t indices_size) {

  struct mesh_IDs mesh_IDs;

  // prepare buffers
  glGenVertexArrays(1, &mesh_IDs.VAO);
  glGenBuffers(1, &mesh_IDs.VBO);
  glGenBuffers(1, &mesh_IDs.EBO);

  glBindVertexArray(mesh_IDs.VAO);
  glBindBuffer(GL_ARRAY_BUFFER, mesh_IDs.VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_IDs.EBO);

  // send data to GPU
  glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

  return mesh_IDs;

}

uint32_t initialize_texture(char* texture_path) {

  //
  stbi_set_flip_vertically_on_load(1);
  int32_t width;
  int32_t height;
  int32_t nrChannels;
  unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 4); //TODO: would be nice to enforce colour_format instead of just use it as descriptor
  if (data == NULL) {
    printf("\nERROR : Unable to load texture.\n");
  }

  uint32_t texture_ID;

  glGenTextures(1, &texture_ID);
  glBindTexture(GL_TEXTURE_2D, texture_ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  return texture_ID;

}

uint32_t initialize_shader(char* vert_path, char* frag_path) {

    // read in vertex shader
    FILE* file = fopen(vert_path, "rb");
    if (file == NULL) { printf("\nERROR : Failed to fopen\n"); }
    fseek(file, 0, SEEK_END);
    uint64_t file_length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* vertex_shader_source = calloc(file_length+1, sizeof(char));
    fread(vertex_shader_source, 1, file_length, file);
    fclose(file);

    // read in fragment shader
    file = fopen(frag_path, "rb");
    if (file == NULL) {
      printf("\nERROR : Failed to fopen\n");
    }
    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* fragment_shader_source = calloc(file_length+1, sizeof(char));
    fread(fragment_shader_source, 1, file_length, file);
    fclose(file);

    // check for errors reading shader files
    if (vertex_shader_source == NULL || fragment_shader_source == NULL) {
      printf("\nERROR: Failed to fread.\n");
    }

    // create vertex and fragment shaders
    unsigned int vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_ID, 1, (const char * const *) &vertex_shader_source, NULL);
    glCompileShader(vertex_shader_ID);
    unsigned int fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_ID, 1, (const char * const *) &fragment_shader_source, NULL);
    glCompileShader(fragment_shader_ID);
    // check for errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader_ID, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
        printf(infoLog);
    }
    glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader_ID, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
        printf(infoLog);
    }

    // create shader from vertex and fragment shaders
    uint32_t shader_ID = glCreateProgram();
    glAttachShader(shader_ID, vertex_shader_ID);
    glAttachShader(shader_ID, fragment_shader_ID);
    glLinkProgram(shader_ID);
    // check for errors
    glGetProgramiv(shader_ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_ID, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
        printf(infoLog);
    }

    // delete vertex and fragment shaders
    glDeleteShader(vertex_shader_ID);
    glDeleteShader(fragment_shader_ID);

    return shader_ID;
}

int main() {

  // =================
  // Initialize Window
  // =================

  GLFWwindow* window = initalize_window();
  if (window == NULL) {
    return 1;
  }

  // ===================
  // Initialize Graphics
  // ===================

  grInit_Colours();
  grInit_Types();

  // =====
  // Model
  // =====

  grModel* model = grCreate_Model("Graphics/Meshes/grRect2D.obj");

  struct mesh_IDs mesh_IDs = {
    .VAO = model->_OpenGL_IDs.VAO,
    .VBO = model->_OpenGL_IDs.VBO,
    .EBO = model->_OpenGL_IDs.EBO
  };

  // =======
  // Texture
  // =======

  grTexture* texture = grCreate_Texture("Graphics/tests/awesomeface.png");

  uint32_t texture_ID = texture->_OpenGL_ID;

  // ======
  // Shader
  // ======

  grShader* shader = grCreate_Shader("Graphics/Shaders/grTexture_2D_vert.glsl",
                                     "Graphics/Shaders/grTexture_2D_frag.glsl");

  uint32_t shader_ID = shader->_OpenGL_ID;

  // ========
  // Renderer
  // ========

  mFrame2D frame = mFrame2D_I;

  grRenderer* renderer = grCreate_Renderer_2D(&frame, model, shader);

  // ======
  // Camera
  // ======

  mFrame2D camera_frame = mFrame2D_I;

  grCamera2D* camera = grCreate_Camera2D(&camera_frame, 2, 2);

  // grAdd_Renderer_2D(renderer, camera);

  // Rendering System

  grRendering_System2D* rs = grCreate_Rendering_System2D(camera);

  dAppend_LLRnd(renderer, rs->_renderers);

  // ==========
  // Set Shader
  // ==========

  grSet_Texture_by_name("grTexture", texture, shader);

  // ==============
  // Rendering Loop
  // ==============

  glClearColor(1,1,1,1);

  while (!glfwWindowShouldClose(window)) {

    // clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // draw
    grRender_Rendering_System2D(rs);
    // grRender_Camera2D(camera);

    // system
    glfwSwapBuffers(window);
    glfwPollEvents();

  }

  // ========
  // Clean Up
  // ========

  grDestroy_Rendering_System2D(rs);
  grDestroy_Camera2D(camera);
  grDestroy_Renderer(renderer);

  glfwTerminate();

  printf("\nDEBUG : PROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
