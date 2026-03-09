#pragma once
#include <stdint.h>

#define RESET "\x1b[0m"
#define BG_RESET "\x1b[10m"

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"


typedef struct {
	char** buffer1;
	char** buffer2;
	int w, h;
	int x, y;
	char* bg;
} Canvas;

Canvas* new_canvas(int w, int h);

void set_pixel (Canvas* canvas, int x, int y, uint8_t r, uint8_t g, uint8_t b);
void set_char_fg (int x, int y, const uint8_t* value, uint8_t r, uint8_t g, uint8_t b);
void set_char_bg (int x, int y, const uint8_t* value, uint8_t r, uint8_t g, uint8_t b);
void set_char (int x, int y, const uint8_t* value, uint8_t fr, uint8_t fg, uint8_t fb, uint8_t br, uint8_t bg, uint8_t bb);
void draw (Canvas* canvas);

int msleep(long msec);
// Function to disable terminal echoing
void disableEcho();

// Function to enable terminal echoing
void enableEcho();
int kbhit(void);

unsigned int termWidth();
unsigned int termHeight();
