#include <stdlib.h>
#include <stdio.h>
#include "../src/printer.h"


int main(){
    Canvas *canvas = newCanvas(10,10,"  ",WHITE,BG_BLACK);


    setPixel(canvas,0,0,"# ",WHITE,BG_BLACK);
    setPixel(canvas,0,9,"# ",WHITE,BG_BLACK);
    setPixel(canvas,9,0," #",WHITE,BG_BLACK);
    setPixel(canvas,9,9," #",WHITE,BG_BLACK);

    setBorder(canvas,0);
    draw(canvas);


    return 0;
}
