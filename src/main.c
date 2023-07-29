#include <stdlib.h>
#include <stdio.h>
#include "Canvas.h"

typedef struct snake{

    Pixel *pixel;
    struct snake *next;

}Snake;

Snake *newSnake(int x, int y){
    Snake *snake = (Snake*)malloc(sizeof(Snake));
    snake->pixel = newPixel(x,y,"#",GREEN);
    
    return snake;
}

void addSnake(Snake *head, int x, int y){
    Snake *prev = head;
    while(prev->next != NULL){
        prev = prev->next;
    }
    prev->next = newSnake(x,y);
}

void removeSnake(Snake *head){
    Snake* old = head->next;
    head->next = old->next;
    free(old->pixel);
    free(old);
}

Snake *getLastSnake(Snake *head){
    Snake *prev = head->next;
    while(prev->next != NULL){
        prev = prev->next;
    }
    return prev;
}

void setSnake(Canvas*canvas,Snake *head){
    Snake *prev = head->next;
    while(prev != NULL){
        setPixelWithPixel(canvas, *prev->pixel);
        prev = prev->next;
    }
}

void freeSnake(Snake *head){
    while(head->next != NULL){
        removeSnake(head);
    }
}
void checkSnakeDeath(Snake *head){
    Snake *prev = head->next;
    Snake *last = getLastSnake(head);

    while(prev != NULL){
        if(prev != last){
            if(prev->pixel->x == last->pixel->x &&
                prev->pixel->y == last->pixel->y){
                printf("\nGG\n"); 
                exit(0);
            }
        }
        prev = prev->next;
    }

}

int main(){
    Snake *head = newSnake(10,10);
    addSnake(head, 1,10);
    addSnake(head, 2,10);
    addSnake(head, 3,10);


    Canvas *canvas = newCanvas(20,20,".",BLUE);
    

    Pixel *apple = newPixel(10, 10, "@", RED);
    
    int x = 1;
    int y = 0;

    while(1){
        system("clear");
        
        clearPixels(canvas);
        setText(canvas, 20/2-2, 0, "CNAKE", WHITE);
        setPixelWithPixel(canvas, *apple);
        setSnake(canvas,head);

        char c = getKeyPressed();
        if(c == 'w' && y != 1) {
            x = 0;
            y = -1;
        }
        if(c == 's' && y != -1) {
            x = 0;
            y = 1;
        }
        if(c == 'a' && x != 1) {
            x = -1;
            y = 0;
        }
        if(c == 'd' && x != -1) {
            x = 1;
            y = 0;
        }

        addSnake(head, getLastSnake(head)->pixel->x+x,getLastSnake(head)->pixel->y+y);
        removeSnake(head);

        checkSnakeDeath(head);


        draw(canvas);
        
        Snake *top = getLastSnake(head);
        if(top->pixel->x == apple->x && top->pixel->y == apple->y){
            addSnake(head, top->pixel->x+x, top->pixel->y+y);
            apple->x = (rand() % 20);
            apple->y = (rand() % 20);
        }


        msleep(100);
    }
    freeSnake(head);
    free(apple);
    freeCanvas(canvas);
    return 0;
}
