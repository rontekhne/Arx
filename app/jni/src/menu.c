/* menu.c: handles title screen and menu */

#include "common.h"
#include "background.h"
#include "draw.h"
#include "highscores.h"
#include "stage.h"
#include "text.h"
#include "sound.h"
#include "volume.h"
#include "menu.h"

extern App app;
extern Touch touch;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool isMenuOn;
extern bool isHelpOn;
extern int logoTimer;
extern Volume soundVolume;
extern Volume musicVolume;

static void logic(void);
static void draw(void);
static void drawLogo(void);
static void drawTitle(void);
static void drawArx(void);
static void drawHelpBtn(void);
static void drawBtn(void);
static void drawHelp(void);

static SDL_Texture *logoTexture;
static SDL_Texture *arxTitle;
static SDL_Texture *arxTexture;
static SDL_Texture *scoreBtnTexture;
static SDL_Texture *playBtnTexture;
static SDL_Texture *helpBtnTexture;
static SDL_Texture *helpTexture;
static SDL_Texture *ptBtnTexture;
static SDL_Texture *enBtnTexture;
static SDL_Texture *quitBtnTexture;

static int reveal = 0;
static int arxX = -32;
static int langTimer = 0;
static int resetLangTimer = 9;
static int helpTimer = 0;
static int resetHelpTimer = 9;

extern char lang;

void initMenu(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    // reset the touch
    isMenuOn = true;
    touch.play = 0;
    touch.score = 0;
    touch.quit = 0;
    touch.lang = 0;
    langTimer = resetLangTimer;

    helpTimer = resetHelpTimer;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

    logoTexture = loadTexture("img/r.png");
    arxTitle = loadTexture("img/arx_title.png");
    arxTexture = loadTexture("img/arx_menu.png");
    scoreBtnTexture = loadTexture("img/score_btn.png");
    playBtnTexture = loadTexture("img/play_btn.png");
    helpTexture = loadTexture("img/help.png");
    helpBtnTexture = loadTexture("img/help_btn.png");
    ptBtnTexture = loadTexture("img/pt_btn.png");
    enBtnTexture = loadTexture("img/en_btn.png");
    quitBtnTexture = loadTexture("img/quit_btn.png");
}

static void logic(void)
{
    doBackground();
    doStarfield();
    doSoundVolume(&soundVolume);
    doMusicVolume(&musicVolume);

    if (touch.lang == 1 && --langTimer < 0) {
        langTimer = resetLangTimer;
        playSound(SND_TAP, CH_ANY);
        if (lang == 'P') {
            lang = 'E';
        }else {
            lang = 'P';
        }
    }

    if (touch.quit == 1) {
        playSound(SND_TAP, CH_ANY);
        exit(0);
    }

    if (touch.score == 1) {
        playSound(SND_TAP, CH_ANY);
        isMenuOn = false;
        initHighscores();
    }

    if (touch.play == 1) {
        playSound(SND_TAP, CH_ANY);
        isMenuOn = false;
        initStage();
    }

    if (touch.help == 1 && --helpTimer == 0) {
        helpTimer = resetHelpTimer;
        if (isHelpOn == false) {
            isHelpOn = true;
        }else {
            isHelpOn = false;
        }
        playSound(SND_TAP, CH_ANY);
    }
}

static void draw(void)
{
    if (logoTimer < LOGO_TIME) {
        drawLogo();
        logoTimer++;
        return;
    }else {
        if (reveal < SCREEN_HEIGHT) {
            reveal++;
        }

        if (arxX <= (SCREEN_WIDTH / 2) - (16)) { // arx width
            arxX++;
        }

        drawBackground();
        drawStarfield();
        drawTitle();
        drawArx();
        drawSoundVolumeBtn(&soundVolume);
        drawMusicVolumeBtn(&musicVolume);
        if (isHelpOn) {
            drawHelp();
        }
        drawBtn();
        drawHelpBtn();
    }
}

static void drawLogo(void)
{
    /* background */
    SDL_Rect fillRect;
    fillRect.x = 0;
    fillRect.y = 0;
    fillRect.w = SCREEN_WIDTH;
    fillRect.h = SCREEN_HEIGHT;
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.renderer, &fillRect);

    /* R */
    SDL_Rect r;
    SDL_QueryTexture(logoTexture, NULL, NULL, &r.w, &r.h);
    r.x = (SCREEN_WIDTH / 2) - (r.w / 10 / 2);
    r.y = (SCREEN_HEIGHT / 2) - (r.h / 10 / 2);
    blitSprite(logoTexture, r.x, r.y, 10, LOGO_ID, 4, 0);
}

static void drawTitle(void)
{
    SDL_Rect r;

    r.x = 0;
    r.y = 0;

    SDL_QueryTexture(arxTitle, NULL, NULL, &r.w, &r.h);
    r.h = MIN(reveal, r.h);
    blitRect(arxTitle, &r, (SCREEN_WIDTH / 4) - (r.w / 2), (SCREEN_HEIGHT / 2) - (r.h / 2));
}

static void drawArx(void)
{
    SDL_Rect r;

    r.x = arxX;
    r.y = 0;

    SDL_QueryTexture(arxTexture, NULL, NULL, &r.w, &r.h);
    blitSprite(arxTexture, arxX, (SCREEN_HEIGHT / 2) - (r.h / 2), 8, ARX_MENU_ID, 4, 0);
}

