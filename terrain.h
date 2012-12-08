#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <stdio.h>
#include "vmode13h.h"

int loadterrain();
void drawterrain();

struct terrain {
    unsigned char c;
    unsigned char data[320];
};

struct terrain current_terrain;


int
loadterrain() {
    int x;
    FILE *tdata;

    if ((tdata = fopen("TERRAIN.DAT", "rb")) == NULL) {
        fprintf(stderr, "Cannot open data file: TERRAIN.DAT\n");
        return (1);
    }

    current_terrain.c = fgetc(tdata);

    for (x = minx; x <= maxx; x++)
        current_terrain.data[x] = fgetc(tdata);

    fclose(tdata);

    return (0);
}


void
drawterrain() {
    int x, y;
    char c = current_terrain.c;

    for (x = minx; x <= maxx; x++)
        for (y = maxy; y > (maxy - current_terrain.data[x]); y--)
            putpixel(x, y, c, virt);
}

#endif
