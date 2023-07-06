/* input.c: handles input, such as reading the keyboard */

#include "common.h"
#include "input.h"

extern App app;
extern Touch touch;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool isMenuOn;
extern bool isScoreOn;
extern bool isKeyboardOn;

/* handles key down */
void doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
            app.keyboard[event->keysym.scancode] = 1;
    }
}

/* handles key down */
void doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 0;
    }
}

void doKeyboardDown(SDL_TouchFingerEvent* event)
{
    // Calculate the touch position
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;

    // Calculate the cell size
    int cellWidth = SCREEN_WIDTH / 15;
    int cellHeight = (SCREEN_HEIGHT / 2) / 8;

    // Calculate the touched cell index
    int cellX = touchX / cellWidth;
    int cellY = (touchY - (SCREEN_HEIGHT / 2)) / cellHeight;

    // Calculate the touched cell index in a 8x15 grid
    int cellIndex = cellY * 15 + cellX;

    if (isKeyboardOn) {
        switch (cellIndex) {
            // first row
            case 16: app.keyboard[SDL_SCANCODE_0] = 1; break;
            case 17: app.keyboard[SDL_SCANCODE_1] = 1; break;
            case 18: app.keyboard[SDL_SCANCODE_2] = 1; break;
            case 19: app.keyboard[SDL_SCANCODE_3] = 1; break;
            case 20: app.keyboard[SDL_SCANCODE_4] = 1; break;
            case 21: app.keyboard[SDL_SCANCODE_5] = 1; break;
            case 22: app.keyboard[SDL_SCANCODE_6] = 1; break;
            case 23: app.keyboard[SDL_SCANCODE_7] = 1; break;
            case 24: app.keyboard[SDL_SCANCODE_8] = 1; break;
            case 25: app.keyboard[SDL_SCANCODE_9] = 1; break;
            case 26: app.keyboard[SDL_SCANCODE_KP_COLON] = 1; break;
            case 27: app.keyboard[SDL_SCANCODE_SEMICOLON] = 1; break;
            case 28: app.keyboard[SDL_SCANCODE_EQUALS] = 1; break;
                // second row
            case 31: app.keyboard[SDL_SCANCODE_Q] = 1; break;
            case 32: app.keyboard[SDL_SCANCODE_W] = 1; break;
            case 33: app.keyboard[SDL_SCANCODE_E] = 1; break;
            case 34: app.keyboard[SDL_SCANCODE_R] = 1; break;
            case 35: app.keyboard[SDL_SCANCODE_T] = 1; break;
            case 36: app.keyboard[SDL_SCANCODE_Y] = 1; break;
            case 37: app.keyboard[SDL_SCANCODE_U] = 1; break;
            case 38: app.keyboard[SDL_SCANCODE_I] = 1; break;
            case 39: app.keyboard[SDL_SCANCODE_O] = 1; break;
            case 40: app.keyboard[SDL_SCANCODE_P] = 1; break;
            case 41: app.keyboard[SDL_SCANCODE_KP_LESS] = 1; break;
            case 42: app.keyboard[SDL_SCANCODE_KP_GREATER] = 1; break;
            case 43: app.keyboard[SDL_SCANCODE_KP_AT] = 1; break;
                // third row
            case 46: app.keyboard[SDL_SCANCODE_A] = 1; break;
            case 47: app.keyboard[SDL_SCANCODE_S] = 1; break;
            case 48: app.keyboard[SDL_SCANCODE_D] = 1; break;
            case 49: app.keyboard[SDL_SCANCODE_F] = 1; break;
            case 50: app.keyboard[SDL_SCANCODE_G] = 1; break;
            case 51: app.keyboard[SDL_SCANCODE_H] = 1; break;
            case 52: app.keyboard[SDL_SCANCODE_J] = 1; break;
            case 53: app.keyboard[SDL_SCANCODE_K] = 1; break;
            case 54: app.keyboard[SDL_SCANCODE_L] = 1; break;
                //case 55: game.keyboard[34] = 1; break; // double quote "
                /* RETURN */
            case 56:
            case 57:
            case 58:
            case 71:
            case 72:
            case 73:
            case 88:
            case 103: app.keyboard[SDL_SCANCODE_RETURN] = 1; break;
                // fourth row
            case 61: app.keyboard[SDL_SCANCODE_KP_EXCLAM] = 1; break;
            case 62: app.keyboard[SDL_SCANCODE_Z] = 1; break;
            case 63: app.keyboard[SDL_SCANCODE_X] = 1; break;
            case 64: app.keyboard[SDL_SCANCODE_C] = 1; break;
            case 65: app.keyboard[SDL_SCANCODE_V] = 1; break;
            case 66: app.keyboard[SDL_SCANCODE_B] = 1; break;
            case 67: app.keyboard[SDL_SCANCODE_N] = 1; break;
            case 68: app.keyboard[SDL_SCANCODE_M] = 1; break;
            case 69: app.keyboard[SDL_SCANCODE_MINUS] = 1; break;
            case 70: app.keyboard[SDL_SCANCODE_APOSTROPHE] = 1; break;

                // fifth row
                //case 76: game.keyboard[63] = 1; break; // question ?
            case 77: app.keyboard[SDL_SCANCODE_KP_HASH] = 1; break; // hash
                //case 78: game.keyboard[36] = 1; break; // dollar
            case 79: app.keyboard[SDL_SCANCODE_KP_PERCENT] = 1; break; // percent
            case 80: app.keyboard[SDL_SCANCODE_KP_AMPERSAND] = 1; break; // ampersand
            case 81: app.keyboard[SDL_SCANCODE_KP_LEFTPAREN] = 1; break; // (
            case 82: app.keyboard[SDL_SCANCODE_KP_RIGHTPAREN] = 1; break; // )
            case 83: app.keyboard[SDL_SCANCODE_KP_MULTIPLY] = 1; break; // *
            case 84: app.keyboard[SDL_SCANCODE_KP_PLUS] = 1; break; // +
            case 85: app.keyboard[SDL_SCANCODE_KP_PERIOD] = 1; break; // .
            case 86: app.keyboard[SDL_SCANCODE_KP_DIVIDE] = 1; break; // /
            case 87: app.keyboard[SDL_SCANCODE_KP_COMMA] = 1; break; // ,

                // sixth row
            case 91: app.keyboard[SDL_SCANCODE_BACKSPACE] = 1; break;
            case 92:
            case 93:
            case 94:
            case 95:
            case 96:
            case 97:
            case 98:
            case 99:
            case 100:
            case 101:
            case 102: app.keyboard[SDL_SCANCODE_SPACE] = 1; break;
        }
    }
}

