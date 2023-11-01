gcc -o Canvas.o -c ./src/Canvas.c
gcc -o msc.o -c ./src/msc.c
ar rcs libcanvas.a Canvas.o msc.o
