#include <stdio.h>
#include "vmode13h.h"

main() {
    screen = screenadr();
    virt = vmemalloc(0xFA00);
    printf("Screen address: %08lx\n", screen);
    printf("Virutal screen address: %08lx\n", virt);
    vmemfree(virt);
    return 0;
};
