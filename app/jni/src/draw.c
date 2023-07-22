/* draw.c: functions related to drawing and rendering */

#include "common.h"
#include "util.h"
#include "draw.h"

extern App app;

/* prepare the renderer */
void prepareScene(void)
{
    /* set the background color in rgba */
    SDL_SetRenderDrawColor(app.renderer, 56, 47, 54, 255);
    SDL_RenderClear(app.renderer);
}

/* display the renderer */
void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

static SDL_Texture *getTexture(char *name)
{
    Texture *t;

    for (t = app.textureHead.next ; t != NULL ; t = t->next)
    {
        if (strcmp(t->name, name) == 0)
        {
            return t->texture;
        }
    }

    return NULL;
}

static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
    Texture *texture;

    texture = malloc(sizeof(Texture));
    memset(texture, 0, sizeof(Texture));
    app.textureTail->next = texture;
    app.textureTail = texture;

    STRNCPY(texture->name, name, MAX_NAME_LENGTH);
    texture->texture = sdlTexture;
}

/* load an image and return it as a texture */
SDL_Texture *loadTexture(char *filename)
{
    SDL_Texture *texture;

    texture = getTexture(filename);

    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
        texture = IMG_LoadTexture(app.renderer, filename);
        addTextureToCache(filename, texture);
    }

    return texture;
}

/* draws the texture on the screen at x and y position  */
void blit(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    
    /* double the size of the texture:
        dest.w *= 2;
        dest.h *= 2; 
    */
    
    SDL_RenderCopy(app.renderer, texture, NULL, &dest); /* drawing */
}

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(app.renderer, texture, src, &dest);
}

/* draw an animated spritesheet */
bool blitSprite(SDL_Texture *texture, int x, int y, int frames, int id, int frame_delay, int times)
{
    // draw only a portion of the image
    SDL_Rect src;
    //  draw the image only to a portion of the screen
    SDL_Rect dest;

    bool isTimes;
    // tentar alocar dinamicamente
    static int delay[16284];
    static int frame[16284];

    resetTwoArraysSameSize(16284, delay, frame);

    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    src.x = 0 + ((dest.w / frames) * frame[id]);
    src.y = 0;
    src.w = (dest.w / frames);
    src.h =  dest.h;

    dest.x = x;
    dest.y = y;
    dest.w = (dest.w / frames);
    dest.h = dest.h;

    SDL_RenderCopy(app.renderer, texture, &src, &dest);

    if (delay[id] == frame_delay) {
        ++frame[id];
        delay[id] = 0;
    }

    if (frame[id] >= frames) {
        if (times == 1) {
            frame[id] = 0;
            return true; // exit blit spritesheet once
        }else {
            frame[id] = 0; // spritesheet loop
            return false;
        }
    }

    if (frame[id] < frames) {
        if (times == 1) {
            isTimes = false; // blit once
        }else { // is
            isTimes = false; // blit loop
        }
    }

    ++delay[id];

    return isTimes;
}