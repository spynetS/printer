#include <stdlib.h>
#include <stdio.h>
#include "../src/printer.h"


int main(){


	Canvas* canvas = new_canvas(termWidth()-1,termHeight()-1);
	
	for(int y = 0; y < termHeight(); y ++) {
			for(int x = 0; x < termWidth(); x ++) {
				set_pixel(canvas, x,y,x+10,y+10,x*y);
			}
	}
	draw(canvas);
	msleep(1000);
	for(int y = 0; y < termHeight()/2; y ++) {
		for(int x = 0; x < termWidth()/2; x ++) {
			set_pixel(canvas, x,y,x+10,y+10,x*y);
		}
	}
	draw(canvas);

	
	return 0;
}