void doKeyboardUp(SDL_TouchFingerEvent* event)
{
    // first row
    app.keyboard[SDL_SCANCODE_0] = 0;
    app.keyboard[SDL_SCANCODE_1] = 0;
    app.keyboard[SDL_SCANCODE_2] = 0;
    app.keyboard[SDL_SCANCODE_3] = 0;
    app.keyboard[SDL_SCANCODE_4] = 0;
    app.keyboard[SDL_SCANCODE_5] = 0;
    app.keyboard[SDL_SCANCODE_6] = 0;
    app.keyboard[SDL_SCANCODE_7] = 0;
    app.keyboard[SDL_SCANCODE_8] = 0;
    app.keyboard[SDL_SCANCODE_9] = 0;
    app.keyboard[SDL_SCANCODE_KP_COLON] = 0;
    app.keyboard[SDL_SCANCODE_SEMICOLON] = 0;
    app.keyboard[SDL_SCANCODE_EQUALS] = 0;
    // second row
    app.keyboard[SDL_SCANCODE_Q] = 0;
    app.keyboard[SDL_SCANCODE_W] = 0;
    app.keyboard[SDL_SCANCODE_E] = 0;
    app.keyboard[SDL_SCANCODE_R] = 0;
    app.keyboard[SDL_SCANCODE_T] = 0;
    app.keyboard[SDL_SCANCODE_Y] = 0;
    app.keyboard[SDL_SCANCODE_U] = 0;
    app.keyboard[SDL_SCANCODE_I] = 0;
    app.keyboard[SDL_SCANCODE_O] = 0;
    app.keyboard[SDL_SCANCODE_P] = 0;
    app.keyboard[SDL_SCANCODE_KP_LESS] = 0;
    app.keyboard[SDL_SCANCODE_KP_GREATER] = 0;
    app.keyboard[SDL_SCANCODE_KP_AT] = 0;
    // third row
    app.keyboard[SDL_SCANCODE_A] = 0;
    app.keyboard[SDL_SCANCODE_S] = 0;
    app.keyboard[SDL_SCANCODE_D] = 0;
    app.keyboard[SDL_SCANCODE_F] = 0;
    app.keyboard[SDL_SCANCODE_G] = 0;
    app.keyboard[SDL_SCANCODE_H] = 0;
    app.keyboard[SDL_SCANCODE_J] = 0;
    app.keyboard[SDL_SCANCODE_K] = 0;
    app.keyboard[SDL_SCANCODE_L] = 0;
    //game.keyboard[34] = 0;
    app.keyboard[SDL_SCANCODE_RETURN] = 0;
    // fourth row
    app.keyboard[SDL_SCANCODE_KP_EXCLAM] = 0;
    app.keyboard[SDL_SCANCODE_Z] = 0;
    app.keyboard[SDL_SCANCODE_X] = 0;
    app.keyboard[SDL_SCANCODE_C] = 0;
    app.keyboard[SDL_SCANCODE_V] = 0;
    app.keyboard[SDL_SCANCODE_B] = 0;
    app.keyboard[SDL_SCANCODE_N] = 0;
    app.keyboard[SDL_SCANCODE_M] = 0;
    app.keyboard[SDL_SCANCODE_MINUS] = 0;
    app.keyboard[SDL_SCANCODE_APOSTROPHE] = 0;
    // fifth row
    //game.keyboard[63] = 0;
    app.keyboard[SDL_SCANCODE_KP_HASH] = 0;
    //game.keyboard[36] = 0;
    app.keyboard[SDL_SCANCODE_KP_PERCENT] = 0;
    app.keyboard[SDL_SCANCODE_KP_AMPERSAND] = 0;
    app.keyboard[SDL_SCANCODE_KP_LEFTPAREN] = 0;
    app.keyboard[SDL_SCANCODE_KP_RIGHTPAREN] = 0;
    app.keyboard[SDL_SCANCODE_KP_MULTIPLY] = 0;
    app.keyboard[SDL_SCANCODE_KP_PLUS] = 0;
    app.keyboard[SDL_SCANCODE_KP_PERIOD] = 0;
    app.keyboard[SDL_SCANCODE_KP_DIVIDE] = 0;
    app.keyboard[SDL_SCANCODE_KP_COMMA] = 0;
    // sixth row
    app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
    app.keyboard[SDL_SCANCODE_SPACE] = 0;
}


