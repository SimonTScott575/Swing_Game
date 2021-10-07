#version 330 core
in vec2 v2f_UV;

uniform sampler2D grTexture;

uniform vec2 screen_pos1;
uniform vec2 screen_pos2;

uniform int gem_count = 0;
uniform vec2 gem_positions[16];
uniform bool gems_is_caught[16];

uniform vec2 portal_position = vec2(0);
uniform float portal_radius = 1;
uniform bool portal_is_lit = false;

out vec4 frag_colour;

void main() {

  vec2 frag_coord = screen_pos1 + (screen_pos2-screen_pos1)*v2f_UV;
  vec4 src_colour = texture(grTexture, v2f_UV);
  frag_colour = src_colour;

  for (int i = 0; i < gem_count; i++) {

    if (gems_is_caught[i]) { continue; }

    float dist = length( frag_coord - gem_positions[i] );

    if ( 0.2 < dist ) {
      frag_colour *= (2/(dist+2.762)/(dist+2.762) + 1);
    }

  }

  if (portal_is_lit) {

    float portal_dist = length(frag_coord - portal_position);
    portal_dist = portal_dist - portal_radius;
    if (portal_dist < 0) {
      portal_dist *= -1;
    }

    frag_colour *= ( 2/(portal_dist+2.762)/(portal_dist+2.762) + 1 );

  }

}