void drawBtn()
{
    SDL_Rect sr, pr, qr, lr;

    // score btn
    sr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;
    sr.y = SCREEN_HEIGHT / 6;
    SDL_QueryTexture(scoreBtnTexture, NULL, NULL, &sr.w, &sr.h);
    sr.w = SCREEN_WIDTH - sr.x;
    SDL_RenderCopy(app.renderer,  scoreBtnTexture, NULL, &sr);
    drawText(
            sr.x + sr.w / 2,
            sr.y + sr.h / 3,
            40,
            40,
            40,
            TEXT_CENTER,
            lang == 'P' ? "PLACAR" : "SCORE"
    );

    // play btn
    pr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;
    pr.y = SCREEN_HEIGHT / 2;
    SDL_QueryTexture(playBtnTexture, NULL, NULL, &pr.w, &pr.h);
    pr.w = SCREEN_WIDTH - pr.x;
    SDL_RenderCopy(app.renderer,  playBtnTexture, NULL, &pr);
    drawText(
            pr.x + pr.w / 2,
            pr.y + pr.h / 3,
            40,
            40,
            40,
            TEXT_CENTER,
            lang == 'P' ? "JOGAR" : "PLAY"
    );

    // quit btn
    qr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4 + SCREEN_HEIGHT / 6;
    qr.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 6;
    SDL_QueryTexture(quitBtnTexture, NULL, NULL, &qr.w, &qr.h);
    blit(quitBtnTexture, qr.x, qr.y);
    drawText(
            qr.x + qr.w / 2,
            qr.y + qr.h / 3,
            255,
            255,
            255,
            TEXT_CENTER,
            lang == 'P' ? "SAIR" : "QUIT"
    );

    // lang btn
    lr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4 - SCREEN_HEIGHT / 6;
    lr.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 6;
    SDL_QueryTexture(ptBtnTexture, NULL, NULL, &lr.w, &lr.h);
    if (lang == 'P') {
        blit(ptBtnTexture, lr.x, lr.y);
    }else {
        blit(enBtnTexture, lr.x, lr.y);
    }
}

/* Draw a help screen above the score screen
 * to help the player to play the game */
static void drawHelp(void)
{
    SDL_Rect r;

    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h = SCREEN_HEIGHT;

    SDL_RenderCopy(app.renderer, helpTexture, NULL, &r);

    int x = GLYPH_WIDTH, y;
    char pt[10][96] =
            {
                    "DEIXE O CONTROLE PRESSIONADO PARA DESVIAR DOS INIMIGOS.",
                    "OBTENHA PONTOS E GARANTA SEU LUGAR NO PLACAR.",
                    "PERDES ENERGIA QUANDO ATINGIDO OU COLIDES COM O INIMIGO.",
                    "ELIMINE OS ARXS COLORIDOS. PEGUE ALMAS E GARANTIR PONTOS.",
                    "QUANDO ELIMINAR O CHEFE, COLETE ALMA DO TEMPO POR PONTOS.",
                    "COLETE GRUPOS DE OITO ALMAS DE CORES DIFERENTES.",
                    "ACIONADOR DE DETONA APARECE QUANDO O DETONA FOR COLETADO.",
                    "ECONOMIZE MAGIA E JAMAIS DEIXE-A ACABAR.",
                    "GOSTOU DO JOGO? AJUDE COM PIX: RONTEKHNE@GMAIL.COM",
                    "DIVIRTA-SE!"
            };
    char en[10][96] =
            {
                    "HOLD DOWN THE CONTROLLER TO DODGE ENEMIES.",
                    "YOU LOSES ENERGY WHEN HIT OR COLLIDING WITH THE ENEMY.",
                    "GET POINTS AND SECURE YOUR PLACE ON THE LEADERBOARD.",
                    "KILL THE COLORFUL ARXS. COLLECT THEIR SOULS TO GET POINTS.",
                    "WHEN YOU KILL THE BOSS, GET THE SOUL OF TIME FOR POINTS.",
                    "COLLECT GROUPS OF EIGHT SOULS OF DIFFERENT COLORS.",
                    "THE WRECK TRIGGER APPEARS WHEN WRECK IS COLLECTED.",
                    "SAVE MAGIC AND NEVER LET IT RUN OUT.",
                    "HAVE FUN!"
            };
    if (lang == 'P') {
        y = SCREEN_HEIGHT / 6 + 32;
        for (int i = 0; i < 10; i++) {
            drawText(x, y + ((GLYPH_HEIGHT * 2) * i), 200, 200, 200, TEXT_LEFT, "%s", pt[i]);
            x++;
            y++;
        }
    }else {
        y = SCREEN_HEIGHT / 6 + 32;
        for (int i = 0; i < 9; i++) {
            drawText(x, y + ((GLYPH_HEIGHT * 2) * i), 200, 200, 200, TEXT_LEFT, "%s", en[i]);
            x++;
            y++;
        }
    }
}


/* Draw the help button */
static void drawHelpBtn(void)
{
    SDL_Rect hr;

    hr.x = (SCREEN_WIDTH - SCREEN_WIDTH / 4) - (SCREEN_HEIGHT / 6 * 3);
    // hr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4 - SCREEN_HEIGHT / 6;
    hr.y = SCREEN_HEIGHT - SCREEN_HEIGHT / 6;
    SDL_QueryTexture(helpBtnTexture, NULL, NULL, &hr.w, &hr.h);
    blit(helpBtnTexture, hr.x, hr.y);
    drawText(
            hr.x + hr.w / 2,
            hr.y + hr.h / 3,
            255,
            255,
            255,
            TEXT_CENTER,
            !isHelpOn ? lang == 'P' ? "AJUDA" : "HELP" : lang == 'P' ? "VOLTAR" : "BACK"
    );
}