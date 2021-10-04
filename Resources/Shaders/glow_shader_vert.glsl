#version 330 core
layout (location = 0) in vec2 vert_position;
layout (location = 1) in vec2 vert_UV;

out vec2 v2f_screen_pos1;
out vec2 v2f_screen_pos2;

out vec2 v2f_UV;

void main() {

  gl_Position = vec4(vert_position, 0, 1);

  v2f_UV = vert_UV;

}
