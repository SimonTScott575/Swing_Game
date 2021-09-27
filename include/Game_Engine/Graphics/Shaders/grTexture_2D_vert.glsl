#version 330 core
layout (location = 0) in vec2 vert_position;
layout (location = 1) in vec2 vert_UV;

uniform float grZ = 0;

uniform mat3 grView3x3 = mat3(1);
uniform mat3 grProjection3x3 = mat3(1);
uniform mat3 grModel3x3 = mat3(1);

out vec2 v2f_UV;

void main() {
  vec3 pos = grProjection3x3 * grView3x3 * grModel3x3 * vec3(vert_position, 1);
  pos[2] = grZ;
  gl_Position = vec4(pos,1);

  v2f_UV = vert_UV;
}
