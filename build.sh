gcc -o ./build/Canvas.o -c ./src/Canvas.c
gcc -o ./build/msc.o -c ./src/msc.c
cd build
ar rcs libprinter.a Canvas.o msc.o
cd ..
gcc -shared -fPIC -o ./build/libprinter.so ./src/Canvas.c ./src/msc.c
