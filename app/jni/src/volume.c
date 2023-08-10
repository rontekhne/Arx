/* volume.c: handles sound and music volume control */

#include "common.h"
#include "draw.h"

extern App app;
Volume soundVolume;
Volume musicVolume;

void initVolume(void)
{
    soundVolume.texture = loadTexture("img/sound_control.png");
    musicVolume.texture = loadTexture("img/music_control.png");
    soundVolume.isBarOn = 0;
    soundVolume.level = 3;
    soundVolume.timer = 77;
    soundVolume.alpha = 100;
    musicVolume.isBarOn = 0;
    musicVolume.level = 3;
    musicVolume.timer = 77;
    musicVolume.alpha = 100;
}

void doSoundVolume(Volume *v)
{
    switch (v->level) {
        case 0:
                Mix_Volume(-1, 0);
            break;
        case 1:
                Mix_Volume(-1, MIX_MAX_VOLUME / 3);
            break;
        case 2:
                Mix_Volume(-1, MIX_MAX_VOLUME / 3 * 2);
            break;
        case 3:
                Mix_Volume(-1, MIX_MAX_VOLUME);
            break;
    }
}

void doMusicVolume(Volume *v)
{
    switch (v->level) {
        case 0:
            Mix_VolumeMusic(0);
            break;
        case 1:
            Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
            break;
        case 2:
            Mix_VolumeMusic(MIX_MAX_VOLUME / 3 * 2);
            break;
        case 3:
            Mix_VolumeMusic(MIX_MAX_VOLUME);
            break;
    }
}

void drawSoundVolumeBtn(Volume *v)
{
    SDL_Rect r;

    r.x = 10;
    r.y = 52;

    SDL_QueryTexture(v->texture, NULL, NULL, &r.w, &r.h);
    blit(v->texture, r.x, r.y);

    if (v->isBarOn) {
        SDL_Rect fillRect;

        fillRect.x = r.x + r.w + 10;
        fillRect.y = r.y;
        fillRect.w = r.w * v->level;
        fillRect.h = r.h;

        if (v->isTouched) {
            v->alpha = 100;
            v->timer = 77;
        }

        if (v->timer > 0) {
            v->alpha = (v->timer * 100) / 77;
            v->timer--;

            SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, v->alpha);
            SDL_RenderFillRect(app.renderer, &fillRect);
        }
    }
}

void drawMusicVolumeBtn(Volume *v)
{
    SDL_Rect r;

    r.x = 10;
    r.y = 104;

    SDL_QueryTexture(v->texture, NULL, NULL, &r.w, &r.h);
    blit(v->texture, r.x, r.y);

    if (v->isBarOn) {
        SDL_Rect fillRect;

        fillRect.x = r.x + r.w + 10;
        fillRect.y = r.y;
        fillRect.w = r.w * v->level;
        fillRect.h = r.h;

        if (v->isTouched) {
            v->alpha = 100;
            v->timer = 77;
        }

        if (v->timer > 0) {
            v->alpha = (v->timer * 100) / 77;
            v->timer--;

            SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, v->alpha);
            SDL_RenderFillRect(app.renderer, &fillRect);
        }
    }
}