/* handles fire and control touchsceen */
void doTouchDown(SDL_TouchFingerEvent* event)
{
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;

    // Calculate the thresholds for the cells
    int cellWidth = SCREEN_WIDTH / 6;
    int cellHeight = SCREEN_HEIGHT / 2;

    // Check touch position and set touch.up, touch.down, touch.left, touch.right, touch.fire accordingly
    if (touchX >= 5 * cellWidth && touchY >= cellHeight) {
        // Touched in cell 12 (bottom-right corner to fire)
        touch.up = 0;
        touch.down = 0;
        touch.left = 0;
        touch.right = 0;
        touch.fire = 1;
    } else if (touchX >= 0 && touchX < cellWidth && touchY >= cellHeight && touchY < 2 * cellHeight) {
        // Touched in cell 7 (control directions)
        int controlX = touchX;
        int controlY = touchY - cellHeight;

        int directionWidth = cellWidth / 3;
        int directionHeight = cellHeight / 3;

        if (controlX >= 0 && controlX < cellWidth && controlY >= 0 && controlY < cellHeight) {
            // Touched in control directions
            int directionX = controlX / directionWidth;
            int directionY = controlY / directionHeight;

            if (directionX == 0 && directionY == 0) {
                // Touched in top-left direction
                touch.up = 1;
                touch.down = 0;
                touch.left = 1;
                touch.right = 0;
                touch.fire = 0;
            } else if (directionX == 1 && directionY == 0) {
                // Touched in top direction
                touch.up = 1;
                touch.down = 0;
                touch.left = 0;
                touch.right = 0;
                touch.fire = 0;
            } else if (directionX == 2 && directionY == 0) {
                // Touched in top-right direction
                touch.up = 1;
                touch.down = 0;
                touch.left = 0;
                touch.right = 1;
                touch.fire = 0;
            } else if (directionX == 0 && directionY == 1) {
                // Touched in left direction
                touch.up = 0;
                touch.down = 0;
                touch.left = 1;
                touch.right = 0;
                touch.fire = 0;
            } else if (directionX == 1 && directionY == 1) {
                // Touched in center direction (no movement)
                touch.up = 0;
                touch.down = 0;
                touch.left = 0;
                touch.right = 0;
                touch.fire = 0;
            } else if (directionX == 2 && directionY == 1) {
                // Touched in right direction
                touch.up = 0;
                touch.down = 0;
                touch.left = 0;
                touch.right = 1;
                touch.fire = 0;
            } else if (directionX == 0 && directionY == 2) {
                // Touched in bottom-left direction
                touch.up = 0;
                touch.down = 1;
                touch.left = 1;
                touch.right = 0;
                touch.fire = 0;
            } else if (directionX == 1 && directionY == 2) {
                // Touched in bottom direction
                touch.up = 0;
                touch.down = 1;
                touch.left = 0;
                touch.right = 0;
                touch.fire = 0;
            } else if (directionX == 2 && directionY == 2) {
                // Touched in bottom-right direction
                touch.up = 0;
                touch.down = 1;
                touch.left = 0;
                touch.right = 1;
                touch.fire = 0;
            } else {
                // Touched outside the control directions
                touch.up = 0;
                touch.down = 0;
                touch.left = 0;
                touch.right = 0;
                touch.fire = 0;
            }
        } else {
            // Touched outside the control directions
            touch.up = 0;
            touch.down = 0;
            touch.left = 0;
            touch.right = 0;
            touch.fire = 0;
        }
    } else {
        // Touched outside the touchable cells
        touch.up = 0;
        touch.down = 0;
        touch.left = 0;
        touch.right = 0;
        touch.fire = 0;
    }
}

