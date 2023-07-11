/* util.c: utilities functions */

#include "common.h"

extern unsigned long long int *Timer;
extern Entity *player;

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