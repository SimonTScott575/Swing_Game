#version 330 core
in vec2 v2f_UV;

uniform sampler2D grTexture;

uniform vec2 screen_pos1;
uniform vec2 screen_pos2;

uniform int gem_count = 0;
uniform vec2 gem_positions[16];
uniform bool gems_is_caught[16];

out vec4 frag_colour;

void main() {

  vec2 frag_coord = screen_pos1 + (screen_pos2-screen_pos1)*v2f_UV;
  vec4 src_colour = texture(grTexture, v2f_UV);
  frag_colour = src_colour;

  for (int i = 0; i < gem_count; i++) {

    if (gems_is_caught[i]) { continue; }

    float dist = length( frag_coord - gem_positions[i] );

    if ( 0.2 < dist ){// frag_coord.x < 0) {
      frag_colour *= (2/(dist+2.762)/(dist+2.762) + 1);
    }

  }

}
