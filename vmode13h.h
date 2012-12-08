#ifndef _VMODE13h_H
#define _VMODE13h_H

extern void setmode(int mode);
extern void wtsync(void);
extern void cleardevice(int far *dest);
extern void swap(int far *src, int far *dest);
extern void putpixel(int x, int y, char color, int far *dest);
extern char getpixel(int x, int y, int far *dest);
extern int far *screenadr(void);
extern int far *vmemalloc(unsigned int);
extern int vmemfree(int far *bytes);


int initgraph();
void closegraph();

int minx = 0, maxx = 319;
int miny = 0, maxy = 199;
int far *screen;
int far *virt;


int
initgraph(void) {
    screen = screenadr();
    virt = vmemalloc(0xFA00);

    if (virt != 0) {
        cleardevice(virt);
        setmode(0x0013);
        return (0);
    } else {
        return (1);
    };
};


void
closegraph(void) {
    vmemfree(virt);
    setmode(0x0003);
};

#endif
