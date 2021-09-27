#version 330 core
in vec2 v2f_UV;

uniform sampler2D grTexture;

out vec4 frag_colour;

void main() {

  vec2 uv = v2f_UV;
  uv.y = 1 - uv.y;
  frag_colour = vec4( 1,1,1, texture(grTexture, uv).r );

}
