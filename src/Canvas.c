#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Canvas.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

void setFullScreen(Canvas* canvas){
    struct winsize size;

    // Use the ioctl system call to get the terminal size
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
    }

    int width;
    if(strlen(canvas->bgCh) > 1)
        width = size.ws_col/2;
    else
        width = size.ws_col;
    int height = size.ws_row;

    canvas->width = width;
    canvas->height = height;

    free(canvas->pixels);
    canvas->pixels = (Pixel*)malloc(sizeof(Pixel)*width*height);

    for(int i = 0; i < width*height; i ++){
        canvas->pixels[i].ch = canvas->bgCh;
        canvas->pixels[i].color = canvas->color;
        canvas->pixels[i].bgcolor = canvas->color;
    }

}

Canvas *newCanvas(int width, int height, char* bgCh, char* color){
    Canvas *canvas = malloc(sizeof(Canvas));
    canvas->bgCh = bgCh;
    canvas->color = color;
    canvas->width = width;
    canvas->height = height;

    canvas->pixels = (Pixel*)malloc(sizeof(Pixel)*width*height);
    for(int i = 0; i < width*height; i ++){
        canvas->pixels[i].ch = bgCh;
        canvas->pixels[i].color = color;
        canvas->pixels[i].bgcolor = color;
    }
    printf("\033[?25h");
    return canvas;
}
Pixel *newPixel(int x, int y, char* ch, char* color,char* bgcolor){
    Pixel *pixel = (Pixel*)malloc(sizeof(Pixel));
    pixel->x = x;
    pixel->y = y;
    pixel->ch = ch;
    pixel->color = color;
    pixel->bgcolor = bgcolor;

    return pixel;
}

void freeStrings(Canvas *canvas){
    for(int i = 0 ; i < canvas->numStrings;i++){
        free(canvas->strings[i]);
    }
    canvas->numStrings = 0;
}

void freeCanvas(Canvas *canvas){
    printf("\033[?25h");
    freeStrings(canvas);
    free(canvas->strings);
    free(canvas);
}

void draw(Canvas *canvas){
    printf("%s",canvas->render);
}

void setRender(Canvas *canvas){

    char* render = malloc(sizeof(char*)*canvas->height*canvas->width*3);
    
    int x = 0;
    for(int i = 0; i < canvas->width*canvas->height; i++){
        Pixel pixel = canvas->pixels[i];

        if(strlen(canvas->bgCh) > 1 && strlen(pixel.ch) < 2)
            sprintf(render,"%s%s%s%s ",render,pixel.color,pixel.bgcolor,pixel.ch);
        else
            sprintf(render,"%s%s%s%s",render,pixel.color,pixel.bgcolor,pixel.ch);

        sprintf(render,"%s%s",render,RESET);
        // if x == width -1 we start on the next row
        if(x == canvas->width-1){
            sprintf(render,"%s\n",render);
            x=-1;
        }
        x++;
    }
    sprintf(render,"%s\033[?25l",render);
    canvas->render = render;

}

void setPixel(Canvas *canvas, int _x, int _y, char* ch, char* color, char* bgcolor){
    int index = 0;
    for(int y = 0; y < canvas->height; y++){
        for(int x = 0; x < canvas->width; x++){
            if(_x == x && _y == y){
                canvas->pixels[index].ch = ch;
                canvas->pixels[index].color = color;
                canvas->pixels[index].bgcolor = bgcolor;
            }
            index++;
        }
    }
}

Pixel *getPixel(Canvas *canvas, int _x, int _y){
    int index = 0;
    for(int y = 0; y < canvas->height; y++){
        for(int x = 0; x < canvas->width; x++){
            if(_x == x && _y == y){
                return &canvas->pixels[index];
            }
            index++;
        }
    }
    return NULL;
}


void setBgOfPixel(Canvas *canvas, int x, int y, char* bgcolor){
    getPixel(canvas, x, y);
}

void setPixelWithPixel(Canvas *canvas, Pixel *pixel){
    setPixel(canvas, pixel->x, pixel->y, pixel->ch, pixel->color, pixel->bgcolor);
}



void clearPixels(Canvas *canvas){
    //free the strings saved 
    freeStrings(canvas);

    int index = 0;
    for(int y = 0; y < canvas->height; y++){
        for(int x = 0; x < canvas->width; x++){
            canvas->pixels[index].ch = canvas->bgCh;
            canvas->pixels[index].color = canvas->color;
            index++;
        }
    }
}

void addString(Canvas *canvas, char *newStr){
    canvas->strings = (char**)realloc(canvas->strings, (canvas->numStrings+1)*sizeof(char*));
    (canvas->strings)[canvas->numStrings] = newStr;
    canvas->numStrings++;
}

void setText(Canvas *canvas, int _x, int _y, char* text, char* color, char* bgcolor){
    int len = strlen(text);
    for(int i = 0; i < len; i++){
        char *newStr = malloc(sizeof(char)*2);
        newStr[0] = text[i];
        newStr[1] = '\0';
        addString(canvas, newStr);
        
        setPixel(canvas, _x+i, _y, newStr, color, bgcolor);
    }
}
