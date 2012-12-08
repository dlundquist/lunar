path %path%;d:\tc\bin;
d:\tc\bin\tcc -c test.c
d:\tc\bin\tasm /ml vmode13h.asm
d:\tc\bin\tcc -ms test.obj vmode13h.obj
pause
