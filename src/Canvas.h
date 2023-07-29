
/**
    (Alfred Roos 2023-07-29)
    USE AS IS
    This library makes printing to the termninal alot easier.
    Instead of fomrating your prints yourself with a lot of for
    loops and such with this library you could just set the 'pixels'
    of your canvas to whatever you want.
    
    example:
    //creating a new canvas 20 width and 20 height
    canvas *canvas = newcanvas(20,20,'.',black);
    //set pixel at 10,10 to @ with color green
    setpixel(canvas, 10,10,'@', green);
    // draw the canvas
    draw(canvas);
    //dont forget to free the canvas with the freecanvas function
    // it frees everything the canvas has allocated
    freecanvas(canvas);

*/



#define BLACK  "\033[0;30m"
#define RED    "\033[0;31m"
#define GREEN  "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE   "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN   "\033[0;36m" 
#define WHITE  "\033[0;37m"


/** a struct to hold data a pixel needs */
typedef struct pixel
{
    char* ch;
    int x;
    int y;
    char* color;

}Pixel;


/** 
The canvas to set pixels to print to stdout 
usage:

    //creating a new canvas 20 width and 20 height
    canvas *canvas = newcanvas(20,20,'.',black);
    //set pixel at 10,10 to @ with color green
    setpixel(canvas, 10,10,'@', green);
    // draw the canvas
    draw(canvas);
    //dont forget to free the canvas with the freecanvas function
    // it frees everything the canvas has allocated
    freecanvas(canvas);

prints:
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . @ . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 
    . . . . . . . . . . . . . . . . . . . . 

*/
typedef struct canvas
{
    int width;
    int height;
    char* bgCh;
    char* color;
    Pixel *pixels;
    char** strings;
    int numStrings;

}Canvas;

/**  */

//canvas.c
/** Sets all pixelts to default pixels (clears all set) */
void clearPixels(Canvas *canvas);
/** sets the pixel at x,y with the data */
void setPixel(Canvas *canvas, int _x, int _y, char* ch, char* color);
/** set the pixel with the pixel arg */
void setPixelWithPixel(Canvas *canvas, Pixel pixel);
/** Sets the text at begining of x and at row y */
void setText(Canvas *canvas, int _x, int _y, char* text, char* color);
/** Internal function. Adds string to a list so we can free it later */
void addString(Canvas*, char *newStr);
/** prints all the pixels set in the canvas (prints with a space after to make it appear square)*/
void draw(Canvas *canvas);
/** prints all the pixels */
void drawMono(Canvas *canvas);
/** frees the canvas */
void freeCanvas(Canvas *canvas);
/** returns a new pixel with the data */
Pixel *newPixel(int x, int y, char* ch, char* color);
/** returns new canvas with the data */
Canvas *newCanvas(int width, int height, char* bgCh, char* color);

//mcs.c
int kbhit(void); //returns 1 if key was pressed
char getKeyPressed(); // returns char if it was pressed otherwise [
int msleep(long msec);