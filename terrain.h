#ifndef _TERRAIN_H
#define _TERRAIN_H

struct terrain {
    unsigned char c;
    unsigned char data[320];
};

struct terrain *loadterrain(const char *);
void drawterrain(const struct terrain *);

#endif
