#include <stdio.h>
#include <bios.h>
#include <conio.h>
#include "vmode13h.h"
#include "terrain.h"

int loadship();
void drawship(int, int);
void scankb();
void crash();
void land();

/* globals */
unsigned char ship[16][16];
int x, y, z;
int posx, posy;
int px, py;
int velx, vely;
char exitflag;
char crashflag;


int
main(int argc, char **argv) {
    char gravcount;

    if (loadterrain() != 0)
        return (1);

    if (loadship() != 0)
        return (1);

    initgraph();

    px = 160 * 16;
    py = 9 * 16;

    velx = 1;
    vely = 0;

    while (exitflag == 0) {
        /* physics */
        px += velx;
        py += vely;
        posx = px / 16;
        posy = py / 16;
        gravcount++;

        /* gravity */
        if (gravcount > 100) {
            gravcount = 0;
            vely++;
        }

        /* input */
        scankb();

        /* wrap around sides of screen */
        if (posx < minx + 9)
            px = (maxx - 9) * 16;

        if (posx > maxx - 9)
            px = (minx + 9) * 16;

        /* prevent leaving the top of the screen */
        if (posy < miny + 9) {
            py = (miny + 9) * 16;
            vely = 0;
        }

        /* terrain collision checking */
        if (posy > maxy - current_terrain.data[posx] - 7)
            crash();

        if (posy > maxy - current_terrain.data[posx] - 6) {
            for (x = -8; x <= 8; x++)
                if (posy != maxy - current_terrain.data[posx + x] - 9)
                    if (crashflag == 0)
                        land();
        }

        /* swap frame buffer */
        wtsync();
        swap(virt, screen);
        cleardevice(virt);

        /* graphics */
        drawship(posx, posy);
        drawterrain();
    }
    setmode(0x0003);

    return (0);
}

int
loadship() {
    FILE *sdata;

    if ((sdata = fopen("SHIP.DAT", "rb")) == NULL) {
        fprintf(stderr, "Cannot open data file: SHIP.DAT\n");
        return (1);
    }

    for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++)
            ship[x][y] = fgetc(sdata);

    fclose(sdata);

    return (0);
}

void
drawship(int x, int y) {
    int u, v;
    char c;

    x -= 8;
    y -= 8;

    for (u = 0; u < 16; u++)
        for (v = 0; v < 16; v++) {
            c = ship[u][v];

            /* transparency */
            if (c != 0)
                putpixel(u + x, v + y, c, virt);
        }
}

void
crash() {
    px = 160 * 16;
    py = 44 * 16;

    velx = 1;
    vely = 0;

    setmode(0x0003);

    printf("You crashed!!!");
    getch();

    setmode(0x0013);
}

void
land() {
    px = 160 * 16;
    py = 44 * 16;

    velx = 1;
    vely = 0;

    setmode(0x0003);

    printf("You landed!!!");
    getch();

    setmode(0x0013);
}

void
scankb() {
    char a, b;

    if (bioskey(1) == 0x00)
        return;

    a = getch();

    if (a == 0x00) {
        b = getch();

        if (b == 0x48) {
            vely--;
            return;
        }

        if (b == 0x50) {
            vely++;
            return;
        }

        if (b == 0x4b) {
            velx--;
            return;
        }

        if (b == 0x4d) {
            velx++;
            return;
        }

        if (b == 0x44) {
            exitflag = 1;
            return;
        }
    }

    if (a == 0x1b) {
        exitflag = 1;
        return;
    }
}
