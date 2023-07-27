/* text.c: handles text drawing on the screen */

#include "common.h"
#include "draw.h"
#include "text.h"

static SDL_Texture *fontTexture;
static SDL_Texture *fadeOutFontTexture;
static char drawTextBuffer[MAX_LINE_LENGTH];
static char drawFadeOutTextBuffer[MAX_LINE_LENGTH];

void initFonts(void)
{
    fontTexture = loadTexture("img/font.png");
    fadeOutFontTexture = loadTexture("img/font_fade_out.png");
}

void drawText(int x, int y, int r, int g, int b, int align, char *format, ...)
{
    int i, len, c;
    SDL_Rect rect;
    va_list args;

    memset(&drawTextBuffer, '\0', sizeof(drawTextBuffer));

    va_start(args, format);
    vsprintf(drawTextBuffer, format, args);
    va_end(args);

    len = strlen(drawTextBuffer);

    switch (align) {
        case TEXT_RIGHT:
            x -= (len * GLYPH_WIDTH);
            break;
        case TEXT_CENTER:
            x -= (len * GLYPH_WIDTH) / 2;
            break;
    }

    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    SDL_SetTextureColorMod(fontTexture, r, g, b);

    for (i = 0; i < len; i++) {
        c = drawTextBuffer[i];

        if (c >= ' ' && c <= 'Z') {
            rect.x = (c - ' ') * GLYPH_WIDTH;
            blitRect(fontTexture, &rect, x, y);
            x += GLYPH_WIDTH;
        }
    }
}

void drawFadeOutText(int x, int y, int r, int g, int b, int a, int align, char *format, ...)
{
    int i, len, c;
    SDL_Rect rect;
    va_list args;

    memset(&drawFadeOutTextBuffer, '\0', sizeof(drawFadeOutTextBuffer));

    va_start(args, format);
    vsprintf(drawFadeOutTextBuffer, format, args);
    va_end(args);

    len = strlen(drawFadeOutTextBuffer);

    switch (align) {
        case TEXT_RIGHT:
            x -= (len * GLYPH_WIDTH);
            break;
        case TEXT_CENTER:
            x -= (len * GLYPH_WIDTH) / 2;
            break;
    }

    rect.w = GLYPH_WIDTH;
    rect.h = GLYPH_HEIGHT;
    rect.y = 0;

    SDL_SetTextureColorMod(fadeOutFontTexture, r, g, b);
    SDL_SetTextureAlphaMod(fadeOutFontTexture, a);

    for (i = 0; i < len; i++) {
        c = drawFadeOutTextBuffer[i];

        if (c >= ' ' && c <= 'Z') {
            rect.x = (c - ' ') * GLYPH_WIDTH;
            blitRect(fadeOutFontTexture, &rect, x, y);
            x += GLYPH_WIDTH;
        }
    }
}