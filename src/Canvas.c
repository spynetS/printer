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
    if(strlen(canvas->bgPixel.ch) > 1)
        width = size.ws_col/2;
    else
        width = size.ws_col;
    int height = size.ws_row;

    canvas->width = width;
    canvas->height = height;
    initPixels(canvas);
   

}

void initPixels(Canvas *canvas){
    if(canvas->pixels != NULL)
        free(canvas->pixels);
    int width = canvas->width;
    int height = canvas->height;
    canvas->pixels = (Pixel*)malloc(sizeof(Pixel)*width*height);

    for(int i = 0; i < canvas->width*height; i ++){
        canvas->pixels[i].ch = canvas->bgPixel.ch;
        canvas->pixels[i].color = canvas->bgPixel.color;
        canvas->pixels[i].bgcolor = canvas->bgPixel.color;
    }

    if(canvas->prevPixels != NULL)
        free(canvas->prevPixels);
    canvas->prevPixels = (Pixel*)malloc(sizeof(Pixel)*width*height);

    for(int i = 0; i < width*height; i ++){
        canvas->prevPixels[i].ch = "";
        canvas->prevPixels[i].color = "";
        canvas->prevPixels[i].bgcolor = "";
    }
}

Canvas *newCanvas(int width, int height, char* bgCh, char* color, char* bgcolor){
    disableEcho(); //dont display user input
    Canvas *canvas = malloc(sizeof(Canvas));
    canvas->bgPixel.ch = bgCh;
    canvas->bgPixel.color = color;
    canvas->bgPixel.bgcolor = bgcolor;
    canvas->width = width;
    canvas->height = height;

    initPixels(canvas);

    //printf("\033[?25h");
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
    free(canvas->pixels);
    free(canvas->prevPixels);
    free(canvas);
}

void draw(Canvas *canvas){
    
    if(canvas->prevPixels != NULL){
        int i = 0;
        for(int y = 0; y < canvas->height;y++){
            for(int x = 0; x < canvas->width;x++){
                Pixel p = canvas->pixels[i];
                if(strcmp(canvas->pixels[i].ch, canvas->prevPixels[i].ch) != 0){
                    char *print = malloc(sizeof(char*));

                    sprintf(print, "%s%s%s%s%s",p.color,p.bgcolor, p.ch,NOCURSOR,RESET);
                    setCharAt(x,y,print);

                    free(print);

                    fflush(stdout); 
                    setCursorPosition(canvas->width, canvas->height);
                    canvas->prevPixels[i] = canvas->pixels[i];
                }
                i++;
            }
            // printf("\n");
        }
    }
      


    // printf("%s",canvas->render);
    // int x = 0;
    // for(int i = 0; i < canvas->width*canvas->height; i++){
    //     Pixel pixel = canvas->pixels[i];
    //
    //     if(strlen(canvas->bgCh) > 1 && strlen(pixel.ch) < 2)
    //         printf("%s%s%s ",pixel.color,pixel.bgcolor,pixel.ch);
    //     else
    //         printf("%s%s%s",pixel.color,pixel.bgcolor,pixel.ch);
    //
    //     printf("%s",RESET);
    //     // if x == width -1 we start on the next row
    //     if(x == canvas->width-1){
    //         printf("\n");
    //         x=-1;
    //     }
    //     x++;
    // }
    // printf("\033[?25l");
}
void setCursorPosition(int x, int y) {
    printf("\033[%d;%dH", y+1, x+1);
}

void setCharAt(int x, int y, char *c) {
    setCursorPosition(x, y);
    printf("%s",c);
}
void setRender(Canvas *canvas){

    char* render = malloc(sizeof(char*)*canvas->height*canvas->width*3);
    
    int x = 0;
    for(int i = 0; i < canvas->width*canvas->height; i++){
        Pixel pixel = canvas->pixels[i];

        if(strlen(canvas->bgPixel.ch) > 1 && strlen(pixel.ch) < 2)
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

    if(canvas->render != NULL){
        printf("check");
        int i = 0;
        for(int x = 0; x < canvas->width;x++){
            for(int y = 0; y < canvas->height;y++){
                printf("%c : %c",canvas->render[i], render[i]);
                if(canvas->render[i] != render[i]){
                    char str[2];
                    str[0] = render[i];
                    str[1] = '\0';
                    setCharAt(x, y, str);
                }
                i++;
            }
        }
    }
    setCharAt(canvas->width, canvas->height, "");
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
            canvas->pixels[index].ch = canvas->bgPixel.ch;
            canvas->pixels[index].color = canvas->bgPixel.color;
            canvas->pixels[index].bgcolor = canvas->bgPixel.bgcolor;
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
