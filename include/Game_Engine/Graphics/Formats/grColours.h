#ifndef GR_COLOURS_H
#define GR_COLOURS_H

typedef int grColour;

struct grColours {
  grColour RGB;
  grColour RGBA;
  grColour R;
};

extern struct grColours grColours;

void grInit_Colours(void);

#endif
