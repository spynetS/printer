#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Canvas.h"

int w = 10;
int h = 10;

int pos[100*100];
char **screen;


int getIndexFromPosition(int _x, int _y){
   int x = 0;
   int y = 0;
   for(int i = 0; i < w*h; i++){
      if(x == _x && y == _y){
         return i;
      } 
      if(x == w-1){
         x = -1;
         y++;
      }
      x++;
   }
   return 0;
}
void setCursorPosition(int x, int y);

void setCharAt(int x, int y, char *c);

void clearScreen(){
   int index = 0;
   for(int y = 0;y < h; y++){
      for(int x = 0;x < w; x++){
         if(pos[index] == 1){
            setCharAt(x, y, "#");
         }
      }
   }
}

void printBg(){
   for(int y = 0; y < h; y++){
      for(int x = 0; x < w; x++){
         setCharAt(x, y, "#");
      }
   }

}


int main() {
   system("clear");
   Canvas *canvas = newCanvas(10,10,"$","");

   setFullScreen(canvas) ;

   int x = 0;

   while(1){

      setPixel(canvas,x-1,4,"$",RED,"");
      setPixel(canvas,x,4,"*",RED,"");
      draw(canvas);

      msleep(100);
      x++;
   }
   

   return 0;
}