/* handles touch up */
void doTouchUp(SDL_TouchFingerEvent *event)
{
    // Reset app.up, app.down, app.left, app.right to 0
    touch.up = 0;
    touch.down = 0;
    touch.left = 0;
    touch.right = 0;
    touch.fire = 0;
}

void doTouchMenuDown(SDL_TouchFingerEvent* event)
{
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;

    // Calculate the thresholds for the cells
    int cellWidth = SCREEN_WIDTH / 3;
    int cellHeight = SCREEN_HEIGHT / 3;

    // Check touch position and set touch.score, touch.play, touch.lang, touch.quit accordingly
    if (touchX >= (SCREEN_WIDTH - SCREEN_WIDTH / 4) && touchY >= SCREEN_HEIGHT / 6 && touchY < (SCREEN_HEIGHT / 6) * 2) {
        // Touched the "SCORE" button
        touch.score = 1;
        touch.play = 0;
        touch.lang = 0;
        touch.quit = 0;
    } else if (touchX >= (SCREEN_WIDTH - SCREEN_WIDTH / 4) && touchY >= (SCREEN_HEIGHT / 2) && touchY < (SCREEN_HEIGHT / 2) + (SCREEN_HEIGHT / 6)) {
        // Touched the "PLAY" button
        touch.score = 0;
        touch.play = 1;
        touch.lang = 0;
        touch.quit = 0;
    } else if (touchX >= (SCREEN_WIDTH - SCREEN_WIDTH / 4) + (SCREEN_HEIGHT / 6) && touchY >= (SCREEN_HEIGHT - SCREEN_HEIGHT / 6)) {
        // Touched the "Q" button
        touch.score = 0;
        touch.play = 0;
        touch.lang = 0;
        touch.quit = 1;
    } else if (touchX >= (SCREEN_WIDTH - SCREEN_WIDTH / 4) - (SCREEN_HEIGHT / 6) && touchY >= (SCREEN_HEIGHT - SCREEN_HEIGHT / 6)) {
        // Touched the language button
        touch.score = 0;
        touch.play = 0;
        touch.lang = 1;
        touch.quit = 0;
    } else {
        // Touched outside the touchable areas
        touch.score = 0;
        touch.play = 0;
        touch.lang = 0;
        touch.quit = 0;
    }
}

