#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Canvas.h"

int main() {
   system("clear");
   Canvas *canvas = newCanvas(10,10,"  ",RED,BG_BLUE);
   Canvas *canvas2 = newCanvas(10,10,"  ",BLACK,BG_BLUE);
   canvas->y = 13;
   canvas->x = 13;

   while(1){
      setText(canvas,0,0,"tests",WHITE,BG_BLACK);
      draw(canvas);

      clearPixels(canvas);


      setPixel(canvas2,5,5,"@",WHITE,"" );
      draw(canvas2);
      setBorder(canvas2,1);
      msleep(10);
   }
   

   return 0;
}
