#include "./printer.h"
#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>



void set_char_at(int x, int y, char *c) {
	printf("\033[%d;%dH", y+1, x+1);
	printf("%s",c);
}

Canvas* new_canvas(int w, int h) {
	Canvas* canvas = malloc(sizeof(Canvas));
	canvas->w = w;
	canvas->h = h;

	canvas->buffer1 = malloc(sizeof(char*) * w * h);
	for(int i = 0; i < w * h; i ++) {
		canvas->buffer1[i] = "#";
	}

	return canvas;
}


void draw (Canvas* canvas) {
	for(int y = 0; y < canvas->h-1; y ++) {
		for(int x = 0; x < canvas->w-1; x ++) {
			int index = y * canvas->w + x;

			char* value = canvas->buffer1[index];
			if(value != NULL)
				set_char_at(x,y,value);
		}
	}
}


void set_pixel(Canvas* canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	if (x < 0 || x >= canvas->w || y < 0 || y >= canvas->h)
		return;

	int index = y * canvas->w + x;
	
	char* value = (char*) malloc(64);
	snprintf(value, 64, "\033[48;2;%d;%d;%dm ", r, g, b);
	canvas->buffer1[index] = value;
}

struct winsize win;
unsigned int termWidth(){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    return (win.ws_col);
}
unsigned int termHeight(){
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    return (win.ws_row);
}
