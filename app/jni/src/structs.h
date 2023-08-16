/* structs.h: object definitions */

// struct definitions
typedef struct Entity Entity;
typedef struct Explosion Explosion;
typedef struct Debris Debris;
typedef struct PlusPoints PlusPoints;
typedef  struct Texture Texture;

/* act as a delegate for handling the logic and draw functions
 * in the game's main loop */
typedef struct
{
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

/* Holds the characters and texture of the font */
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
    int detona;
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
    SDL_Texture *textureDebris;
    Entity *next;
};

/* Represents the debris after entities are dead */
struct Debris
{
    float x;
    float y;
    float dx;
    float dy;
    int a;
    SDL_Rect rect;
    SDL_Texture *texture;
    int life;
    Debris *next;
};

/* Represents the text that appears when the player gets a drop */
struct PlusPoints
{
    float x;
    float y;
    float dx;
    float dy;
    int points;
    int life;
    int r;
    int g;
    int b;
    int a;
    PlusPoints *next;
};

/* linked lists: holds information about fighters and powers */
typedef struct
{
    Entity fighterHead, *fighterTail;
    Entity powerHead, *powerTail;
    Debris debrisHead, *debrisTail;
    PlusPoints plusPointsHead, *plusPointsTail;
    Entity energyHead, *energyTail;
    Entity magicHead, *magicTail;
    Entity soulOfTheTomeHead, *soulOfTheTimeTail;
    Entity detonaHead, *detonaTail;
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

/* Holds the highscore */
typedef struct
{
    Highscore highscore[NUM_HIGHSCORES];
} Highscores;

/* holds the game time */
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
    int detona;
    int play;
    int score;
    int quit;
    int menu;
    int lang;
    int help;
    int music;
    int sound;
}Touch;

/* Represents the pad */
typedef struct {
    int fingerId;
    int centerX, centerY;
    int touchX, touchY;
    int lastTouchX, lastTouchY;
    int currentX, currentY;
    int radius;
    int isPressed;
    int pressedDirection;
    SDL_Texture *texture;
} Control;

/* Represents the fire button */
typedef struct
{
    int fingerId;
    int x;
    int y;
    int w;
    int h;
    int isPressed;
    SDL_Texture *texture;
} Fire;

/* Represents the sound effect and volume control */
typedef struct
{
    int x;
    int y;
    int w;
    int h;
    int isBarOn;
    int isTouched;
    int level;
    int timer;
    int alpha;
    SDL_Texture *texture;
} Volume;

/* database */
typedef struct
{
    char *name;
    int score;
}Users;
