#include <stdlib.h>
#include <stdio.h>
#include "Canvas.h"



int main(){

    Canvas *canvas = newCanvas(20,20,".",BLACK);

    Pixel *player = newPixel(10,10,"██",GREEN);

    while(1){
        clearPixels(canvas);
        setText(canvas,4,1,"Hello Sweden",WHITE);
        setText(canvas,5,2,"Hello world",WHITE);
        setPixelWithPixel(canvas,*player);

        char c = getKeyPressed();
        if(c == 'w') {
            player->y --;
        }
        if(c == 's') {
            player->y ++;
        }
        if(c == 'a') {
            player->x --;
        }
        if(c == 'd') {
            player->x ++;
        }


        draw(canvas);
        puts("");
        msleep(10);
    }

    free(player);
    freeCanvas(canvas);

    return 0;
}
