#include <Game_Engine/Graphics/grShader.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Game_Engine/dATUM/dFile.h>
// #include <Game_Engine/System/sysFile_IO.h>

grShader* grCreate_Shader(const char* vertex_path, const char* fragment_path) {

  // -------------------------
  // Import shader source code
  // -------------------------

  FILE* file = fopen(vertex_path, "rb");
  if (file == NULL) {
    printf("\nERROR : Failed to fopen");
  }
  uint64_t file_length = dFile_length(file);
  char* vertex_shader_source = calloc(file_length+1, sizeof(char));
  fread(vertex_shader_source, 1, file_length, file);
  fclose(file);

  file = fopen(fragment_path, "rb");
  if (file == NULL) {
    printf("\nERROR : Failed to fopen");
  }
  file_length = dFile_length(file);
  char* fragment_shader_source = calloc(file_length+1, sizeof(char));
  fread(fragment_shader_source, 1, file_length, file);
  fclose(file);

  // Check for errors reading shader files
  if (vertex_shader_source == NULL || fragment_shader_source == NULL) {
    printf("\nERROR: Failed to fread.\n");
  }

  // ------------------------------------------------
  // Vertex and fragment shaders - create and compile
  // ------------------------------------------------

  unsigned int vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader_ID, 1, (const char * const *) &vertex_shader_source, NULL);
  glCompileShader(vertex_shader_ID);
  unsigned int fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader_ID, 1, (const char * const *) &fragment_shader_source, NULL);
  glCompileShader(fragment_shader_ID);
  // Check for errors
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

  // ------------
  // Link shaders
  // ------------

  unsigned int shader_ID = glCreateProgram();
  glAttachShader(shader_ID, vertex_shader_ID);
  glAttachShader(shader_ID, fragment_shader_ID);
  glLinkProgram(shader_ID);
  // Check for errors
  glGetProgramiv(shader_ID, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(shader_ID, 512, NULL, infoLog);
      printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
      printf(infoLog);
  }

  glDeleteShader(vertex_shader_ID);
  glDeleteShader(fragment_shader_ID);

  // ----------
  // Set shader
  // ----------

  grShader* shader = malloc(sizeof(grShader));
  shader->_OpenGL_ID = shader_ID;
  shader->textures = NULL;
  shader->_texture_locations = NULL;
  shader->_textures_length = 0;

  shader->_Z_location = glGetUniformLocation(shader->_OpenGL_ID, "grZ"); //! not auto updated in shader, should be
  shader->_Model3x3_location = glGetUniformLocation(shader->_OpenGL_ID, "grModel3x3");
  shader->_View3x3_location = glGetUniformLocation(shader->_OpenGL_ID, "grView3x3");
  shader->_Projection3x3_location = glGetUniformLocation(shader->_OpenGL_ID, "grProjection3x3");

  shader->_Model4x4_location = glGetUniformLocation(shader->_OpenGL_ID, "grModel4x4");
  shader->_View4x4_location = glGetUniformLocation(shader->_OpenGL_ID, "grView4x4");
  shader->_Projection4x4_location = glGetUniformLocation(shader->_OpenGL_ID, "grProjection4x4");

  return shader;
};

void grDestroy_Shader(grShader* shader) {
  glDeleteProgram(shader->_OpenGL_ID);

  free(shader->textures);
  free(shader->_texture_locations);
  free(shader);
};

// Get shader variable location by name
int grGet_location(const char* name, const grShader* shader) {
  return glGetUniformLocation(shader->_OpenGL_ID, name);
};
// Get texture index
int grGet_Texture_index(int32_t location, const grShader* shader) {
  for (int i = 0; i < shader->_textures_length; i++) {
    if (shader->_texture_locations[i] == location) {
      return i;
    }
  }

  return -1;
}


// =============================
// Set shader values by location
// =============================

// ------------
// Single value
// ------------

// Sets texture in shader, adds texture to shader if location >= 0 AND texture not already uploaded with this location.
void grSet_Texture(int location, grTexture* texture, grShader* shader) {
  if (location != -1) {
    int texture_index = grGet_Texture_index(location, shader);

    if (texture_index >= 0) {
      shader->textures[texture_index] = texture;
    } else {
      shader->_textures_length += 1;

      if (shader->_textures_length == 1) {
        shader->textures = malloc(
          shader->_textures_length * sizeof(grTexture*)
        );
        shader->_texture_locations = malloc(
          shader->_textures_length * sizeof(int*)
        );
      } else {
        shader->textures = realloc(
          shader->textures,
          shader->_textures_length * sizeof(grTexture*)
        );
        shader->_texture_locations = realloc(
          shader->_texture_locations,
          shader->_textures_length * sizeof(int*)
        );
      }

      shader->textures[shader->_textures_length - 1] = texture;
      shader->_texture_locations[shader->_textures_length - 1] = location;

      glUseProgram(shader->_OpenGL_ID);
      glUniform1i(location, shader->_textures_length - 1);
    }
  }
}

void grSet_bool(int32_t location, grShader* shader, bool value) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform1i(location, value);
}

void grSet_float(int32_t location, grShader* shader, float value) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform1f(location, value);
}
void grSet_float2(int32_t location, grShader* shader, float value0, float value1) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform2f(location, value0, value1);
}
void grSet_float3(int32_t location, grShader* shader, float value0, float value1, float value2) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform3f(location, value0, value1, value2);
}
void grSet_float4(int32_t location, grShader* shader, float value0, float value1, float value2, float value3) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform4f(location, value0, value1, value2, value3);
}

