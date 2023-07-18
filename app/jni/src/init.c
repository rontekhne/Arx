/* init.c: functions concerned with setting up sdl */

#include "common.h"
#include "background.h"
#include "highscores.h"
#include "menu.h"
#include "init.h"
#include "sound.h"
#include "text.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern App app;
extern Stage stage;

void initSDL(void)
{
    int rendererFlags, windowFlags;
    
    /* flags to the renderer and window */
    rendererFlags = SDL_RENDERER_ACCELERATED;
    windowFlags = SDL_WINDOW_FULLSCREEN;

    /* initialize SDL2 video subsystem */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* create the window */
    app.window = SDL_CreateWindow(
        "Arx",
        SDL_WINDOWPOS_UNDEFINED, /* OS choose initial position */
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        windowFlags);

    if (!app.window) {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Set hint for separate mouse and touch events
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_TOUCH_EVENTS, "1", SDL_HINT_OVERRIDE);

    /* Define a orientação paisagem */
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "Landscape");

    /* create the renderer */
    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    /* initialize sound */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    /* Initialize SDL image for png and jpg */
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    /* get real window size */
    SDL_GetWindowSize(app.window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    /* hide the cursor */
    SDL_ShowCursor(0);
}

void initGame(void)
{
    initBackground();
    initStarfield();
    initSounds();
    initFonts();
    initHighscoreTable();
    initMenu();
    memset(&stage, 0, sizeof(Stage));
    loadMusic("msc/arx_main_theme.ogg");
    playMusic(1);
}

void cleanup(void)
{
    IMG_Quit();
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
