/* util.h: header file for util.c */

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy);
Time getTime(unsigned long long int *Timer);
void enemyChasePlayer(Entity *e);
int generateRandom(int min, int max);
void shuffleArray(int array[], int size);
void doPlusPoints(void);
void addPlusPoints(Entity *e, int points);
void drawPlusPoints(void);
void resetTwoArraysSameSize(int size, int a[size], int b[size]);