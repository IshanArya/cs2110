#include "logic.h"


void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.

    appState->gameOver = 0;
    appState->lives = '9';
    appState->player.x = 91;
    appState->player.y = 53;
    appState->rocket.direction = SE;
    appState->rocket.x = 130;
    appState->rocket.y = 40;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

static int collision(AppState *appState) {
    Player player = appState->player;
    Rocket rocket = appState->rocket;
    return ((player.x < rocket.x + ROCKET_WIDTH &&
            rocket.x < player.x + PLAYER_WIDTH) &&
            (player.y < rocket.y + ROCKET_HEIGHT &&
            rocket.y < player.y + PLAYER_HEIGHT));
}

    // This function processes your current app state and returns the new (i.e.
    // next) state of your application.
    AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */
    UNUSED(keysPressedBefore);
    AppState nextAppState = *currentAppState;
    int x = currentAppState->player.x;
    int y = currentAppState->player.y;
    Rocket rocket = currentAppState->rocket;
    if (KEYS_DOWN(BUTTON_RIGHT, keysPressedNow)) {
        if(x < RIGHT_BOUND) {
            x++;
        }
    }
    if (KEYS_DOWN(BUTTON_LEFT, keysPressedNow)) {
        if(x > LEFT_BOUND) {
            x--;
        }
    }
    if (KEYS_DOWN(BUTTON_UP, keysPressedNow)) {
        if(y > TOP_BOUND) {
            y--;
        }
    }
    if (KEYS_DOWN(BUTTON_DOWN, keysPressedNow)) {
        if(y < BOTTOM_BOUND) {
            y++;
        }
    }
    switch(rocket.direction) {
        case NW:
            rocket.x -= ROCKET_SPEED * randint(1, 5);
            rocket.y -= ROCKET_SPEED * randint(1, 5);
            break;
        case NE:
            rocket.x += ROCKET_SPEED * randint(1, 5);
            rocket.y -= ROCKET_SPEED * randint(1, 5);
            break;
        case SW:
            rocket.x -= ROCKET_SPEED * randint(1, 5);
            rocket.y += ROCKET_SPEED * randint(1, 5);
            break;
        case SE:
            rocket.x += ROCKET_SPEED * randint(1, 5);
            rocket.y += ROCKET_SPEED * randint(1, 5);
            break;
        default:
            break;
    }

    if(rocket.x <= LEFT_BOUND) {
        rocket.direction = NE;
    }
    if(rocket.y <= TOP_BOUND) {
        rocket.direction = SE;
    }
    if (rocket.x >= RIGHT_BOUND) {
        rocket.direction = SW;
    }
    if (rocket.y >= BOTTOM_BOUND) {
        rocket.direction = NW;
    }

    nextAppState.player.x = x;
    nextAppState.player.y = y;
    nextAppState.rocket = rocket;

    if(!collision(currentAppState) && collision(&nextAppState)) {
        nextAppState.lives--;
    }

    if(nextAppState.lives <= '0') {
        nextAppState.gameOver = 1;
    }


    return nextAppState;
}
