/* menu.c: handles title screen and menu */

/*
 * Copyright (C) 2015-2018,2022 Parallel Realities. All rights reserved.
 */

#include "common.h"
#include "background.h"
#include "draw.h"
#include "highscores.h"
#include "stage.h"
#include "text.h"
#include "menu.h"

extern App app;
extern Touch touch;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool isMenuOn;
extern int logoTimer;

static void logic(void);
static void draw(void);
static void drawLogo(void);
static void drawTitle(void);
static void drawBtn(void);

static SDL_Texture *logoBackground;
static SDL_Texture *arxTitle;
static SDL_Texture *btnLargeTexture;
static SDL_Texture *btnSmallTexture;

extern char lang;

void initMenu(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    // reset the touch
    isMenuOn = true;
    touch.fire = 0;
    touch.play = 0;
    touch.score = 0;
    touch.quit = 0;
    touch.lang = 0;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

    logoBackground = loadTexture("img/logo_background.png");
    arxTitle = loadTexture("img/arx_title.png");
    btnLargeTexture = loadTexture("img/btn_large.png");
    btnSmallTexture = loadTexture("img/btn_small.png");
}

static void logic(void)
{
    doBackground();
    doStarfield();

    if (touch.lang == 1) {
        if (lang == 'P') {
            lang = 'E';
        }else {
            lang = 'P';
        }
    }

    if (touch.quit == 1) {
        exit(0);
    }

    if (touch.score == 1) {
        isMenuOn = false;
        initHighscores();
    }

    if (touch.play == 1) {
        isMenuOn = false;
        initStage();
    }
}

static void draw(void)
{
    if (logoTimer < LOGO_TIME) {
        drawLogo();
        logoTimer++;
        return;
    }else {
        drawBackground();
        drawStarfield();
        drawTitle();
        drawBtn();
    }
}

static void drawLogo(void)
{
    SDL_Rect dest;

    dest.x = 0;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    SDL_RenderCopy(app.renderer, logoBackground, NULL, &dest);
}

static void drawTitle(void)
{
    SDL_Rect r;

    r.x = 0;
    r.y = 0;

    SDL_QueryTexture(arxTitle, NULL, NULL, &r.w, &r.h);
    blitRect(arxTitle, &r, (SCREEN_WIDTH / 4) - (r.w / 2), (SCREEN_HEIGHT / 2) - (r.h / 2));
}

void drawBtn()
{
    SDL_Rect sr, pr, qr, lr;

    sr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;
    sr.y = SCREEN_HEIGHT / 6;

    pr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;
    pr.y = SCREEN_HEIGHT / 2;

    qr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4 + SCREEN_HEIGHT / 6;
    qr.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 6;

    lr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4 - SCREEN_HEIGHT / 6;
    lr.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 6;

    SDL_QueryTexture(btnLargeTexture, NULL, NULL, &sr.w, &sr.h);
    SDL_QueryTexture(btnSmallTexture, NULL, NULL, &qr.w, &qr.h);

    blit(btnLargeTexture, sr.x, sr.y);
    drawText(
            sr.x + sr.w / 2,
            sr.y + sr.h / 3,
            0,
            0,
            0,
            TEXT_CENTER,
            lang == 'P' ? "PLACAR" : "SCORE"
    );

    blit(btnLargeTexture, pr.x, pr.y);
    pr.w = sr.w;
    pr.h = sr.h;
    drawText(
            pr.x + pr.w / 2,
            pr.y + pr.h / 3,
            0,
            0,
            0,
            TEXT_CENTER,
            lang == 'P' ? "JOGAR" : "PLAY"
            );

    blit(btnSmallTexture, qr.x, qr.y);
    drawText(
            qr.x + qr.w / 2,
            qr.y + qr.h / 3,
            0,
            0,
            0,
            TEXT_CENTER,
            lang == 'P' ? "SAIR" : "QUIT"
    );

    blit(btnSmallTexture, lr.x, lr.y);
    lr.w = qr.w;
    lr.h = qr.h;
    drawText(
            lr.x + lr.w / 2,
            lr.y + lr.h / 3,
            0,
            0,
            0,
            TEXT_CENTER,
            lang == 'P' ? "PORT." : "ENG."
    );
}

