/* defs.h: contains definitions, such as the size of the window */

/* window size and screen resolution */
//#define SCREEN_WIDTH 1024
//#define SCREEN_HEIGHT 680

#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define PLAYER_SPEED 4
#define PLAYER_POWER_SPEED 16
#define PLAYER_INITIAL_ENERGY 500
#define PLAYER_INITIAL_MAGIC 500

#define MAX_KEYBOARD_KEYS 350
#define SIDE_PLAYER 0
#define SIDE_ENEMY 1
#define FPS 60
#define ENEMY_POWER_SPEED 8
#define MAX_STARS 500
#define MAX_SND_CHANNELS 8
#define NUM_HIGHSCORES 8
#define MAX_NAME_LENGTH 32
#define MAX_LINE_LENGTH 1024
#define MAX_SCORE_NAME_LENGTH 16
#define GLYPH_WIDTH 18
#define GLYPH_HEIGHT 28
#define LOGO_TIME 250
#define MAX_ENERGY 500
#define MAX_MAGIC 500
#define MAX_DETONA 10

#define PLAYER_GOT_DROP_ID 16283
#define HOURGLASS_ID 16282
#define SCORE_ID 16281
#define LOGO_ID 16280
#define ARX_MENU_ID 16279

#define SDL_DIR_UP 0
#define SDL_DIR_DOWN 1
#define SDL_DIR_LEFT 2
#define SDL_DIR_RIGHT 3
#define SDL_DIR_UP_LEFT 4
#define SDL_DIR_UP_RIGHT 5
#define SDL_DIR_DOWN_LEFT 6
#define SDL_DIR_DOWN_RIGHT 7
#define SDL_DIR_NONE 8

enum
{
    CH_ANY = -1,
    CH_PLAYER,
    CH_ENEMY_POWER,
    CH_SUPPLY,
    CH_SOULS,
    CH_EFFECT,
    CH_DEATH
};

enum
{
    SND_PLAYER_POWER,
    SND_ENEMY_POWER,
    SND_PLAYER_DIE,
    SND_ENEMY_DIE,
    SND_IMPACT,
    SND_ENERGY,
    SND_MAGIC,
    SND_SOUL_OF_THE_TIME,
    SND_DETONA,
    SND_DETONA_EXPLOSION,
    SND_VIOLET,
    SND_BLUE,
    SND_CYAN,
    SND_GREEN,
    SND_YELLOW,
    SND_ORANGE,
    SND_RED,
    SND_PINK,
    SND_TAP,
    SND_MAX
};

enum
{
    TEXT_LEFT,
    TEXT_CENTER,
    TEXT_RIGHT
};