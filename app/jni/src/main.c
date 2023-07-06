/* main.c: where the main loop and program entry point exists */

#include "common.h"
#include "draw.h"
#include "highscores.h"
#include "init.h"
#include "input.h"
#include "main.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

App app;
Highscores highscores;
Stage stage;
Touch touch;

char lang = 'P';

bool isKeyboardOn = false;
bool isMenuOn = false;
bool isScoreOn = false;

unsigned int id; // entities id
unsigned long long int *Timer; // o tempo total
int logoTimer;

static void capFrameRate(long *then, float *remainder);

/* driver */
int main(int argc, char *argv[])
{
    long then;
    long remainder;
    logoTimer = 0;

    memset(&app, 0, sizeof(App));
    Timer = malloc(sizeof(unsigned long long int));
    app.textureTail = &app.textureHead;
    id = 1;

    initSDL();
    atexit(cleanup);
    initGame();

    then = SDL_GetTicks();
    remainder = 0;

    while (true) {
        prepareScene();
        doInput();
        app.delegate.logic();
        app.delegate.draw();
        presentScene();
        capFrameRate(&then, &remainder);
    }

    free(Timer);
    return 0;
}

/* Does some funky maths to attempt an accurate 60fps lock.
 * This works by testing how long it took to render the
 * previous frame and adjusting our SDL_Delay value appropriately.
 * The remainder comes into play due to 1000 / 60 = 16.66667.
 * This is an accumulator that will help to keep us closer to
 * 60fps rather than 62fps. It works well for the most part. */
static void capFrameRate(long *then, float *remainder)
{
    long wait, frameTime;

    wait = 16 + *remainder;
    *remainder -= (int)*remainder;
    frameTime = SDL_GetTicks() - *then;
    wait -= frameTime;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);
    *remainder += 0.667;
    *then = SDL_GetTicks();
}