#include <stdio.h>
#include "terrain.h"
#include "vmode13h.h"

struct terrain *
loadterrain(const char *filename) {
    int x;
    FILE *fd;
    static struct terrain terrain;

    if ((fd = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Cannot open data file: %s\n", filename);
        return NULL;
    }

    terrain.c = fgetc(fd);

    for (x = minx; x <= maxx; x++)
        terrain.data[x] = fgetc(fd);

    fclose(fd);

    return &terrain;
}

void
drawterrain(const struct terrain *terrain) {
    int x, y;
    char c = terrain->c;

    for (x = minx; x <= maxx; x++)
        for (y = maxy - terrain->data[x]; y <= maxy; y++)
            putpixel(x, y, c, virt);
}
