.PHONY: all debug clean

all: asciivn asciibuffer.o asciibufferaa.o

main.o: main.c asciibufferaa.o
	gcc -c main.c -o main.o
asciibuffer.o: asciibuffer.c
	gcc -c asciibuffer.c -o asciibuffer.o
asciibufferaa.o: asciibufferaa.c
	gcc -c asciibufferaa.c -o asciibufferaa.o
asciibufferfill.o: asciibufferfill.c
	gcc -c asciibufferfill.c -o asciibufferfill.o
testimage.o: testimage.c
	gcc -c testimage.c -o testimage.o

asciivn: main.o asciibuffer.o asciibufferfill.o testimage.o
	gcc -laa main.o asciibuffer.o asciibufferfill.o testimage.o -o asciivn

clean:
	rm *.o

Debug: all
