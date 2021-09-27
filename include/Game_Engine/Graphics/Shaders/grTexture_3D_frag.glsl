#version 330 core
in vec2 v2f_UV;

uniform sampler2D grTexture;

out vec4 frag_colour;

void main() {
  frag_colour = texture(grTexture, v2f_UV);
}
