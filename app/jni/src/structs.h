/* structs.h: object definitions */

typedef struct Entity Entity;
typedef struct Explosion Explosion;
typedef struct Debris Debris;
typedef  struct Texture Texture;

/* act as a delegate for handling the logic and draw functions
 * in the game's main loop */
typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

struct Texture
{
    char name[MAX_NAME_LENGTH];
    SDL_Texture *texture;
    Texture *next;
};

/* holds references to the renderer and window */
typedef struct 
{
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    int keyboard[MAX_KEYBOARD_KEYS];
    Texture textureHead, *textureTail;
    char inputText[MAX_LINE_LENGTH];
} App;

/* represents an entity like the player and enemy */
struct Entity
{
    int id;
    int frames;
    int species;
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int energy;
    int magic;
    int soulOfTheTime;
    int violetSoul;
    int blueSoul;
    int cyanSoul;
    int greenSoul;
    int yellowSoul;
    int orangeSoul;
    int redSoul;
    int pinkSoul;
    int reload;
    int side;
    SDL_Texture *texture;
    Entity *next;
};

struct Debris
{
    float x;
    float y;
    float dx;
    float dy;
    SDL_Rect rect;
    SDL_Texture *texture;
    int life;
    Debris *next;
};

/* holds information about fighters and powers */
typedef struct
{
    Entity fighterHead, *fighterTail;
    Entity powerHead, *powerTail;
    Debris debrisHead, *debrisTail;
    Entity energyHead, *energyTail;
    Entity magicHead, *magicTail;
    Entity soulOfTheTomeHead, *soulOfTheTimeTail;
    Entity violetSoulHead, *violetSoulTail;
    Entity blueSoulHead, *blueSoulTail;
    Entity cyanSoulHead, *cyanSoulTail;
    Entity greenSoulHead, *greenSoulTail;
    Entity yellowSoulHead, *yellowSoulTail;
    Entity orangeSoulHead, *orangeSoulTail;
    Entity redSoulHead, *redSoulTail;
    Entity pinkSoulHead, *pinkSoulTail;
    int score;
} Stage;

/* object stars */
typedef struct
{
    int x;
    int y;
    int speed;
} Star;

/* object scores */
typedef struct
{
    char name[MAX_SCORE_NAME_LENGTH];
    int recent;
    int score;
} Highscore;

typedef struct
{
    Highscore highscore[NUM_HIGHSCORES];
} Highscores;

/* handles time */
typedef struct
{
    int d;
    int h;
    int m;
    int s;
} Time;

/* objects to represent touchscreen */
typedef struct
{
    int up;
    int down;
    int left;
    int right;
    int fire;
    int play;
    int score;
    int quit;
    int menu;
    int lang;
}Touch;

typedef struct
{
    int touchX;
    int touchY;
    int cellWidth;
    int cellHeight;
    int controlX;
    int controlY;
    int directionWidth;
    int directionHeight;
    int directionX;
    int directionY;
} TouchBtn;