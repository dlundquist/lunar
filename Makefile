all: lunar.exe random.exe m13htest.exe

lunar.obj: lunar.c
	bcc -c lunar.c

terrain.obj: terrain.c
	bcc -c terrain.c

m13htest.obj: m13htest.c
	bcc -c m13htest.c

random.obj: random.c
	bcc -c random.c

vmode13h.obj: vmode13h.asm
	tasm /x /ml vmode13h.asm

lunar.exe: lunar.obj terrain.obj vmode13h.obj
	bcc -ms lunar.obj terrain.obj vmode13h.obj

random.exe: random.obj vmode13h.obj
	bcc -ms random.obj vmode13h.obj

m13htest.exe: m13htest.obj vmode13h.obj
	bcc -ms m13htest.obj vmode13h.obj
