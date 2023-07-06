/* highscores.c: handles highscore table */

#include "common.h"
#include "background.h"
#include "highscores.h"
#include "menu.h"
#include "draw.h"
#include "stage.h"
#include "text.h"

extern App app;
extern Highscores highscores;
extern Touch touch;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool isKeyboardOn;
extern int isScoreOn;
extern char lang;

static void logic(void);
static void draw(void);
static int  highscoreComparator(const void *a, const void *b);
static void drawHighscores(void);
static void doNameInput(void);
static void drawNameInput(void);
static void drawVirtualKeyboard(void);
static void drawBtn(void);

static SDL_Texture * virtualKeyboard;
static Highscore *newHighscore;
static int        cursorBlink;

void initHighscoreTable(void)
{
    int i;

    memset(&highscores, 0, sizeof(Highscores));

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        highscores.highscore[i].score = NUM_HIGHSCORES - i;
        STRNCPY(highscores.highscore[i].name, "ANON", MAX_SCORE_NAME_LENGTH);
    }

    newHighscore = NULL;
    cursorBlink = 0;
}

void initHighscores(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    isScoreOn = true;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

static void logic(void)
{
    doBackground();
    doStarfield();

    if (touch.menu == 1) {
        isScoreOn = false;
        isKeyboardOn = false;
        touch.menu = 0;
        initMenu();
        return;
    }

    if (touch.quit == 1) {
        exit(0);
    }

    if (newHighscore != NULL) {
        isKeyboardOn = true;
        isScoreOn = false;
        doNameInput();
    }else {
        isKeyboardOn = false;
        isScoreOn = true;
        initHighscores();
    }

    if (++cursorBlink >= FPS) {
        cursorBlink = 0;
    }
}

static void handleVirtualKeyboardTouch(char character, int keyboardCode, int* n, char* name)
{
    /* handle delay touch */
    static int touchInProgress = 0;
    static unsigned int lastTouchTime = 0;
    static unsigned int touchDelay = 500; // Delay in milliseconds

    if (app.keyboard[keyboardCode] && (!touchInProgress || (SDL_GetTicks() - lastTouchTime) >= touchDelay)) {
        name[*n] = character;
        touchInProgress = 1;
        lastTouchTime = SDL_GetTicks();
        (*n)++;
    }
}

static void doNameInput(void)
{
    int  i, n;
    char c;

    n = strlen(newHighscore->name);

    for (i = 0; i < strlen(app.inputText); i++) {
        c = toupper(app.inputText[i]);

        if (n < MAX_SCORE_NAME_LENGTH - 1 && c >= ' ' && c <= 'Z') {
            newHighscore->name[n++] = c;
        }
    }

    /* get touch */

    // first row
    handleVirtualKeyboardTouch('0', SDL_SCANCODE_0, &n, newHighscore->name);
    handleVirtualKeyboardTouch('1', SDL_SCANCODE_1, &n, newHighscore->name);
    handleVirtualKeyboardTouch('2', SDL_SCANCODE_2, &n, newHighscore->name);
    handleVirtualKeyboardTouch('3', SDL_SCANCODE_3, &n, newHighscore->name);
    handleVirtualKeyboardTouch('4', SDL_SCANCODE_4, &n, newHighscore->name);
    handleVirtualKeyboardTouch('5', SDL_SCANCODE_5, &n, newHighscore->name);
    handleVirtualKeyboardTouch('6', SDL_SCANCODE_6, &n, newHighscore->name);
    handleVirtualKeyboardTouch('7', SDL_SCANCODE_7, &n, newHighscore->name);
    handleVirtualKeyboardTouch('8', SDL_SCANCODE_8, &n, newHighscore->name);
    handleVirtualKeyboardTouch('9', SDL_SCANCODE_9, &n, newHighscore->name);
    handleVirtualKeyboardTouch(':', SDL_SCANCODE_KP_COLON, &n, newHighscore->name);
    handleVirtualKeyboardTouch(';', SDL_SCANCODE_SEMICOLON, &n, newHighscore->name);
    handleVirtualKeyboardTouch('=', SDL_SCANCODE_EQUALS, &n, newHighscore->name);
    // second row
    handleVirtualKeyboardTouch('Q', SDL_SCANCODE_Q, &n, newHighscore->name);
    handleVirtualKeyboardTouch('W', SDL_SCANCODE_W, &n, newHighscore->name);
    handleVirtualKeyboardTouch('E', SDL_SCANCODE_E, &n, newHighscore->name);
    handleVirtualKeyboardTouch('R', SDL_SCANCODE_R, &n, newHighscore->name);
    handleVirtualKeyboardTouch('T', SDL_SCANCODE_T, &n, newHighscore->name);
    handleVirtualKeyboardTouch('Y', SDL_SCANCODE_Y, &n, newHighscore->name);
    handleVirtualKeyboardTouch('U', SDL_SCANCODE_U, &n, newHighscore->name);
    handleVirtualKeyboardTouch('I', SDL_SCANCODE_I, &n, newHighscore->name);
    handleVirtualKeyboardTouch('O', SDL_SCANCODE_O, &n, newHighscore->name);
    handleVirtualKeyboardTouch('P', SDL_SCANCODE_P, &n, newHighscore->name);
    handleVirtualKeyboardTouch('<', SDL_SCANCODE_KP_LESS, &n, newHighscore->name);
    handleVirtualKeyboardTouch('>', SDL_SCANCODE_KP_GREATER, &n, newHighscore->name);
    handleVirtualKeyboardTouch('@', SDL_SCANCODE_KP_AT, &n, newHighscore->name);
    // third row
    handleVirtualKeyboardTouch('A', SDL_SCANCODE_A, &n, newHighscore->name);
    handleVirtualKeyboardTouch('S', SDL_SCANCODE_S, &n, newHighscore->name);
    handleVirtualKeyboardTouch('D', SDL_SCANCODE_D, &n, newHighscore->name);
    handleVirtualKeyboardTouch('F', SDL_SCANCODE_F, &n, newHighscore->name);
    handleVirtualKeyboardTouch('G', SDL_SCANCODE_G, &n, newHighscore->name);
    handleVirtualKeyboardTouch('H', SDL_SCANCODE_H, &n, newHighscore->name);
    handleVirtualKeyboardTouch('J', SDL_SCANCODE_J, &n, newHighscore->name);
    handleVirtualKeyboardTouch('K', SDL_SCANCODE_K, &n, newHighscore->name);
    handleVirtualKeyboardTouch('L', SDL_SCANCODE_L, &n, newHighscore->name);
    handleVirtualKeyboardTouch('P', SDL_SCANCODE_P, &n, newHighscore->name);
    //handleVirtualKeyboardTouch('\"', 34, &n, newHighscore->name);
    handleVirtualKeyboardTouch(' ', SDL_SCANCODE_RETURN, &n, newHighscore->name);
    // fouth row
    handleVirtualKeyboardTouch('!', SDL_SCANCODE_KP_EXCLAM, &n, newHighscore->name);
    handleVirtualKeyboardTouch('Z', SDL_SCANCODE_Z, &n, newHighscore->name);
    handleVirtualKeyboardTouch('X', SDL_SCANCODE_X, &n, newHighscore->name);
    handleVirtualKeyboardTouch('C', SDL_SCANCODE_C, &n, newHighscore->name);
    handleVirtualKeyboardTouch('V', SDL_SCANCODE_V, &n, newHighscore->name);
    handleVirtualKeyboardTouch('B', SDL_SCANCODE_B, &n, newHighscore->name);
    handleVirtualKeyboardTouch('N', SDL_SCANCODE_N, &n, newHighscore->name);
    handleVirtualKeyboardTouch('M', SDL_SCANCODE_M, &n, newHighscore->name);
    handleVirtualKeyboardTouch('\'', SDL_SCANCODE_APOSTROPHE, &n, newHighscore->name);
    // fifth row
    //handleVirtualKeyboardTouch('?', 63, &n, newHighscore->name);
    handleVirtualKeyboardTouch('#', SDL_SCANCODE_KP_HASH, &n, newHighscore->name);
    //handleVirtualKeyboardTouch('$', 36, &n, newHighscore->name);
    handleVirtualKeyboardTouch('%', SDL_SCANCODE_KP_PERCENT, &n, newHighscore->name);
    handleVirtualKeyboardTouch('&', SDL_SCANCODE_KP_AMPERSAND, &n, newHighscore->name);
    handleVirtualKeyboardTouch('(', SDL_SCANCODE_KP_LEFTPAREN, &n, newHighscore->name);
    handleVirtualKeyboardTouch(')', SDL_SCANCODE_KP_RIGHTPAREN, &n, newHighscore->name);
    handleVirtualKeyboardTouch('*', SDL_SCANCODE_KP_MULTIPLY, &n, newHighscore->name);
    handleVirtualKeyboardTouch('+', SDL_SCANCODE_KP_PLUS, &n, newHighscore->name);
    handleVirtualKeyboardTouch('.', SDL_SCANCODE_KP_PERIOD, &n, newHighscore->name);
    handleVirtualKeyboardTouch('/', SDL_SCANCODE_KP_DIVIDE, &n, newHighscore->name);
    handleVirtualKeyboardTouch(',', SDL_SCANCODE_KP_COMMA, &n, newHighscore->name);
    // sixth row
    handleVirtualKeyboardTouch('\0', SDL_SCANCODE_BACKSPACE, &n, newHighscore->name); // verify
    handleVirtualKeyboardTouch(' ', SDL_SCANCODE_SPACE, &n, newHighscore->name);


    if (n > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE]) {
        newHighscore->name[--n] = '\0';
        app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
    }

    if (app.keyboard[SDL_SCANCODE_RETURN]) {
        if (strlen(newHighscore->name) == 0) {
            STRNCPY(newHighscore->name, "ANON", MAX_SCORE_NAME_LENGTH);
        }
        newHighscore = NULL;
    }
}

