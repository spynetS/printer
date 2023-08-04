#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Canvas.h"
typedef struct{
   int x;
   int y;
}Point;

int main() {
   system("clear");
   Canvas *canvas = newCanvas(10,10,"##",BLACK,BG_BLACK);
   //setFullScreen(canvas);
   Pixel *apple = newPixel(5,5,"🍎","",BG_BLACK);


   Point pos;
   pos.x = 0;
   pos.y = 4;
   
   Point direction;
   direction.x = 1;
   direction.y = 0;

   clearPixels(canvas);

   while(1){
      // clearPixels(canvas);

      char c = getKeyPressed();
      if(c == 'w'){
         direction.y = -1;
         direction.x = 0;
      }
      if(c == 's'){
         direction.y = 1;
         direction.x = 0;
      }
      if(c == 'a'){
         direction.y = 0;
         direction.x = -1;
      }
      if(c == 'd'){
         direction.y = 0;
         direction.x = 1;
      }
      setPixelWithPixel(canvas, apple);

      // setPixel(canvas,5,5,"🍎","",BG_BLACK);
      setPixel(canvas,pos.x,pos.y,"🐍",BLUE,BG_BLACK);
      setPixel(canvas,pos.x+direction.x,pos.y+direction.y,"🤯",BLUE,BG_BLACK);
      draw(canvas);

      msleep(500);
      pos.x+=direction.x;
      pos.y+=direction.y;

   }
   

   return 0;
}
