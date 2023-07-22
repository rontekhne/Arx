/* util.c: utilities functions */

#include "common.h"
#include "text.h"

extern Stage stage;
extern unsigned long long int *Timer;
extern Entity *player;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

/* This function takes 8 arguments, essentially two rectangles.
 * It tests to see if the rectangles overlap and if so, returns 1 */
int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
}

/* This function takes six arguments: the x and y of a src coordinate,
 * the x and y of a destination coordinate, and two float references.
 * What this function does is calculate the normalized step from one
 * point to another. The dx or dy will always be 1 (or -1), while the
 * other could be any value between -1 and 1. This will be used to tell
 * the enemy's power which way they need to go to reach their target
 * when they're fired. */
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = *dy = 0;
        return;
    }

    *dx = (x1 - x2);
    *dx /= steps;

    *dy = (y1 - y2);
    *dy /= steps;
}

/* handles game time */
Time getTime(unsigned long long int *Timer)
{
    Time t;
    unsigned long long int second = *Timer / 60;

    t.s = (second % 60);
    t.m = (second % 3600) / 60;
    t.h = (second % 86400) / 3600;
    t.d = (second % (86400 * 30)) / 86400;

    return t;
}

void enemyChasePlayer(Entity *e)
{
    double hyp;

    if (player != NULL) {
        e->dx = (double)(player->x - e->x);
        e->dy = (double)(player->y - e->y);

        hyp = sqrt(e->dx*e->dx + e->dy*e->dy);
        e->dx /= hyp;
        e->dy /= hyp;

        e->x += e->dx; // * speed
        e->y += e->dy; // * speed
    }
}

/* functions to randomize enemies spawn using Fisher-Yates algorithm */
int generateRandom(int min, int max) {
    return min + rand() % (max - min + 1);
}

void shuffleArray(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = generateRandom(0, i);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void doPlusPoints(void)
{
    PlusPoints *pp, *prev;

    prev = &stage.plusPointsHead;

    for (pp = stage.plusPointsHead.next; pp != NULL; pp = pp->next) {
        pp->x -= pp->dx;
        pp->y -= pp->dy;

        if (--pp->life <= 0) {
            if (pp == stage.plusPointsTail) {
                stage.plusPointsTail = prev;
            }
            prev->next = pp->next;
            free(pp);
            pp = prev;
        }
        prev = pp;
    }
}

void addPlusPoints(Entity *e, int points)
{
    PlusPoints *pp;

    pp = malloc(sizeof(PlusPoints));
    memset(pp, 0, sizeof(PlusPoints));
    stage.plusPointsTail->next = pp;
    stage.plusPointsTail = pp;

    pp->life = FPS;
    pp->points = points;

    switch (e->species) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 12: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21:
        // species 1-8 enemies / 9 boss / 12 soft / 14-21 souls
        pp->x = SCREEN_WIDTH - 65;
        pp->y = 200;
        break;
    case 10: case 11: case 13:
        // 10 energy, 11 magic, 13 detona
        pp->x = player->x + player->w / player->frames / 2;
        pp->y = player->y;
        break;
    }

    pp->dx = 0;
    pp->dy = 2;
}

void drawPlusPoints(void)
{
    PlusPoints *pp;

    for (pp = stage.plusPointsHead.next; pp != NULL; pp = pp->next) {
        drawText(pp->x, pp->y, 255, 255, 255, TEXT_CENTER, "+ %d", pp->points);
    }
}

// used in the blitSprite function at draw.c
void resetTwoArraysSameSize(int size, int a[size], int b[size])
{
    if (player == NULL) {
        for (int i = 0; i < 16284; i++) {
            a[i] = 0;
            b[i] = 0;
        }
    }
}
