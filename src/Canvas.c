#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Canvas.h"


Canvas *newCanvas(int width, int height, char* bgCh, char* color){
    Canvas *canvas = malloc(sizeof(Canvas));
    canvas->bgCh = bgCh;
    canvas->color = color;
    canvas->pixels = (Pixel*)malloc(sizeof(Pixel)*width*height);
    canvas->width = width;
    canvas->height = height;

    for(int i = 0; i < width*height; i ++){
        canvas->pixels[i].ch = bgCh;
        canvas->pixels[i].color = color;
        canvas->pixels[i].bgcolor = color;
    }
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
    freeStrings(canvas);
    free(canvas->strings);
    free(canvas);
}

void draw(Canvas *canvas){
    // to keep track in what x coord we are priting
    int x = 0;
    for(int i = 0; i < canvas->width*canvas->height; i++){
        Pixel pixel = canvas->pixels[i];
        // if the pixel has less then 2 chars we dont print with a space
        if(strlen(pixel.ch) < 2)
            printf("%s%s%s ",pixel.bgcolor,pixel.color,pixel.ch);
        else
            printf("%s%s%s",pixel.color,pixel.bgcolor,pixel.ch);

        printf(RESET);
        // if x == width -1 we start on the next row
        if(x == canvas->width-1){
            printf("\n");
            x=-1;
        }
        x++;
    }
}
void drawMono(Canvas *canvas){
    int w = 20;
    int h = 20;
    for(int i = 0; i < canvas->width*canvas->height; i++){
        if(i%canvas->height==0) printf("\n");
        printf("%s%s",canvas->pixels[i].color,canvas->pixels[i].ch);
    }
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
