#ifndef _VMODE13h_H
#define _VMODE13h_H

void setmode(int);
void wtsync(void);
void cleardevice(int far *);
void swap(int far *, int far *);
void putpixel(int, int, char, int far *);
char getpixel(int, int, int far *);
int far *screenadr(void);
int far *vmemalloc(unsigned int);
int vmemfree(int far *);

extern int minx;
extern int maxx;
extern int miny;
extern int maxy;
extern int far *screen;
extern int far *virt;

#endif
