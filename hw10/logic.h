#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"

#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"

typedef enum { NW, NE, SW, SE } Direction;




typedef struct {
    int x;
    int y;
} Player;

typedef struct {
    int x;
    int y;
    Direction direction;
} Rocket;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;

    Rocket rocket;
    Player player;
    char lives;

} AppState;

/*
* TA-TODO: Add any additional structs that you need for your app.
*
* For example, for a Snake game, one could be:
*
* typedef struct {
*   int heading;
*   int length;
*   int x;
*   int y;
* } Snake;
*
*/




// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
