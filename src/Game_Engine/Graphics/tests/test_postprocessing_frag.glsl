#version 330 core
in vec2 v2f_UV;

uniform sampler2D grTexture;

out vec4 frag_colour;

void main() {

  vec4 img_pixel = texture(grTexture, v2f_UV);

  frag_colour = 1 - img_pixel; // 

}