static void draw(void)
{
    drawBackground();
    drawStarfield();

    if (newHighscore != NULL) {
        drawNameInput();
    }
    else {
        drawHighscores();
        drawBtn();
    }
}

static void drawNameInput(void)
{
    SDL_Rect r;

    drawVirtualKeyboard();

    drawText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, lang == 'P' ? "EXCELENTE! VOCE ENTROU PARA O PLACAR!" : "CONGRATULATIONS, YOU'VE GAINED A HIGHSCORE!");
    drawText(SCREEN_WIDTH / 2, 120, 255, 255, 255, TEXT_CENTER, lang == 'P' ? "DIGITE SEU NOME ABAIXO:" : "ENTER YOUR NAME BELOW:");
    drawText(SCREEN_WIDTH / 2, 250, 128, 255, 128, TEXT_CENTER, newHighscore->name);

    if (cursorBlink < FPS / 2) {
        r.x = ((SCREEN_WIDTH / 2) + (strlen(newHighscore->name) * GLYPH_WIDTH) / 2) + 5;
        r.y = 250;
        r.w = GLYPH_WIDTH;
        r.h = GLYPH_HEIGHT;

        SDL_SetRenderDrawColor(app.renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(app.renderer, &r);
    }
}

static void drawHighscores(void)
{
    int i, y, r, g, b;

    y = 150;

    drawText(SCREEN_WIDTH / 3, y, 255, 255, 255, TEXT_CENTER, lang == 'P' ? "PLACAR" : "HIGHSCORES");

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        r = 255;
        g = 255;
        b = 255;

        if (highscores.highscore[i].recent) {
            b = 0;
        }

        drawText(SCREEN_WIDTH / 3, y + 70, r, g, b, TEXT_CENTER, "#%d. %-15s ...... %03d", (i + 1), highscores.highscore[i].name, highscores.highscore[i].score);

        y += 50;
    }
}

