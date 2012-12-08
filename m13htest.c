#include <stdio.h>
#include "vmode13h.h"

main()
{
    screen=screenadr();
    virt=vmemalloc(0xFA00);
    printf("Screen address: 0x0%8X \n",&screen);
    printf("Virutal screen address: 0x0%8X \n",&virt);
    vmemfree(virt);
};
