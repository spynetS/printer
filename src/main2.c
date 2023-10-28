#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Canvas.h"

int main() {
   system("clear");
   Canvas *canvas = newCanvas(10,10,"##",RED,BG_BLUE);
   Canvas *canvas2 = newCanvas(10,10,"##",BLACK,BG_BLUE);
   canvas->y = 10;
   canvas->x = 10;

   while(1){
      draw(canvas); 
      clearPixels(canvas);
      setPixel(canvas,5,5,"@",WHITE,"" );
      draw(canvas2); 
      msleep(10);
   }
   

   return 0;
}
