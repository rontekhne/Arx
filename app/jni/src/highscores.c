/* highscores.c: handles highscore table */

/* includes the headers used in this file */
#include "common.h"
#include "background.h"
#include "highscores.h"
#include "menu.h"
#include "draw.h"
#include "stage.h"
#include "sound.h"
#include "volume.h"
#include "text.h"
#include "databaseManager.h"

/* add the extern global variables, constants and structures */
extern App app;
extern Stage stage;
extern Highscores highscores;
extern Touch touch;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern bool isKeyboardOn;
extern bool isScoreOn;
extern char lang;
extern Volume soundVolume;
extern Users *users;

/* prototypes of the static functions */
static void logic(void);
static void draw(void);
static int  highscoreComparator(const void *a, const void *b);
static void drawHighscores(void);
static void doNameInput(void);
static void drawNameInput(void);
static void drawVirtualKeyboard(void);
static void drawBtn(void);
static void drawTextPresentation(void);
static void drawNameExists(void);

/* declaration of static textures */
static SDL_Texture *menuBtnTexture;
static SDL_Texture *quitBtnTexture;
static SDL_Texture *trophyTexture;
static SDL_Texture * virtualKeyboard;

/* static logic variables used here */
static Highscore *newHighscore;
static int        cursorBlink;
static int lastScore;

static bool isUnique;

extern JavaVM *jvm; // Ponter to JVM

/* this function initialize the score table with ANON if
 * there's no score recorded, otherwise it's populated
 * with the name and score of the player */
void initHighscoreTable(void)
{
    int i;

    memset(&highscores, 0, sizeof(Highscores));

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        STRNCPY(highscores.highscore[i].name, users[i].name, MAX_SCORE_NAME_LENGTH);
        highscores.highscore[i].score = users[i].score;
    }

    newHighscore = NULL;
    cursorBlink = 0;
}

/* this function initialize this module, aka highscores.
 * It begins delegating the logic and draw functions to
 * the app, then there are control variables being initialized,
 * textures being loaded and memory allocated to the keyboard keys */
