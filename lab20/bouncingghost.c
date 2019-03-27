#include "lib.h"
#include "ghost.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;
void setRowBlank(int row, int col);
void setColBlank(int row, int col);

int main(void) {

    REG_DISPCNT = MODE3 | BG2_ENABLE;

    int row = 0;
    int col = 0;

    //loop infinitely
    while(1) {
        drawGhost(row, col, GHOST_WIDTH, GHOST_HEIGHT, ghost);
        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            setColBlank(row, col);
            col++; 
        }
        if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            col--;
        }
        if (KEY_DOWN_NOW(BUTTON_UP)) {
            setRowBlank(row + GHOST_HEIGHT - 1, col);
            row--;
        }
        if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            setRowBlank(row, col);
            row++; 
        }
        // Don't worry about this too much yet
        waitForVblank();

        

        //When ghost moves, it leaves a residue behind! There are four scenarios of movement to clean up behind the ghost

        //TODO: Scenario 1: ghost moves up (ie row--)
        

        //TODO: Scenario 2: ghost moves down (ie row++)
        

        //TODO: Scenario 3: ghost moves left (ie col--)
        

        //TODO: Scenario 4: ghost moves right (ie col++)
        


    }

}

void setRowBlank(int row, int col) {
    for(int i = col; i < col + GHOST_WIDTH; i++) {
        setPixel(row, i, BLACK);
    }
}

void setColBlank(int row, int col) {
    for(int i = row; i < row + GHOST_HEIGHT; i++) {
        setPixel(i, col, BLACK);
    }
}

//DO NOT EDIT ANY OF THESE FUNCTIONS
void setPixel(int row, int col, u16 color)
{ 
    videoBuffer[row*WIDTH + col] = color;
}

void drawRectangle(int row, int col, int width, int height, u16 color) {
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            setPixel(row + x, col + y, color);	
        }
    }
}

void waitForVblank(void) {
    while (*SCANLINECOUNTER > 160);
    while (*SCANLINECOUNTER < 160);
}

//Do not worry about what DMA is - we will be learning this soon! 
void drawGhost(int r, int c, int width, int height, const unsigned short *image) {
    for (int x = 0; x < height; x++) {
        DMA[3].src = image + OFFSET(x,0,width);
        DMA[3].dst = videoBuffer + OFFSET(x+r, c, 240);
        DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
    }
}
