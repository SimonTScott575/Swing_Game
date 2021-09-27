#version 330 core


uniform vec4 grColour = vec4(1, 0.41, 0.70, 1);

out vec4 frag_colour;

void main() {
  frag_colour = grColour;
  if (frag_colour.a == 0) {
    discard;
  }
}