void grSet_int(int32_t location, grShader* shader, int32_t value) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform1i(location, value);
}
void grSet_int2(int32_t location, grShader* shader, int32_t value0, int32_t value1) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform2i(location, value0, value1);
}
void grSet_int3(int32_t location, grShader* shader, int32_t value0, int32_t value1, int32_t value2) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform3i(location, value0, value1, value2);
}
void grSet_int4(int32_t location, grShader* shader, int32_t value0, int32_t value1, int32_t value2, int32_t value3) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform4i(location, value0, value1, value2, value3);
}

void grSet_uint(int32_t location, grShader* shader, uint32_t value) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform1ui(location, value);
}
void grSet_uint2(int32_t location, grShader* shader, uint32_t value0, uint32_t value1) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform2ui(location, value0, value1);
}
void grSet_uint3(int32_t location, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform3ui(location, value0, value1, value2);
}
void grSet_uint4(int32_t location, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2, uint32_t value3) {
  glUseProgram(shader->_OpenGL_ID);
  glUniform4ui(location, value0, value1, value2, value3);
}

void grSet_Matrix2f(int32_t location, grShader* shader, mMatrix2f matrix) {
  glUseProgram(shader->_OpenGL_ID);
  glUniformMatrix2fv(location, 1, GL_TRUE, (const GLfloat *) matrix.i);
}
void grSet_Matrix3f(int32_t location, grShader* shader, mMatrix3f matrix) {
  glUseProgram(shader->_OpenGL_ID);
  glUniformMatrix3fv(location, 1, GL_TRUE, (const GLfloat *) matrix.i);
}
void grSet_Matrix4f(int32_t location, grShader* shader, mMatrix4f matrix) {
  glUseProgram(shader->_OpenGL_ID);
  glUniformMatrix4fv(location, 1, GL_TRUE, (const GLfloat *) matrix.i);
}

// --------------
// Multiple value
// --------------

//TODO...

// =========================
// Set shader values by name
// =========================

// ------------
// Single value
// ------------

void grSet_Texture_by_name(const char* name, grTexture* texture, grShader* shader) {
  int location = glGetUniformLocation(shader->_OpenGL_ID, name);
  grSet_Texture(location, texture, shader);
}

void grSet_bool_by_name(const char* name, grShader* shader, bool value) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform1i(location, value);
}

void grSet_float_by_name(const char* name, grShader* shader, float value) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform1f(location, value);
}
void grSet_float2_by_name(const char* name, grShader* shader, float value0, float value1) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform2f(location, value0, value1);
}
void grSet_float3_by_name(const char* name, grShader* shader, float value0, float value1, float value2) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform3f(location, value0, value1, value2);
}
void grSet_float4_by_name(const char* name, grShader* shader, float value0, float value1, float value2, float value3) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform4f(location, value0, value1, value2, value3);
}

void grSet_int_by_name(const char* name, grShader* shader, int32_t value) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform1i(location, value);
}
void grSet_int2_by_name(const char* name, grShader* shader, int32_t value0, int32_t value1) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform2i(location, value0, value1);
}
void grSet_int3_by_name(const char* name, grShader* shader, int32_t value0, int32_t value1, int32_t value2) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform3i(location, value0, value1, value2);
}
void grSet_int4_by_name(const char* name, grShader* shader, int32_t value0, int32_t value1, int32_t value2, int32_t value3) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform4i(location, value0, value1, value2, value3);
}

void grSet_uint_by_name(const char* name, grShader* shader, uint32_t value) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform1ui(location, value);
}
void grSet_uint2_by_name(const char* name, grShader* shader, uint32_t value0, uint32_t value1) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform2ui(location, value0, value1);
}
void grSet_uint3_by_name(const char* name, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform3ui(location, value0, value1, value2);
}
void grSet_uint4_by_name(const char* name, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2, uint32_t value3) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniform4ui(location, value0, value1, value2, value3);
}

void grSet_Matrix2f_by_name(const char* name, grShader* shader, mMatrix2f matrix) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniformMatrix2fv(location, 1, GL_TRUE, (const GLfloat *) matrix.i);
}
void grSet_Matrix3f_by_name(const char* name, grShader* shader, mMatrix3f matrix) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniformMatrix3fv(location, 1, GL_TRUE, (const GLfloat *) matrix.i);
}
void grSet_Matrix4f_by_name(const char* name, grShader* shader, mMatrix4f matrix) {
  int32_t location = glGetUniformLocation(shader->_OpenGL_ID, name);
  glUseProgram(shader->_OpenGL_ID);
  glUniformMatrix4fv(location, 1, GL_TRUE, (const GLfloat *) matrix.i);
}

// ---------------
// Multiple values
// ---------------

//TODO...

// +++++++++


// const char* vertex_shader_source = read_file_PATH(vertex_path);
// const char* fragment_shader_source = read_file_PATH(fragment_path);
// // Check for errors reading shader files
// if (vertex_shader_source == NULL || fragment_shader_source == NULL) {
//   printf("\nERROR: Failed to read_file.\n");
// }






// //! set_texture_by_name would be good too but would need to hold onto names in shader
// void grSet_textures_by_name_ALL(char** name_in_shader, grTexture** textures, uint32_t textures_length, grShader* shader) {
//   if (shader->textures == NULL) {
//     shader->textures = malloc(textures_length*sizeof(grTexture*));
//     shader->textures_length = textures_length;
//   }
//
//   glUseProgram(shader->OpenGL_ID);
//   for (int i = 0; i < textures_length; i++) {
//     shader->textures[i] = textures[i];
//     int location = glGetUniformLocation(shader->OpenGL_ID, name_in_shader[i]);
//     glUniform1i(location, i);
//   }
// };
