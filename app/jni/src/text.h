/* text.h: header file for text.c */

void initFonts(void);
void drawText(int x, int y, int r, int g, int b, int align, char *format, ...);
void drawFadeOutText(int x, int y, int r, int g, int b, int a, int align, char *format, ...);