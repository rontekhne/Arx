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
extern bool isDetonaOn;

Control control;
Fire fire;

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


void doFireDown(SDL_TouchFingerEvent* event, Fire *fire)
{
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;
    if (touchX >= fire->x && touchX <= fire->x + fire->w &&
        touchY >= fire->y && touchY <= fire->y + fire->h) {
        fire->isPressed = 1;
    }
}

void doFireUp(SDL_TouchFingerEvent* event, Fire *fire)
{
    fire->isPressed = 0;
}

void controlMotion(SDL_TouchFingerEvent *event, Control *control) {
    if (control->isPressed) {
        int touchX = event->x * SCREEN_WIDTH;
        int touchY = event->y * SCREEN_HEIGHT;

        int distance = sqrt(pow(touchX - control->centerX, 2) + pow(touchY - control->centerY, 2));
        if (distance <= control->radius * 2) {
            control->lastTouchX = touchX;
            control->lastTouchY = touchY;

            double angle = atan2(touchY - control->centerY, touchX - control->centerX) * 180 / M_PI;

            if (angle >= -22.5 && angle < 22.5) {
                control->pressedDirection = SDL_DIR_RIGHT;
            } else if (angle >= 22.5 && angle < 67.5) {
                control->pressedDirection = SDL_DIR_DOWN_RIGHT;
            } else if (angle >= 67.5 && angle < 112.5) {
                control->pressedDirection = SDL_DIR_DOWN;
            } else if (angle >= 112.5 && angle < 157.5) {
                control->pressedDirection = SDL_DIR_DOWN_LEFT;
            } else if ((angle >= 157.5 && angle <= 180) || (angle >= -180 && angle < -157.5)) {
                control->pressedDirection = SDL_DIR_LEFT;
            } else if (angle >= -157.5 && angle < -112.5) {
                control->pressedDirection = SDL_DIR_UP_LEFT;
            } else if (angle >= -112.5 && angle < -67.5) {
                control->pressedDirection = SDL_DIR_UP;
            } else if (angle >= -67.5 && angle < -22.5) {
                control->pressedDirection = SDL_DIR_UP_RIGHT;
            }
        }
    }
}

void controlTouchDown(SDL_TouchFingerEvent *event, Control *control) {
    if (event->type == SDL_FINGERDOWN) {
        control->touchX = event->x * SCREEN_WIDTH;
        control->touchY = event->y * SCREEN_HEIGHT;
        control->lastTouchX = control->touchX;
        control->lastTouchY = control->touchY;

        int distance = sqrt(pow(control->touchX - control->centerX, 2) + pow(control->touchY - control->centerY, 2));
        if (distance <= control->radius) {
            control->isPressed = 1;

            double angle = atan2(control->touchY - control->centerY, control->touchX - control->centerX) * 180 / M_PI;

            if (angle >= -22.5 && angle < 22.5) {
                control->pressedDirection = SDL_DIR_RIGHT;
            } else if (angle >= 22.5 && angle < 67.5) {
                control->pressedDirection = SDL_DIR_DOWN_RIGHT;
            } else if (angle >= 67.5 && angle < 112.5) {
                control->pressedDirection = SDL_DIR_DOWN;
            } else if (angle >= 112.5 && angle < 157.5) {
                control->pressedDirection = SDL_DIR_DOWN_LEFT;
            } else if ((angle >= 157.5 && angle <= 180) || (angle >= -180 && angle < -157.5)) {
                control->pressedDirection = SDL_DIR_LEFT;
            } else if (angle >= -157.5 && angle < -112.5) {
                control->pressedDirection = SDL_DIR_UP_LEFT;
            } else if (angle >= -112.5 && angle < -67.5) {
                control->pressedDirection = SDL_DIR_UP;
            } else if (angle >= -67.5 && angle < -22.5) {
                control->pressedDirection = SDL_DIR_UP_RIGHT;
            }
        }
    }
}

void controlTouchUp(SDL_TouchFingerEvent *event, Control *control) {
    if (event->type == SDL_FINGERUP) {
        control->isPressed = 0;
        control->pressedDirection = SDL_DIR_NONE;

        control->lastTouchX = control->centerX;
        control->lastTouchY = control->centerY;
    }
}

void doTouchMenuDown(SDL_TouchFingerEvent* event)
{
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;

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

void doTouchDetonaDown(SDL_TouchFingerEvent* event)
{
    int touchX = event->x * SCREEN_WIDTH;
    int touchY = event->y * SCREEN_HEIGHT;

    int btnWidth = 120;
    int btnHeight = 120;

    int cellWidth = SCREEN_WIDTH / 6;
    int cellHeight = SCREEN_HEIGHT / 2;
    int cellX = (5 * cellWidth) + (cellWidth / 2) - cellWidth;
    int cellY = cellHeight + (cellHeight / 2);

    if (touchX >= cellX && touchX < cellX + btnWidth && touchY >= cellY && touchY < cellY + btnHeight) {
        touch.detona = 1;
    } else {
        touch.detona = 0;
    }
}

void doTouchDetonaUp(SDL_TouchFingerEvent* event)
{
    touch.detona = 0;
}

/* handles input */
void doInput(void)
{
    SDL_Event event;

    memset(app.inputText, '\0', MAX_LINE_LENGTH);

    // reads all inputs from SDL queue
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
                    if (isDetonaOn) {
                        doTouchDetonaDown(&event.tfinger);
                    }
                    controlTouchDown(&event.tfinger, &control);
                    doFireDown(&event.tfinger, &fire);
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
                    if (isDetonaOn) {
                        doTouchDetonaUp(&event.tfinger);
                    }
                    controlTouchUp(&event.tfinger, &control);
                    doFireUp(&event.tfinger, &fire);
                }
                break;
            case SDL_FINGERMOTION:
                controlMotion(&event.tfinger, &control);
                break;
            default:
                break;
        }
    }
}