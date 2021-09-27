#include "../grScreen.h"

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

//TEMP
grScreen* screen;
grShader* screen_shader;
void postprocessing_cb(grScreen* s_in) {

  grBlit(s_in, screen, NULL);

  grBlit(screen, s_in, screen_shader);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* initalize_window() {

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

  // ===============
  // Initialize GLFW
  // ===============

  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
  grInit_Screen(WINDOW_SIZE_X, WINDOW_SIZE_Y);

  // ====
  // Mesh
  // ====

  float mesh_vertices[] = { -0.5, -0.5,   0, 0,
                                0.5,  0.5,   1, 1,
                               -0.5,  0.5,   0, 1,
                                0.5, -0.5,   1, 0  };
  int32_t mesh_indices[] = { 0,1,2, 0,3,1 };

  uint64_t mesh_size_of_vertex = 4*sizeof(float);
  uint64_t mesh_vertices_count = 4;
  uint64_t mesh_indices_count = 6;

  uint32_t mesh_counts[2] = { 2, 2 };
  grType mesh_types[2] = { grTypes._float, grTypes._float };
  size_t mesh_offsets[2] = { 0, 2*sizeof(float) };

  // =====
  // Model
  // =====

  struct mesh_IDs mesh_IDs = initialize_mesh(
    mesh_vertices, mesh_indices, mesh_size_of_vertex*mesh_vertices_count, sizeof(int32_t)*mesh_indices_count
  );

  for (int i = 0; i < 2; i++) {
    glVertexAttribPointer(i, mesh_counts[i], mesh_types[i], GL_FALSE, mesh_size_of_vertex, (void*) mesh_offsets[i]);
    glEnableVertexAttribArray(i);
  }

  // =======
  // Texture
  // =======

  uint32_t texture_ID = initialize_texture("Graphics/tests/awesomeface.png");

  // ======
  // Shader
  // ======

  uint32_t shader_ID = initialize_shader("Graphics/Shaders/grTexture_2D_vert.glsl", "Graphics/Shaders/grTexture_2D_frag.glsl");

  // ==========
  // Set Shader
  // ==========

  glUseProgram(shader_ID);
  glUniform1i(glGetUniformLocation(shader_ID, "grTexture"), 0);

  // ======
  // Screen
  // ======

  grSet_Clear_Screen_Colour((float[4]){1,1,1,1}, grBack_Screen);
  grSet_Clear_Screen_Colour((float[4]){1,1,1,1}, grFront_Screen);

  grTexture* screen_texture = grCreate_Texture_NULL(800,800);
  screen_shader = grCreate_Shader("Graphics/tests/test_postprocessing_vert.glsl", "Graphics/tests/test_postprocessing_frag.glsl");
  grSet_Texture_by_name("grTexture", screen_texture, screen_shader);
  screen = grCreate_Screen(screen_texture);

  // ==============
  // Rendering Loop
  // ==============

  while (!glfwWindowShouldClose(window)) {

    // ------------
    // clear screen
    // ------------

    grClear_Screen_Colour(grBack_Screen);

    // ------
    // render
    // ------

    glUseProgram(shader_ID);

    // set texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_ID);

    // set shader properties
    glBindVertexArray(mesh_IDs.VAO);

    // draw
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    postprocessing_cb(grBack_Screen);

    grSwap_Screens(window);

    // ------
    // events
    // ------

    glfwPollEvents();

  }

  // ========
  // Clean Up
  // ========

  glfwTerminate();

  printf("\nDEBUG : PROGRAM ENDING SUCCESSFULLY\n");

  return 0;
}
