#ifndef GR_SHADER_H
#define GR_SHADER_H

#include <stdint.h>

#include <Game_Engine/Maths/Maths.h>

#include "grTexture.h"

typedef struct grShader grShader;
struct grShader {
  grTexture** textures;
  int* _texture_locations;
  uint32_t _textures_length;

  int _Z_location;
  int _Model3x3_location;
  int _View3x3_location;
  int _Projection3x3_location;

  int _Model4x4_location;
  int _View4x4_location;
  int _Projection4x4_location;

  uint32_t _OpenGL_ID;
};

grShader* grCreate_Shader(const char* vertex_path, const char* fragment_path);

void grDestroy_Shader(grShader* shader);

int grGet_location(const char* name, const grShader* shader);
int grGet_Texture_index(int32_t location, const grShader* shader);

// =============================
// Set shader values by location
// =============================

void grSet_Texture(int location, grTexture* texture, grShader* shader);

void grSet_bool(int32_t location, grShader* shader, bool value);

void grSet_float(int32_t location, grShader* shader, float value);
void grSet_float2(int32_t location, grShader* shader, float value0, float value1);
void grSet_float3(int32_t location, grShader* shader, float value0, float value1, float value2);
void grSet_float4(int32_t location, grShader* shader, float value0, float value1, float value2, float value3);

void grSet_int(int32_t location, grShader* shader, int32_t value);
void grSet_int2(int32_t location, grShader* shader, int32_t value0, int32_t value1);
void grSet_int3(int32_t location, grShader* shader, int32_t value0, int32_t value1, int32_t value2);
void grSet_int4(int32_t location, grShader* shader, int32_t value0, int32_t value1, int32_t value2, int32_t value3);

void grSet_uint(int32_t location, grShader* shader, uint32_t value);
void grSet_uint2(int32_t location, grShader* shader, uint32_t value0, uint32_t value1);
void grSet_uint3(int32_t location, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2);
void grSet_uint4(int32_t location, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2, uint32_t value3);

void grSet_Matrix2f(int32_t location, grShader* shader, mMatrix2f matrix);
void grSet_Matrix3f(int32_t location, grShader* shader, mMatrix3f matrix);
void grSet_Matrix4f(int32_t location, grShader* shader, mMatrix4f matrix);

//TODO: arrays
//d void grSet_float_array(int32_t location, float* array, uint64_t array_length); //? grSet_float4_array etc !?

// =========================
// Set shader values by name
// =========================

// ------------
// Single value
// ------------

void grSet_Texture_by_name(const char* name_in_shader, grTexture* texture, grShader* shader);

void grSet_bool_by_name(const char* name, grShader* shader, bool value);

void grSet_float_by_name(const char* name, grShader* shader, float value);
void grSet_float2_by_name(const char* name, grShader* shader, float value0, float value1);
void grSet_float3_by_name(const char* name, grShader* shader, float value0, float value1, float value2);
void grSet_float4_by_name(const char* name, grShader* shader, float value0, float value1, float value2, float value3);

void grSet_int_by_name(const char* name, grShader* shader, int32_t value);
void grSet_int2_by_name(const char* name, grShader* shader, int32_t value0, int32_t value1);
void grSet_int3_by_name(const char* name, grShader* shader, int32_t value0, int32_t value1, int32_t value2);
void grSet_int4_by_name(const char* name, grShader* shader, int32_t value0, int32_t value1, int32_t value2, int32_t value3);

void grSet_uint_by_name(const char* name, grShader* shader, uint32_t value);
void grSet_uint2_by_name(const char* name, grShader* shader, uint32_t value0, uint32_t value1);
void grSet_uint3_by_name(const char* name, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2);
void grSet_uint4_by_name(const char* name, grShader* shader, uint32_t value0, uint32_t value1, uint32_t value2, uint32_t value3);

void grSet_Matrix2f_by_name(const char* name, grShader* shader, mMatrix2f matrix);
void grSet_Matrix3f_by_name(const char* name, grShader* shader, mMatrix3f matrix);
void grSet_Matrix4f_by_name(const char* name, grShader* shader, mMatrix4f matrix);

void grSet_intv_by_name(const char* name, grShader* shader, int* values, int32_t length);
void grSet_float2v_by_name(const char* name, grShader* shader, float* values, int32_t length);

// ---------------
// Multiple Values
// ---------------

#endif
