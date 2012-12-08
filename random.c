#include <vmode13h.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int
main(int argc, char **argv) {
    int x, y, i;
    char i;

    randomize();
    setmode(0x0013);

    for(i = 0; i < 32000; i ++) {
        x = random(320);
        y = random(200);
        c = random(256);
        putpixel(x,y,c);
    };

    c = getch();

    for(i = 0; i < 256; i ++) {
        for(y = 0; y < 200; y ++) {
            x = i;
            c = i;
            putpixel(x,y,c);
        };
    };

    c = getch();
    setmode(3);
}
