/* background.c: handles background */

#include "common.h"
#include "background.h"
#include "draw.h"

extern App app;
extern Entity *player;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool isDetonaExplosion;

static int          backgroundX;
static Star         stars[MAX_STARS];
static SDL_Texture *background;

void initBackground(void)
{
    background = loadTexture("img/background.png");

    backgroundX = 0;
}

void initStarfield(void)
{
    int i;

    for (i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % SCREEN_WIDTH;
        stars[i].y = rand() % SCREEN_HEIGHT;
        stars[i].speed = 1 + rand() % 8;
    }
}

void doBackground(void)
{
    if (--backgroundX < -SCREEN_WIDTH) {
        backgroundX = 0;
    }
}

void doStarfield(void)
{
    int i;

    for (i = 0; i < MAX_STARS; i++) {
        stars[i].x -= stars[i].speed;

        if (stars[i].x < 0) {
            stars[i].x = SCREEN_WIDTH + stars[i].x;
        }
    }
}

void drawStarfield(void)
{
    int i, c;

    for (i = 0; i < MAX_STARS; i++) {
        c = 32 * stars[i].speed;

        SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);

        SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
    }
}

void drawBackground(void)
{
    SDL_Rect dest;
    int      x;

    for (x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        const int maxColorValue = 200;
        const int transitionSpeed = 5;

        if (isDetonaExplosion) {
            static int colorValue = 150;
            colorValue = MIN(colorValue + transitionSpeed, maxColorValue);
            SDL_SetTextureColorMod(background, colorValue, colorValue, colorValue);

            SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
            SDL_SetTextureBlendMode(background, SDL_BLENDMODE_ADD);

            int centerX = player->x + player->w / 2;
            int centerY = player->y + player->h / 2;
            int radius = MAX(SCREEN_WIDTH, SCREEN_HEIGHT) * 2;

            SDL_Rect explosionRect = {
                    centerX - radius / 2,
                    centerY - radius / 2,
                    radius,
                    radius
            };
            SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, colorValue);
            SDL_RenderFillRect(app.renderer, &explosionRect);

            SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
            SDL_RenderCopy(app.renderer, background, NULL, &dest);

            if (colorValue == maxColorValue) {
                isDetonaExplosion = false;
                colorValue = 0;
                SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
                SDL_SetTextureBlendMode(background, SDL_BLENDMODE_NONE);
            }
        } else {
            SDL_SetTextureColorMod(background, 255, 255, 255);

            SDL_RenderCopy(app.renderer, background, NULL, &dest);
        }
    }
}