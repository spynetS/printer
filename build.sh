gcc -o ./build/Canvas.o -c ./src/Canvas.c
gcc -o ./build/msc.o -c ./src/msc.c
cd build
ar rcs libcanvas.a Canvas.o msc.o