void addHighscore(int score)
{
    Highscore newHighscores[NUM_HIGHSCORES + 1];
    int       i;

    memset(newHighscores, 0, sizeof(Highscore) * (NUM_HIGHSCORES + 1));

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        newHighscores[i] = highscores.highscore[i];
        newHighscores[i].recent = 0;
    }

    newHighscores[NUM_HIGHSCORES].score = score;
    newHighscores[NUM_HIGHSCORES].recent = 1;

    qsort(newHighscores, NUM_HIGHSCORES + 1, sizeof(Highscore), highscoreComparator);

    newHighscore = NULL;

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        highscores.highscore[i] = newHighscores[i];

        if (highscores.highscore[i].recent) {
            newHighscore = &highscores.highscore[i];
        }
    }
}

static int highscoreComparator(const void *a, const void *b)
{
    Highscore *h1 = ((Highscore*)a);
    Highscore *h2 = ((Highscore*)b);

    return h2->score - h1->score;
}

/* draw the android virtual keyboard */
static void drawVirtualKeyboard(void)
{
    SDL_Rect dest;
    virtualKeyboard = loadTexture("img/virtual_keyboard.png");

    blit(virtualKeyboard, dest.w, SCREEN_HEIGHT / 2);

    dest.x = 0;
    dest.y = SCREEN_HEIGHT / 2;

    SDL_QueryTexture(virtualKeyboard, NULL, NULL, &dest.w, &dest.h);
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT / 2;
    SDL_RenderCopy(app.renderer, virtualKeyboard, NULL, &dest);
}

void drawBtn()
{
    drawText(
            SCREEN_WIDTH - SCREEN_WIDTH / 4,
            SCREEN_HEIGHT / 5,
            255,
            255,
            255,
            TEXT_CENTER,
            "MENU"
    );
    drawText(
            SCREEN_WIDTH - SCREEN_WIDTH / 4 + SCREEN_HEIGHT / 6,
            SCREEN_HEIGHT - SCREEN_HEIGHT / 6,
            255,
            255,
            255,
            TEXT_RIGHT,
            lang == 'P' ? "S" : "Q"
    );
}


