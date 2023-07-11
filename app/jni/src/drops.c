/* drops.c: drop functions */

#include "common.h"
#include "util.h"
#include "sound.h"
#include "draw.h"
#include "drops.h"

extern Stage stage;
extern Entity *player;

extern SDL_Texture *energyTexture;
extern SDL_Texture *magicTexture;
extern SDL_Texture *soulOfTheTimeTexture;
extern SDL_Texture *detonaTexture;
extern SDL_Texture *violetSoulTexture;
extern SDL_Texture *blueSoulTexture;
extern SDL_Texture *cyanSoulTexture;
extern SDL_Texture *greenSoulTexture;
extern SDL_Texture *yellowSoulTexture;
extern SDL_Texture *orangeSoulTexture;
extern SDL_Texture *redSoulTexture;
extern SDL_Texture *pinkSoulTexture;

extern unsigned long long int id;

void doEnergyPods(void)
{
    Entity *e, *prev;

    prev = &stage.energyHead;

    for (e = stage.energyHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->energy += (1 + rand() % 10);
            if (player->energy > MAX_ENERGY) {
                player->energy = MAX_ENERGY;
            }
            playSound(SND_ENERGY, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.energyTail) {
                stage.energyTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addEnergyPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.energyTail->next = e;

    e->id = id;
    e->frames = 8;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = energyTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doMagicPods(void)
{
    Entity *e, *prev;

    prev = &stage.magicHead;

    for (e = stage.magicHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames , e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->magic += (1 + rand() % 30);
            if (player->magic > MAX_MAGIC) {
                player->magic = MAX_MAGIC;
            };
            playSound(SND_MAGIC, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.magicTail) {
                stage.magicTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addMagicPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.magicTail->next = e;

    e->id = id;
    e->frames = 8;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = magicTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doSoulOfTheTimePods(void)
{
    Entity *e, *prev;

    prev = &stage.soulOfTheTomeHead;

    for (e = stage.soulOfTheTomeHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->soulOfTheTime += 1;
            playSound(SND_SOUL_OF_THE_TIME, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.soulOfTheTimeTail) {
                stage.soulOfTheTimeTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addSoulOfTheTimePods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.soulOfTheTimeTail->next = e;

    e->id = id;
    e->frames = 8;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = soulOfTheTimeTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doDetonaPods(void)
{
    Entity *e, *prev;

    prev = &stage.detonaHead;

    for (e = stage.detonaHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->detona += 1;
            if (player->detona > MAX_DETONA) {
                player->detona = MAX_DETONA;
                player->energy += 1;
            }
            playSound(SND_DETONA, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.detonaTail) {
                stage.detonaTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addDetonaPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.detonaTail->next = e;

    e->id = id;
    e->frames = 8;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = detonaTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doVioletSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.violetSoulHead;

    for (e = stage.violetSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->violetSoul++;
            playSound(SND_VIOLET, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.violetSoulTail) {
                stage.violetSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addVioletSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.violetSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = violetSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doBlueSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.blueSoulHead;

    for (e = stage.blueSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->blueSoul++;
            playSound(SND_BLUE, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.blueSoulTail) {
                stage.blueSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addBlueSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.blueSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = blueSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doCyanSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.cyanSoulHead;

    for (e = stage.cyanSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->cyanSoul++;
            playSound(SND_CYAN, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.cyanSoulTail) {
                stage.cyanSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addCyanSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.cyanSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = cyanSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doGreenSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.greenSoulHead;

    for (e = stage.greenSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->greenSoul++;
            playSound(SND_GREEN, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.greenSoulTail) {
                stage.greenSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addGreenSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.greenSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = greenSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doYellowSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.yellowSoulHead;

    for (e = stage.yellowSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->yellowSoul++;
            playSound(SND_YELLOW, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.yellowSoulTail) {
                stage.yellowSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addYellowSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.yellowSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = yellowSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doOrangeSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.orangeSoulHead;

    for (e = stage.orangeSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->orangeSoul++;
            playSound(SND_ORANGE, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.orangeSoulTail) {
                stage.orangeSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addOrangeSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.orangeSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = orangeSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doRedSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.redSoulHead;

    for (e = stage.redSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->redSoul++;
            playSound(SND_RED, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.redSoulTail) {
                stage.redSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addRedSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.redSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = redSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void doPinkSoulPods(void)
{
    Entity *e, *prev;

    prev = &stage.pinkSoulHead;

    for (e = stage.pinkSoulHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (player != NULL && collision(e->x, e->y, e->w / e->frames, e->h, player->x, player->y, player->w / player->frames, player->h)) {
            e->energy = 0;
            player->pinkSoul++;
            playSound(SND_PINK, CH_ANY);
        }

        if (--e->energy <= 0) {
            if (e == stage.pinkSoulTail) {
                stage.pinkSoulTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

void addPinkSoulPods(int x, int y)
{
    Entity *e;

    e = malloc(sizeof(Entity));
    memset(e, 0, sizeof(Entity));
    stage.pinkSoulTail->next = e;

    e->id = id;
    e->frames = 16;
    e->x = x;
    e->y = y;
    e->dx = -(rand() % 5);
    e->dy = (rand() % 5) - (rand() % 5);
    e->energy = FPS * 10;
    e->texture = pinkSoulTexture;

    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->x -= e->w / e->frames / 2;
    e->y -= e->h / e->frames / 2;

    ++id;
}

void drawEnergyPods(void)
{
    Entity *e;

    for (e = stage.energyHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawMagicPods(void)
{
    Entity *e;

    for (e = stage.magicHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawSoulOfTheTimePods(void)
{
    Entity *e;

    for (e = stage.soulOfTheTomeHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawDetonaPods(void)
{
    Entity *e;

    for (e = stage.detonaHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawVioletSoulPods(void)
{
    Entity *e;

    for (e = stage.violetSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawBlueSoulPods(void)
{
    Entity *e;

    for (e = stage.blueSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawCyanSoulPods(void)
{
    Entity *e;

    for (e = stage.cyanSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawGreenSoulPods(void)
{
    Entity *e;

    for (e = stage.greenSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawYellowSoulPods(void)
{
    Entity *e;

    for (e = stage.yellowSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawOrangeSoulPods(void)
{
    Entity *e;

    for (e = stage.orangeSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawRedSoulPods(void)
{
    Entity *e;

    for (e = stage.redSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

void drawPinkSoulPods(void)
{
    Entity *e;

    for (e = stage.pinkSoulHead.next; e != NULL; e = e->next) {
        if (e->energy > (FPS * 2) || e->energy % 12 < 6) {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}