void initHighscores(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    isScoreOn = true;
    isUnique = true;

    menuBtnTexture = loadTexture("img/menu_btn.png");
    quitBtnTexture = loadTexture("img/quit_btn.png");
    trophyTexture = loadTexture("img/trophy.png");
    virtualKeyboard = loadTexture("img/virtual_keyboard.png");
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

/* This is the main logic function of the hoghscore module.
 * It handles the pressing of buttons and uses flags to do
 * it */
static void logic(void)
{
    doBackground();
    doStarfield();

    if (touch.menu == 1) {
        playSound(SND_TAP, CH_ANY);
        isScoreOn = false;
        isKeyboardOn = false;
        touch.menu = 0;
        initMenu();
        return;
    }

    if (touch.quit == 1) {
        playSound(SND_TAP, CH_ANY);
        exit(0);
    }

    if (newHighscore != NULL) {
        isKeyboardOn = true;
        isScoreOn = false;
        doNameInput();
        doSoundVolume(&soundVolume);
    }else {
        isKeyboardOn = false;
        isScoreOn = true;
    }

    if (++cursorBlink >= FPS) {
        cursorBlink = 0;
    }
}

/* This function handles the touch of the virtual keyboard and its
 * called for all keys in the doNameInput function. It begins setting
 * static variables to hold the time in order to simulate a delay to
 * avoid multi click when the player clicks it. After this, the
 * variables are updated inside the if statement and a delay is applyed */
static void handleVirtualKeyboardTouch(char character, int keyboardCode, int* n, char* name)
{
    /* handle delay touch */
    static int touchInProgress = 0;
    static unsigned int lastTouchTime = 0;
    static unsigned int touchDelay = 500; // Delay in milliseconds

    if (app.keyboard[keyboardCode] && (!touchInProgress || (SDL_GetTicks() - lastTouchTime) >= touchDelay)) {
        playSound(SND_TAP, CH_ANY);
        name[*n] = character;
        touchInProgress = 1;
        lastTouchTime = SDL_GetTicks();
        (*n)++;
    }
}

/* This function handles the input in the virtual keyboard screen.
 * It uses the handleVirtualKeyboardTouch function to apply a delay
 * when the player touches in a key and is done when the return key
 * is pressed. */
static void doNameInput(void)
{
    int  i, j, n;

    n = strlen(newHighscore->name);

    if (n < MAX_SCORE_NAME_LENGTH - 1) {
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
        handleVirtualKeyboardTouch('\"', SDL_SCANCODE_DOUBLEQUOTE, &n, newHighscore->name);
        handleVirtualKeyboardTouch('\0', SDL_SCANCODE_RETURN, &n, newHighscore->name);
        // fouth row
        handleVirtualKeyboardTouch('!', SDL_SCANCODE_KP_EXCLAM, &n, newHighscore->name);
        handleVirtualKeyboardTouch('Z', SDL_SCANCODE_Z, &n, newHighscore->name);
        handleVirtualKeyboardTouch('X', SDL_SCANCODE_X, &n, newHighscore->name);
        handleVirtualKeyboardTouch('C', SDL_SCANCODE_C, &n, newHighscore->name);
        handleVirtualKeyboardTouch('V', SDL_SCANCODE_V, &n, newHighscore->name);
        handleVirtualKeyboardTouch('B', SDL_SCANCODE_B, &n, newHighscore->name);
        handleVirtualKeyboardTouch('N', SDL_SCANCODE_N, &n, newHighscore->name);
        handleVirtualKeyboardTouch('M', SDL_SCANCODE_M, &n, newHighscore->name);
        handleVirtualKeyboardTouch('-', SDL_SCANCODE_HIFEN, &n, newHighscore->name);
        handleVirtualKeyboardTouch('\'', SDL_SCANCODE_APOSTROPHE, &n, newHighscore->name);
        // fifth row
        handleVirtualKeyboardTouch('?', SDLK_QUESTION, &n, newHighscore->name);
        handleVirtualKeyboardTouch('#', SDL_SCANCODE_KP_HASH, &n, newHighscore->name);
        handleVirtualKeyboardTouch('$', SDL_SCANCODE_DOLAR, &n, newHighscore->name);
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
    }

    if (n > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE]) {
        newHighscore->name[--n] = '\0';
        app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
    }

    if (app.keyboard[SDL_SCANCODE_RETURN]) {

        isUnique = true;

        /* manual iteration to find equal names in highscores */
        for (i = 0; i < NUM_HIGHSCORES; i++) {
            for (j = 0; users[i].name[j] == newHighscore->name[j]; j++) {
                if (users[i].name[j] == '\0' && newHighscore->name[j] == '\0') {
                    isUnique = false;
                    break;
                }
            }
            if (isUnique == false) {
                break;
            }
        }

        if (isUnique && strlen(newHighscore->name) != 0) {
            JNIEnv *env = SDL_AndroidGetJNIEnv();
            saveData(jvm, env, newHighscore->name, lastScore);

            newHighscore = NULL;
            loadMusic("msc/arx_main_theme.ogg");
            playMusic(1);
        }
    }
}

/* The draw function calls all draw functions in this module.
 * It has a logic to handle the switching between screen and
 * draw accordingly */
static void draw(void)
{
    drawBackground();
    drawStarfield();

    if (newHighscore != NULL) {
        drawNameInput();
        drawVirtualKeyboard();
        if (isUnique == false) {
            drawNameExists();
        }
        drawSoundVolumeBtn(&soundVolume);
    }
    else {
        drawHighscores();
        drawTextPresentation();
        drawBtn();
    }
}

/* This function uses the font texture to draw each
 * character in the virtual keyboard screen. It simply
 * draw the character pressed */
static void drawNameInput(void)
{
    SDL_Rect r;

    // drawVirtualKeyboard();

    drawText(SCREEN_WIDTH / 2, 70, 255, 255, 255, TEXT_CENTER, lang == 'P' ? "EXCELENTE! VOCE ENTROU PARA O PLACAR!" : "CONGRATULATIONS, YOU'VE GAINED A HIGHSCORE!");
    drawText(SCREEN_WIDTH / 2, 120, 255, 255, 255, TEXT_CENTER, lang == 'P' ? "DIGITE SEU NOME ABAIXO:" : "ENTER YOUR NAME BELOW:");
    drawText(SCREEN_WIDTH / 2, 250, 255, 255, 255, TEXT_CENTER, newHighscore->name);

    if (cursorBlink < FPS / 2) {
        r.x = ((SCREEN_WIDTH / 2) + (strlen(newHighscore->name) * GLYPH_WIDTH) / 2) + 5;
        r.y = 250;
        r.w = GLYPH_WIDTH;
        r.h = GLYPH_HEIGHT;

        SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(app.renderer, &r);
    }
}

/* This function draws the eight score in the highscore
 * table. It choses colors for the first three ranks and
 * draw the rest with the same fourth color: that's grey. */