void doTouchMenuUp(SDL_TouchFingerEvent* event)
{
    // reset
    touch.score = 0;
    touch.play = 0;
    touch.lang = 0;
    touch.quit = 0;
}

void doTouchScoreDown(SDL_TouchFingerEvent* event)
{
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;

    // Calculate the thresholds for the cells
    int cellWidth = SCREEN_WIDTH / 4;
    int cellHeight = SCREEN_HEIGHT / 5;

    // Check touch position and set touch.menu and touch.quit accordingly
    if (touchX >= (SCREEN_WIDTH - SCREEN_WIDTH / 4) && touchY >= SCREEN_HEIGHT / 5 && touchY < (SCREEN_HEIGHT / 5) * 2) {
        // Touched the "MENU" button
        touch.menu = 1;
        touch.quit = 0;
    } else if (touchX >= (SCREEN_WIDTH - SCREEN_WIDTH / 4) + (SCREEN_HEIGHT / 6) && touchY >= (SCREEN_HEIGHT - SCREEN_HEIGHT / 6)) {
        // Touched the "Q" button
        touch.menu = 0;
        touch.quit = 1;
    } else {
        // Touched outside the touchable areas
        touch.menu = 0;
        touch.quit = 0;
    }
}

void doTouchScoreUp(SDL_TouchFingerEvent* event)
{
    // Reset touch.menu and touch.quit
    touch.menu = 0;
    touch.quit = 0;
}

/* handles input */
void doInput(void)
{
    SDL_Event event;

    memset(app.inputText, '\0', MAX_LINE_LENGTH);

    /* reads all inputs from SDL queue */
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;
            case SDL_TEXTINPUT:
                STRNCPY(app.inputText, event.text.text, MAX_LINE_LENGTH);
                break;
            case SDL_FINGERDOWN:
                if (isKeyboardOn) {
                    doKeyboardDown(&event.tfinger);
                }else if (isMenuOn) {
                    doTouchMenuDown(&event.tfinger);
                }else if (isScoreOn) {
                    doTouchScoreDown(&event.tfinger);
                }else {
                    doTouchDown(&event.tfinger);
                }
                break;
            case SDL_FINGERUP:
                if (isKeyboardOn) {
                    doKeyboardUp(&event.tfinger);
                }else if (isMenuOn) {
                    doTouchMenuUp(&event.tfinger);
                }else if (isScoreOn) {
                    doTouchScoreUp(&event.tfinger);
                }else {
                    doTouchUp(&event.tfinger);
                }
                break;
            default:
                break;
        }
    }
}
