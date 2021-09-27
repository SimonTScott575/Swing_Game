#version 330 core
layout (location = 0) in vec3 vert_position;
layout (location = 1) in vec4 vert_colour;

uniform float grZ; //!!!

uniform mat4 grModel4x4;
uniform mat4 grView4x4;
uniform mat4 grProjection4x4;

out vec4 v2f_colour;

void main() {
  vec4 pos = grProjection4x4 * grView4x4 * grModel4x4 * vec4(vert_position, 1); //!!! grZ // grProjection3x3 * grView3x3 * grModel3x3 *
  gl_Position = pos;

  v2f_colour = vert_colour;
}