static void drawHighscores(void)
{
    int i, y, r, g, b;

    y = SCREEN_HEIGHT / 6;

    blit(trophyTexture, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 8);

    for (i = 0; i < NUM_HIGHSCORES; i++) {
        r = 191;
        g = 191;
        b = 191;

        if (i == 0) { // gold
            r = 230;
            g = 227;
            b = 115;
        }else if (i == 1) { // silver
            r = 255;
            g = 255;
            b = 255;
        }else if (i == 2) { // bronze
            r = 230;
            g = 184;
            b = 184;
        }

        drawText(SCREEN_WIDTH / 10, y + 70, r, g, b, TEXT_LEFT, "%d %-20s %03d", (i + 1), highscores.highscore[i].name, highscores.highscore[i].score);

        y += 50;
    }

    // temporary while has no database
    if (newHighscore == NULL) {
        drawText(SCREEN_WIDTH / 10, y + 70, r, g, b, TEXT_LEFT, lang == 'P' ? "SEUS PONTOS:           %03d" : "YOUR SCORES:           %03d", stage.score);
    }
}

/* This function add the new highscore if the player has one.
 * It get the score from the game and puts it in the table */
void addHighscore(int score)
{
    Highscore newHighscores[NUM_HIGHSCORES + 1];
    int       i;

    lastScore = score; // for database

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

/* This function compares the scores with the purpose
 * of order. The socre table has an order that goes from
 * the forst place to the eighth */
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

    dest.x = 0;
    dest.y = SCREEN_HEIGHT / 2;

    SDL_QueryTexture(virtualKeyboard, NULL, NULL, &dest.w, &dest.h);
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT / 2;
    SDL_RenderCopy(app.renderer, virtualKeyboard, NULL, &dest);
}

/* Draw the menu and quit buttons in the score screen */
void drawBtn()
{
    SDL_Rect mr, qr;

    mr.x = SCREEN_WIDTH - SCREEN_WIDTH / 4;
    mr.y = SCREEN_HEIGHT / 6;
    SDL_QueryTexture(menuBtnTexture, NULL, NULL, &mr.w, &mr.h);
    mr.w = SCREEN_WIDTH - mr.x;
    SDL_RenderCopy(app.renderer,  menuBtnTexture, NULL, &mr);
    drawText(
            mr.x + mr.w / 2,
            mr.y + mr.h / 3,
            40,
            40,
            40,
            TEXT_CENTER,
            "MENU"
    );

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
}

/* This function draws a text in the score screen */
static void drawTextPresentation(void)
{
    char textPt[] = "O INIMIGO PODE CONTER UMA ALMA, QUEPOR ALGUM MOTIVO DESCONHECIDO FAZ ASUA ALMA ALIMENTAR-SE DE PODERES DEOUTRO MUNDO. SOIS UM ARX E SUA FAMAEMERGE COMO FRUTO DE SUAS BATALHAS. ";
    char textEn[] = "THE ENEMY MAY POSSESS A SOUL,      WHICH FOR SOME UNKNOWN REASON FEEDSON POWERS FROM ANOTHER WORLD. YOU  ARE AN ARX, AND YOUR FAME EMERGES  AS THE FRUIT OF YOUR BATTLES.         ";
    char line[256] = "";
    char temp[256] = "";
    int x = SCREEN_WIDTH / 2;
    int y = SCREEN_HEIGHT / 3 + GLYPH_HEIGHT * 2;
    int i;
    static int counter = 0;
    static int lineCounter = 1;
    const int saveX = x;
    const int saveY = y;

    if (lang == 'P') {
        strcpy(line, textPt);
    }else {
        strcpy(line, textEn);
    }

    for (i = 0; i < counter; i++) {
        temp[i] = line[i];
    }
    temp[i] = '\0';

    if (SDL_GetTicks() % 15 == 0) {
        counter++;
    }

    if (counter > strlen(line)) {
        counter = 0;
        lineCounter = 1;
        x = saveX;
        y = saveY;
    }

    int maxCharsPerLine = strlen(line) / 5;

    for (i = 0; i < counter; i++) {
        drawText(x, y, 200, 200, 200, TEXT_LEFT, "%c", temp[i]);
        x += GLYPH_WIDTH;

        if ((i + 1) % maxCharsPerLine == 0) {
            x = saveX;
            y += (GLYPH_HEIGHT * 2);
            lineCounter++;
        }
    }
}

static void drawNameExists(void)
{
    drawText(SCREEN_WIDTH / 2, 340, 255, 255, 255, TEXT_CENTER, lang == 'P' ? "ESSE NOME EXISTE :(" : "THIS NAME EXISTS :(");
}