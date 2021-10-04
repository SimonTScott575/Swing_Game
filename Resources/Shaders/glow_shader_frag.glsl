#version 330 core
in vec2 v2f_UV;

uniform sampler2D grTexture;

uniform vec2 screen_pos1;
uniform vec2 screen_pos2;

uniform vec2 gem_pos = vec2(-1);

out vec4 frag_colour;

void main() {

  vec2 frag_coord = screen_pos1 + (screen_pos2-screen_pos1)*v2f_UV;
  float dist = length( frag_coord - gem_pos );

  vec4 src_colour = texture(grTexture, v2f_UV);

  if ( 0.05 < dist && dist < 5){// frag_coord.x < 0) {
    frag_colour = src_colour*1.1; // /dist; // vec4(1 - vec3(src_colour), 1);
  } else {
    frag_colour = src_colour;
  }

}
