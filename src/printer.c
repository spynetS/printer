#include "./printer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./logger.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>



void set_char_at(int x, int y, char *c) {
	printf("\033[%d;%dH", y+1, x+1);
	printf("%s",c);
}

void free_canvas(Canvas* canvas) {
	close_logger(canvas->logger);
	
	free(canvas->pixels);
	free(canvas->prev_pixels);
	free(canvas);

}

Canvas* new_canvas(int w, int h) {
	Logger logger = {0};
	if(init_logger(&logger, "./log.txt") == 1) {
		exit(1);
	}

	Canvas* canvas = malloc(sizeof(Canvas));
	canvas->logger = &logger;
	
	canvas->w = w;
	canvas->h = h;

	canvas->bg = RESET" ";
	canvas->pixels = malloc(sizeof(Pixel) * w * h);
	canvas->prev_pixels = malloc(sizeof(Pixel) * w * h);
	for(int i = 0; i < canvas->w * canvas->h; i++){
		canvas->pixels[i].r = 0;
		canvas->pixels[i].g = 0;
		canvas->pixels[i].b = 0;
		canvas->prev_pixels[i].r = 1;
		canvas->prev_pixels[i].g = 1;
		canvas->prev_pixels[i].b = 1;
	}
	return canvas;
}


void draw (Canvas* canvas) {

	int skipped = 0;
	for(int y = 0; y < canvas->h; y ++) {
		for(int x = 0; x < canvas->w; x ++) {
			int index = y * canvas->w + x;
			// if back we draw transparent
			if (canvas->pixels[index].r != canvas->prev_pixels[index].r ||
					canvas->pixels[index].g != canvas->prev_pixels[index].b ||
					canvas->pixels[index].b != canvas->prev_pixels[index].g){
				if(canvas->pixels[index].r == 0 &&
					 canvas->pixels[index].g == 0 &&
					 canvas->pixels[index].b == 0){
					set_char_at(x, y, RESET" ");
					continue;
				}

				char* value = (char*) malloc(64);
				snprintf(value, 64, "\033[48;2;%d;%d;%dm ",
								 canvas->pixels[index].r,
								 canvas->pixels[index].g,
								 canvas->pixels[index].b);
				set_char_at(x, y, value);
				free(value);
			}
			else{
				skipped++;
			}
		}
	}
	
	/* char msg[255]; */
	/* sprintf(msg,"%d", skipped); */
	/* log_message(canvas->logger, msg); */
	
	if(canvas->prev_pixels != NULL)
		free(canvas->prev_pixels);
	canvas->prev_pixels = canvas->pixels;
	canvas->pixels = malloc(sizeof(Pixel) * canvas->w * canvas->h);
	for(int i = 0; i < canvas->w * canvas->h; i++){
		canvas->pixels[i].r = 0;
		canvas->pixels[i].g = 0;
		canvas->pixels[i].b = 0;
	}

}


void set_pixel(Canvas* canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	if (x < 0 || x >= canvas->w || y < 0 || y >= canvas->h)
		return;
	int index = y * canvas->w + x;

	canvas->pixels[index].r = r;
	canvas->pixels[index].g = g;
	canvas->pixels[index].b = b;

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

