/* stage.c: the game main stage */

#include "common.h"
#include "draw.h"
#include "sound.h"
#include "util.h"
#include "text.h"
#include "background.h"
#include "highscores.h"
#include "drops.h"
#include "stage.h"

extern App app;
extern Highscores highscores;
extern Stage stage;
extern Touch touch;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern char lang;
extern int id;
extern bool isDetonaOn;
extern unsigned long long int *Timer;

extern Control control;
extern Fire fire;

/* logic */
static void initPlayer(void);
static void initFireBtn(Fire *fire);
static void resetStage(void);
static void logic(void);
static void doPlayer(void);
static void doEnemies(void);
static void firePower(void);
static void fireEnemyPower(Entity *e);
static void fireDetona(void);
static int powerHitFighter(Entity *p);
static void doPower(void);
static void doFighters(void);
static void spawnEnemies(void);
static void doDebris(void);
static void addDebris(Entity *e);

static void clipPlayer(void);
/* draw */
static void draw(void);
static void drawFighters(void);
static void drawPower(void);
static void drawDebris(void);
static void drawControl(Control *control);
static void drawFireBtn(Fire *fire);
static void drawDetonaBtn(void);
static void drawHud(void);
static void drawDetonaBar(void);
static void drawEnergyBar(void);
static void drawMagicBar(void);

static int calculateTotalScore(void);

/* Entities */
Entity *player;

// Textures
static SDL_Texture *fireDetonaBtnTexture;

static SDL_Texture *playerTexture;
static SDL_Texture *playerGotDropTexture;
static SDL_Texture *powerTexture;
/* enemies textures */
static SDL_Texture *violetTexture;
static SDL_Texture *violetPowerTexture;
static SDL_Texture *blueTexture;
static SDL_Texture *bluePowerTexture;
static SDL_Texture *cyanTexture;
static SDL_Texture *cyanPowerTexture;
static SDL_Texture *greenTexture;
static SDL_Texture *greenPowerTexture;
static SDL_Texture *yellowTexture;
static SDL_Texture *yellowPowerTexture;
static SDL_Texture *orangeTexture;
static SDL_Texture *orangePowerTexture;
static SDL_Texture *redTexture;
static SDL_Texture *redPowerTexture;
static SDL_Texture *pinkTexture;
static SDL_Texture *pinkPowerTexture;
/* boss */
static SDL_Texture *bossTexture;
static SDL_Texture *bossPowerTexture;

/* hud */
static SDL_Texture *hourglassTexture;
static SDL_Texture *scoreTexture;

/* Drop textures */
SDL_Texture *energyTexture;
SDL_Texture *magicTexture;
SDL_Texture *soulOfTheTimeTexture;
SDL_Texture *detonaTexture;
SDL_Texture *violetSoulTexture;
SDL_Texture *blueSoulTexture;
SDL_Texture *cyanSoulTexture;
SDL_Texture *greenSoulTexture;
SDL_Texture *yellowSoulTexture;
SDL_Texture *orangeSoulTexture;
SDL_Texture *redSoulTexture;
SDL_Texture *pinkSoulTexture;

// control
static int enemySpawnTimer;
static int bossSpawnTimer;
static int stageResetTimer;
static int playerEnergy;
static int playerMagic;
Time t;
bool isDetonaExplosion;
bool isBlitedOnce;
bool playerGotDrop;

/* tracks died enemies */
static int violetDead;
static int blueDead;
static int cyanDead;
static int greenDead;
static int yellowDead;
static int orangeDead;
static int redDead;
static int pinkDead;
static int bossDead;

/* tracks souls */
static int playerSoulOfTheTime;
static int playerDetona;
static int playerVioletSoul;
static int playerBlueSoul;
static int playerCyanSoul;
static int playerGreenSoul;
static int playerYellowSoul;
static int playerOrangeSoul;
static int playerRedSoul;
static int playerPinkSoul;

/* randomize species */
static int specie[8] = {1, 2, 3, 4, 5, 6, 7, 8};
static int energies[8] = {1, 2, 3, 4, 5, 6, 7, 8};

void initStage(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    fireDetonaBtnTexture = loadTexture("img/detona_btn.png");
    control.texture = loadTexture("img/control.png");
    fire.texture = loadTexture("img/control.png");
    playerTexture = loadTexture("img/arx.png");
    playerGotDropTexture = loadTexture("img/arx_got_drop.png");
    powerTexture = loadTexture("img/playerPower.png");
    energyTexture = loadTexture("img/energy.png");
    magicTexture = loadTexture("img/magic.png");
    soulOfTheTimeTexture = loadTexture("img/soul_of_the_time.png");
    detonaTexture = loadTexture("img/detona.png");
    violetTexture = loadTexture("img/violet.png");
    violetPowerTexture = loadTexture("img/violetPower.png");
    blueTexture = loadTexture("img/blue.png");
    bluePowerTexture = loadTexture("img/bluePower.png");
    cyanTexture = loadTexture("img/cyan.png");
    cyanPowerTexture = loadTexture("img/cyanPower.png");
    greenTexture = loadTexture("img/green.png");
    greenPowerTexture = loadTexture("img/greenPower.png");
    yellowTexture = loadTexture("img/yellow.png");
    yellowPowerTexture = loadTexture("img/yellowPower.png");
    orangeTexture = loadTexture("img/orange.png");
    orangePowerTexture = loadTexture("img/orangePower.png");
    redTexture = loadTexture("img/red.png");
    redPowerTexture = loadTexture("img/redPower.png");
    pinkTexture = loadTexture("img/pink.png");
    pinkPowerTexture = loadTexture("img/pinkPower.png");
    bossTexture = loadTexture("img/rainbow.png");
    bossPowerTexture = loadTexture("img/bossPower.png");
    violetSoulTexture = loadTexture("img/violetSoul.png");
    blueSoulTexture = loadTexture("img/blueSoul.png");
    cyanSoulTexture = loadTexture("img/cyanSoul.png");
    greenSoulTexture = loadTexture("img/greenSoul.png");
    yellowSoulTexture = loadTexture("img/yellowSoul.png");
    orangeSoulTexture = loadTexture("img/orangeSoul.png");
    redSoulTexture = loadTexture("img/redSoul.png");
    pinkSoulTexture = loadTexture("img/pinkSoul.png");

    /* hud */
    hourglassTexture = loadTexture("img/hourglass.png");
    scoreTexture = loadTexture("img/score.png");

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

    resetStage();
    initPlayer();
    initFireBtn(&fire);
    stageResetTimer = FPS * 3;
    bossSpawnTimer = 15000;
    *Timer = 0;
    stage.score = 0;

    violetDead = 0;
    blueDead = 0;
    cyanDead = 0;
    greenDead = 0;
    yellowDead = 0;
    orangeDead = 0;
    redDead = 0;
    pinkDead = 0;
    bossDead = 0;

    isDetonaExplosion = false;
    isBlitedOnce = false;
    playerGotDrop = false;

    shuffleArray(specie, 8); // shuffle enemy species
    shuffleArray(energies, 8); // shuffle enemy energies
}

static void resetStage(void)
{
    Entity *e;
    Explosion *ex;
    Debris *d;
    PlusPoints *pp;

    while (stage.fighterHead.next) {
        e = stage.fighterHead.next;
        stage.fighterHead.next = e->next;
        free(e);
    }

    while (stage.powerHead.next) {
        e = stage.powerHead.next;
        stage.powerHead.next = e->next;
        free(e);
    }

    while (stage.debrisHead.next) {
        d = stage.debrisHead.next;
        stage.debrisHead.next = d->next;
        free(d);
    }

    while (stage.plusPointsHead.next) {
        pp = stage.plusPointsHead.next;
        stage.plusPointsHead.next = pp->next;
        free(pp);
    }

    while (stage.energyHead.next) {
        e = stage.energyHead.next;
        stage.energyHead.next = e->next;
        free(e);
    }

    while (stage.magicHead.next) {
        e = stage.magicHead.next;
        stage.magicHead.next = e->next;
        free(e);
    }

    while (stage.soulOfTheTomeHead.next) {
        e = stage.soulOfTheTomeHead.next;
        stage.soulOfTheTomeHead.next = e->next;
        free(e);
    }

    while (stage.detonaHead.next) {
        e = stage.detonaHead.next;
        stage.detonaHead.next = e->next;
        free(e);
    }

    while (stage.violetSoulHead.next) {
        e = stage.violetSoulHead.next;
        stage.violetSoulHead.next = e->next;
        free(e);
    }

    while (stage.blueSoulHead.next) {
        e = stage.blueSoulHead.next;
        stage.blueSoulHead.next = e->next;
        free(e);
    }

    while (stage.cyanSoulHead.next) {
        e = stage.cyanSoulHead.next;
        stage.cyanSoulHead.next = e->next;
        free(e);
    }

    while (stage.greenSoulHead.next) {
        e = stage.greenSoulHead.next;
        stage.greenSoulHead.next = e->next;
        free(e);
    }

    while (stage.yellowSoulHead.next) {
        e = stage.yellowSoulHead.next;
        stage.yellowSoulHead.next = e->next;
        free(e);
    }

    while (stage.orangeSoulHead.next) {
        e = stage.orangeSoulHead.next;
        stage.orangeSoulHead.next = e->next;
        free(e);
    }

    while (stage.redSoulHead.next) {
        e = stage.redSoulHead.next;
        stage.redSoulHead.next = e->next;
        free(e);
    }

    while (stage.pinkSoulHead.next) {
        e = stage.pinkSoulHead.next;
        stage.pinkSoulHead.next = e->next;
        free(e);
    }

    memset(&stage, 0, sizeof(Stage));
    stage.fighterTail = &stage.fighterHead;
    stage.powerTail = &stage.powerHead;
    stage.debrisTail = &stage.debrisHead;
    stage.plusPointsTail = &stage.plusPointsHead;
    stage.energyTail = &stage.energyHead;
    stage.magicTail = &stage.magicHead;
    stage.soulOfTheTimeTail = &stage.soulOfTheTomeHead;
    stage.detonaTail = &stage.detonaHead;
    stage.violetSoulTail = &stage.violetSoulHead;
    stage.blueSoulTail = &stage.blueSoulHead;
    stage.cyanSoulTail = &stage.cyanSoulHead;
    stage.greenSoulTail = &stage.greenSoulHead;
    stage.yellowSoulTail = &stage.yellowSoulHead;
    stage.orangeSoulTail = &stage.orangeSoulHead;
    stage.redSoulTail = &stage.redSoulHead;
    stage.pinkSoulTail = &stage.pinkSoulHead;
}

static void initPlayer(void)
{
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    stage.fighterTail->next = player;
    stage.fighterTail = player;

    player->id = 0;
    player->frames = 8;
    player->species = 0;
    player->energy = PLAYER_INITIAL_ENERGY;
    player->magic = PLAYER_INITIAL_MAGIC;
    player->soulOfTheTime = 0;
    player->detona = 0;
    player->violetSoul = 0;
    player->blueSoul = 0;
    player->cyanSoul = 0;
    player->greenSoul = 0;
    player->yellowSoul = 0;
    player->orangeSoul = 0;
    player->redSoul = 0;
    player->pinkSoul = 0;
    player->texture = playerTexture;
    player->side = SIDE_PLAYER;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
    player->x = (SCREEN_WIDTH / 2) - (player->w / player->frames / 2);
    player->y = (SCREEN_HEIGHT / 2) - (player->h / 2);
}

static void initFireBtn(Fire *fire)
{
    SDL_Rect r;

    SDL_QueryTexture(fire->texture, NULL, NULL, &r.w, &r.h);

    fire->x = SCREEN_WIDTH - r.w - 100;
    fire->y = SCREEN_HEIGHT - r.h - r.h / 2 - 100;
    fire->w = r.w;
    fire->h = r.h;
    fire->isPressed = 0;
}

static int calculateTotalScore(void) {
    int playerDrops[] = {playerVioletSoul, playerBlueSoul, playerCyanSoul, playerGreenSoul,
                          playerYellowSoul, playerOrangeSoul, playerRedSoul, playerPinkSoul};

    int totalScore;
    int bonusPoints = 0;
    int i, j;

    // has bonus? Give it
    for (i = 0; playerDrops[i] > 0; i++) {
        if (i == 7) {
            i = -1;
            bonusPoints += 15;
            for (j = 0; j < 8; j++) {
                playerDrops[j] -= 1;
            }
        }
    }

    // get remaining points from drops
    for (i = 0; i < 8; i++) {
        bonusPoints += playerDrops[i];
    }

    // get total score
    totalScore = violetDead + blueDead + cyanDead +
            greenDead + yellowDead + orangeDead +
            redDead + pinkDead + bonusPoints;

    // check if boss is dead
    if (bossDead) {
        totalScore += 50;
    }

    // check if player got soulOfTheTime | convert the time in seconds into points
    if (playerSoulOfTheTime > 0) {
        totalScore += (t.m * 60 + t.s);
        player->soulOfTheTime = 0;
    }

    return totalScore;
}


static void logic(void)
{
    if (player == NULL && --stageResetTimer <= 0) {
        *Timer = 0;
        stage.score = calculateTotalScore();
        addHighscore(stage.score);
        initHighscores();
    }

    doBackground();
    doStarfield();
    doPlayer();
    doEnemies();
    doFighters();
    spawnEnemies();
    doPower();
    doDebris();
    doPlusPoints();
    doEnergyPods();
    doMagicPods();
    doSoulOfTheTimePods();
    doDetonaPods();
    doVioletSoulPods();
    doBlueSoulPods();
    doCyanSoulPods();
    doGreenSoulPods();
    doYellowSoulPods();
    doOrangeSoulPods();
    doRedSoulPods();
    doPinkSoulPods();
    clipPlayer();

    if (player != NULL) {
        if (player->detona > 0) {
            isDetonaOn = true;
        }else {
            isDetonaOn = false;
        }

        if (player->energy < 0) {
            player->energy = 0;
        }
        if (player->magic < 0) {
            player->magic = 0;
        }
        playerEnergy = player->energy;
        playerMagic = player->magic;
        playerSoulOfTheTime = player->soulOfTheTime;
        playerDetona = player->detona;
        playerVioletSoul = player->violetSoul;
        playerBlueSoul = player->blueSoul;
        playerCyanSoul = player->cyanSoul;
        playerGreenSoul = player->greenSoul;
        playerYellowSoul = player->yellowSoul;
        playerOrangeSoul = player->orangeSoul;
        playerRedSoul = player->redSoul;
        playerPinkSoul = player->pinkSoul;
    }

    (*Timer)++;
}

static void doPlayer(void)
{
    if (player != NULL) {
        player->dx = player->dy = 0;

        if (player->reload > 0) {
            player->reload--;
        }

        switch (control.pressedDirection) {
            case SDL_DIR_UP:
                player->dy = -PLAYER_SPEED;
                break;
            case SDL_DIR_DOWN:
                player->dy = PLAYER_SPEED;
                break;
            case SDL_DIR_LEFT:
                player->dx = -PLAYER_SPEED;
                break;
            case SDL_DIR_RIGHT:
                player->dx = PLAYER_SPEED;
                break;
            case SDL_DIR_UP_LEFT:
                player->dx = -PLAYER_SPEED;
                player->dy = -PLAYER_SPEED;
                break;
            case SDL_DIR_UP_RIGHT:
                player->dx = PLAYER_SPEED;
                player->dy = -PLAYER_SPEED;
                break;
            case SDL_DIR_DOWN_LEFT:
                player->dx = -PLAYER_SPEED;
                player->dy = PLAYER_SPEED;
                break;
            case SDL_DIR_DOWN_RIGHT:
                player->dx = PLAYER_SPEED;
                player->dy = PLAYER_SPEED;
                break;
        }

        if (fire.isPressed && player->reload == 0) {
            if (player->magic > 0) {
                playSound(SND_PLAYER_POWER, CH_PLAYER);
                firePower();
                player->magic--;
            }else {
                player->magic = 0;
            }
        }

        if (app.keyboard[SDL_SCANCODE_D] || touch.detona && player->reload == 0) {
            if (player->detona > 0) {
                playSound(SND_DETONA, CH_ANY);
                fireDetona();
                touch.detona = 0; // ugly hack that works
                player->detona--;
                isDetonaExplosion = true;
            }else {
                player->detona = 0;
            }
        }
    }
}

static void doEnemies(void)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        if (e != player) {
            e->y = MIN(MAX(e->y, 0), SCREEN_HEIGHT - e->h);

            if (player != NULL && --e->reload <= 0) {
                fireEnemyPower(e);
                playSound(SND_ENEMY_POWER, CH_ENEMY_POWER);
            }
        }
    }
}

static void firePower(void)
{
    Entity *power;

    power = malloc(sizeof(Entity));
    memset(power, 0, sizeof(Entity));
    stage.powerTail->next = power;
    stage.powerTail = power;

    power->id = id;
    power->frames = 1;
    power->x = player->x + player->w / player->frames / 2;
    power->y = player->y;
    power->side = SIDE_PLAYER;
    power->dx = PLAYER_POWER_SPEED;
    power->energy = 1;
    power->texture = powerTexture;
    SDL_QueryTexture(power->texture, NULL, NULL, &power->w, &power->h);

    power->y += (player->h / 2) - (power->h / 2);

    player->reload = 8; // reload the power timer

    ++id;
}

static void fireEnemyPower(Entity *e)
{
    Entity *power;

    power = malloc(sizeof(Entity));
    memset(power, 0, sizeof(Entity));
    stage.powerTail->next = power;
    stage.powerTail = power;

    power->x = e->x;
    power->y = e->y;
    power->energy = 1;

    power->id = id;
    power->frames = 1;

    switch (e->species) {
        case 1: power->texture = violetPowerTexture; break;
        case 2: power->texture = bluePowerTexture; break;
        case 3: power->texture = cyanPowerTexture; break;
        case 4: power->texture = greenPowerTexture; break;
        case 5: power->texture = yellowPowerTexture; break;
        case 6: power->texture = orangePowerTexture; break;
        case 7: power->texture = redPowerTexture; break;
        case 8: power->texture = pinkPowerTexture; break;
        case 9: power->texture = bossPowerTexture; power->frames = 9; break;
    }

    power->side = SIDE_ENEMY;
    SDL_QueryTexture(power->texture, NULL, NULL, &power->w, &power->h);

    power->x += (e->w / e->frames / 2) - (power->w / e->frames / 2);
    power->y += (e->h / 2) - (power->h / 2);

    calcSlope(player->x + (player->w / player->frames / 2), player->y + (player->h / 2), e->x, e->y, &power->dx, &power->dy);

    power->dx *= ENEMY_POWER_SPEED;
    power->dy *= ENEMY_POWER_SPEED;

    e->reload = (rand() % FPS * 4);

    ++id;
}

static int powerHitFighter(Entity *p)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        if (e->side != p->side &&
            collision(p->x, p->y, p->w, p->h, e->x, e->y, e->w / e->frames, e->h)) {
            p->energy = 0;
            --e->energy;

            if (e == player) {
                addDebris(e);
                if (e->energy == 0) {
                    playSound(SND_PLAYER_DIE, CH_PLAYER);
                }else {
                    playSound(SND_IMPACT, CH_PLAYER);
                }
            }else {
                addDebris(e);
                if (e->energy == 0 && e->species != 9 && e->id % 10 == 0) {
                    addDetonaPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                }

                switch (e->species) {
                    case 1:
                        if (e->energy == 0) {
                            violetDead++;
                            addVioletSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 2:
                        if (e->energy == 0) {
                            blueDead++;
                            addBlueSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 3:
                        if (e->energy == 0) {
                            cyanDead++;
                            addCyanSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 4:
                        if (e->energy == 0) {
                            greenDead++;
                            addGreenSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 5:
                        if (e->energy == 0) {
                            yellowDead++;
                            addYellowSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 6:
                        if (e->energy == 0) {
                            orangeDead++;
                            addOrangeSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 7:
                        if (e->energy == 0) {
                            redDead++;
                            addRedSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 8:
                        if (e->energy == 0) {
                            pinkDead++;
                            addPinkSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                        }
                        break;
                    case 9:
                        if (e->energy == 0) {
                            addPlusPoints(e, 50);
                            for (int i = 0; i < 20; i++) {
                                switch(rand() % 10) {
                                    case 0: addVioletSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 1: addBlueSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 2: addCyanSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 3: addGreenSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 4: addYellowSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 5: addOrangeSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 6: addRedSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 7: addPinkSoulPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 8: addEnergyPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                    case 9: addMagicPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                }
                            }
                            addSoulOfTheTimePods(e->x + e->w / e->frames / 2, e->y + e->h / 2);
                            bossDead = 1;
                        }
                }

                if (e->energy == 0 && e->species != 9) {
                    addPlusPoints(e, 1);
                    switch(rand() % 2) {
                        case 0:
                            switch(rand() % 2) {
                                case 0:
                                    addEnergyPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                                case 1:
                                    addMagicPods(e->x + e->w / e->frames / 2, e->y + e->h / 2); break;
                            }
                    }
                }

                if (e->energy == 0) {
                    playSound(SND_ENEMY_DIE, CH_DEATH);
                }else {
                    playSound(SND_IMPACT, CH_DEATH);
                }
            }

            if (e->energy == 0) {
                addDebris(e);
            }

            return 1;
        }
    }
    return 0;
}

void fireDetona(void)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        if (e != player) {
            e->energy = 0;
            playSound(SND_DETONA_EXPLOSION, CH_EFFECT);
            addDebris(e);
        }
    }
}

static void doPower(void)
{
    Entity *p, *prev;

    prev = &stage.powerHead;

    for (p = stage.powerHead.next; p != NULL; p = p->next) {
        p->x += p->dx;
        p->y += p->dy;

        if (powerHitFighter(p) || p->x < -p->w || p->y < -p->h || p->x > SCREEN_WIDTH || p->y > SCREEN_HEIGHT) {
            if (p == stage.powerTail) {
                stage.powerTail = prev;
            }
            prev->next = p->next;
            free(p);
            p = prev;
        }
        prev = p;
    }
}

static void doFighters(void)
{
    Entity *e, *prev;

    prev = &stage.fighterHead;

    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        e->x += e->dx;
        e->y += e->dy;

        if (e != player && e->x < -e->w) {
            e->energy = 0;
        }

        if (e->energy == 0) {
            if (e == player) {
                player = NULL;
            }

            if (e == stage.fighterTail) {
                stage.fighterTail = prev;
            }
            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void spawnEnemies(void)
{
    Entity *enemy, *boss;
    int species;

    if (--enemySpawnTimer <= 0) {
        enemy = malloc(sizeof(Entity));
        memset(enemy, 0, sizeof(Entity));
        stage.fighterTail->next = enemy;
        stage.fighterTail = enemy;

        enemy->id = id;
        enemy->frames = 8;

        /* logic of enemies spawn */
        if (t.m == 0 && t.s < 29) {
            species = specie[0];
        }else if (t.m == 0 && t.s < 59) {
            species = specie[1];
        }else if (t.m == 1 && t.s < 29) {
            species = specie[2];
        }else if (t.m == 1 && t.s < 59) {
            species = specie[3];
        }else if (t.m == 2 && t.s < 29) {
            species = specie[4];
        }else if (t.m == 2 && t.s < 59) {
            species = specie[5];
        }else if (t.m == 3 && t.s < 29) {
            species = specie[6];
        }else if (t.m == 3 && t.s < 59) {
            species = specie[7];
        }else {
            species = 1 + rand() % 9;
        }

        /* enemy attributes */
        switch (species) {
            case 1:
                enemy->species = 1;
                enemy->texture = violetTexture;
                enemy->energy = energies[0];
                break;
            case 2:
                enemy->species = 2;
                enemy->texture = blueTexture;
                enemy->energy = energies[1];
                break;
            case 3:
                enemy->species = 3;
                enemy->texture = cyanTexture;
                enemy->energy = energies[2];
                break;
            case 4:
                enemy->species = 4;
                enemy->texture = greenTexture;
                enemy->energy = energies[3];
                break;
            case 5:
                enemy->species = 5;
                enemy->texture = yellowTexture;
                enemy->energy = energies[4];
                break;
            case 6:
                enemy->species = 6;
                enemy->texture = orangeTexture;
                enemy->energy = energies[5];
                break;
            case 7:
                enemy->species = 7;
                enemy->texture = redTexture;
                enemy->energy = energies[6];
                break;
            case 8:
                enemy->species = 8;
                enemy->texture = pinkTexture;
                enemy->energy = energies[7];
                break;
        }

        enemy->x = SCREEN_WIDTH;
        enemy->y = rand() % SCREEN_HEIGHT;
        enemy->side = SIDE_ENEMY;

        SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

        if (bossDead) {
            enemy->dx = -(2 + (rand() % 7)); //  speed
            enemy->reload = FPS / 3; // crazy reload fire
            enemySpawnTimer = 50; //  spawn time
        }else {
            enemy->dx = -(2 + (rand() % 4)); // normal speed
            enemy->reload = FPS * (1 + (rand() % 2)); // reload fire
            // between 30 and 89 milliseconds (meaning a new enemy is created between 0.5 and 1.5 seconds)
            enemySpawnTimer = 30 + (rand() % 60);
        }

        enemy->dy = -100 + (rand() % 200);
        enemy->dy /= 100;

        ++id;
    }

    if (!bossDead && --bossSpawnTimer <= 0) {
        boss = malloc(sizeof(Entity));
        memset(boss, 0, sizeof(Entity));
        stage.fighterTail->next = boss;
        stage.fighterTail = boss;

        boss->id = id;
        boss->frames = 8;
        boss->energy = 100;
        boss->species = 9;
        boss->texture = bossTexture;

        boss->x = SCREEN_WIDTH;
        boss->y = rand() % SCREEN_HEIGHT;
        boss->side = SIDE_ENEMY;

        SDL_QueryTexture(boss->texture, NULL, NULL, &boss->w, &boss->h);
        // enemy->dx = -(2 + (rand() % t.s)); // crazy speed
        boss->dx = -(2 + (rand() % 4)); // enemy speed
        boss->dy = -100 + (rand() % 200);
        boss->dy /= 100;

        // between 30 and 89 milliseconds (meaning a new enemy is created between 0.5 and 1.5 seconds)
        bossSpawnTimer = FPS * 99999;
        boss->reload = FPS * (1 + (rand() % 3));

        ++id;
    }
}

static void doDebris(void)
{
    Debris *d, *prev;

    prev = &stage.debrisHead;

    for (d = stage.debrisHead.next; d != NULL; d = d->next) {
        d->x += d->dx;
        d->y += d->dy;

        //d->dy += 0.5; gravity

        if (--d->life <= 0) {
            if (d == stage.debrisTail) {
                stage.debrisTail = prev;
            }
            prev->next = d->next;
            free(d);
            d = prev;
        }
        prev = d;
    }
}

static void addDebris(Entity *e)
{
    Debris *d;
    int x, y, w, h;

    if (e->energy > 0) { // gone to lazy down the game...
        w = e->w / e->frames / 5;
        h = e->h / 5;
    }else {
        w = e->w / e->frames / 3;
        h = e->h / 3;
    }

    for (y = 0; y <= h; y++) {
        for (x = 0; x <= w; x++) {
            d = malloc(sizeof(Debris));
            memset(d, 0, sizeof(Debris));
            stage.debrisTail->next = d;
            stage.debrisTail = d;

            d->x = e->x + x;
            d->y = e->y + y;
            // expansion rate 0.01, less is slower
            d->dx = (((rand() % 21) - 10) * 0.1) + (x - w / 2) * ((rand() % 10) * 0.01);
            d->dy = (((rand() % 21) - 10) * 0.1) + (y - h / 2) * ((rand() % 10) * 0.01);
            d->life = FPS * 4;
            d->texture = e->texture;

            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = 2;
            d->rect.h = 2;
        }
    }
}

static void clipPlayer(void)
{
    if (player != NULL) {
        if (player->x < 0) {
            player->x = 0;
        }

        if (player->y < 0) {
            player->y = 0;
        }

        if (player->x > SCREEN_WIDTH - player->w / player->frames) {
            player->x = SCREEN_WIDTH - player->w / player->frames;
        }

        if (player->y > SCREEN_HEIGHT - player->h) {
            player->y = SCREEN_HEIGHT - player->h;
        }
    }
}

static void draw(void)
{
    drawBackground();
    drawStarfield();
    drawFighters();
    drawPower();
    drawDebris();
    drawPlusPoints();
    drawEnergyPods();
    drawMagicPods();
    drawSoulOfTheTimePods();
    drawDetonaPods();
    drawVioletSoulPods();
    drawBlueSoulPods();
    drawCyanSoulPods();
    drawGreenSoulPods();
    drawYellowSoulPods();
    drawOrangeSoulPods();
    drawRedSoulPods();
    drawPinkSoulPods();
    drawControl(&control);
    drawFireBtn(&fire);

    if (isDetonaOn) {
        drawDetonaBtn();
    }

    drawHud();
}

static void drawFighters(void)
{
    Entity *e;

    for (e = stage.fighterHead.next; e != NULL; e = e->next) {
        if (e->species == 9) {
            enemyChasePlayer(e);
        }

        if (e == player) {
            if (playerGotDrop) {
                isBlitedOnce = blitSprite(playerGotDropTexture, e->x, e->y, 24, e->id, 6, 1);
                if (isBlitedOnce) {
                    isBlitedOnce = false;
                    playerGotDrop = false;
                }
            }else {
                blitSprite(e->texture, e->x, e->y, e->frames, e->id, 6, 0);
            }
        }else {
            blitSprite(e->texture, e->x, e->y, e->frames, e->id, 4, 0);
        }
    }
}

static void drawPower(void)
{
    Entity *p;

    for (p = stage.powerHead.next; p != NULL; p = p->next) {
        blitSprite(p->texture, p->x, p->y, p->frames, p->id, 4, 0);
    }
}

static void drawDebris(void)
{
    Debris *d;

    for (d = stage.debrisHead.next; d != NULL; d = d->next) {
        blitRect(d->texture, &d->rect, d->x, d->y);
    }
}

static void drawControl(Control *control) {
    SDL_Rect r;

    SDL_QueryTexture(control->texture, NULL, NULL, &r.w, &r.h);
    control->radius = (r.w < r.h) ? r.w / 2 : r.h / 2;

    int controlX = 100 + control->radius;
    int controlY = SCREEN_HEIGHT - r.h - control->radius - 50;

    control->centerX = controlX;
    control->centerY = controlY;

    if (control->isPressed) {
        controlX = control->touchX;
        controlY = control->touchY;
        SDL_SetTextureColorMod(control->texture, 255, 255, 255);
    } else {
        SDL_SetTextureColorMod(control->texture, 128, 128, 128);
    }

    int renderX = controlX - control->radius;
    int renderY = controlY - control->radius;

    blit(control->texture, renderX, renderY);
}

static void drawFireBtn(Fire *fire)
{
    if (fire->isPressed) {
        SDL_SetTextureColorMod(fire->texture, 255, 255, 255);
    } else {
        SDL_SetTextureColorMod(fire->texture, 128, 128, 128);
    }

    blit(fire->texture, fire->x, fire->y);
}

static void drawDetonaBtn(void)
{
    int cellWidth3 = SCREEN_WIDTH / 6;
    int cellHeight3 = SCREEN_HEIGHT / 2;
    int cell2X = (5 * cellWidth3) + (cellWidth3 / 2) - cellWidth3;
    int cell2Y = cellHeight3 + (cellHeight3 / 2); - (240);

    if (t.s % 2 == 0) {
        SDL_SetTextureColorMod(fireDetonaBtnTexture, 255, 255, 255);
    } else {
        SDL_SetTextureColorMod(fireDetonaBtnTexture, 128, 128, 128);
    }
    blit(fireDetonaBtnTexture, cell2X, cell2Y);
}

static void drawHud(void) {
    t = getTime(Timer);

    blitSprite(hourglassTexture, 10, 5, 6, 16270, 3, 0);
    drawText(30, 10, 255, 255, 255, TEXT_LEFT, " %02d:%02d", t.m, t.s);

    drawDetonaBar();
    drawEnergyBar();
    drawMagicBar();

    blit(scoreTexture, SCREEN_WIDTH - 130, 5);
    drawText(SCREEN_WIDTH - 35, 10, 255, 255, 255, TEXT_RIGHT, " %03d", calculateTotalScore());
}

static void drawDetonaBar(void)
{
    int x = SCREEN_WIDTH * 10 / 100;
    int y = 10;
    int barWidth = SCREEN_WIDTH * 5 / 100;
    int barHeight = 20;
    float fillRatio = (float)playerDetona / 10.0;

    SDL_Rect fillRect;
    fillRect.x = x;
    fillRect.y = y;
    fillRect.w = (int)(barWidth * fillRatio);
    fillRect.h = barHeight;

    Uint32 colors[] = {0xffffff, 0xbfbfbf, 0x808080, 0x404040};
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int colorIndex = SDL_GetTicks() / 80 % numColors;

    Uint8 r = (colors[colorIndex] >> 16) & 0xFF;
    Uint8 g = (colors[colorIndex] >> 8) & 0xFF;
    Uint8 b = colors[colorIndex] & 0xFF;

    SDL_SetRenderDrawColor(app.renderer, r, g, b, 255);
    SDL_RenderFillRect(app.renderer, &fillRect);
}

static void drawEnergyBar(void)
{
    int x = SCREEN_WIDTH * 15 / 100;
    int y = 10;
    int barWidth = SCREEN_WIDTH * 35.0 / 100.0;
    int barHeight = 20;
    float fillRatio = (float)playerEnergy / 500.0;

    SDL_Rect fillRect;
    fillRect.x = x;
    fillRect.y = y;
    fillRect.w = (int)(barWidth * fillRatio);
    fillRect.h = barHeight;

    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.renderer, &fillRect);
}

static void drawMagicBar(void)
{
    int x = SCREEN_WIDTH * 50 / 100;
    int y = 10;
    int barWidth = SCREEN_WIDTH * 35.0 / 100.0;
    int barHeight = 20;
    float fillRatio = (float)playerMagic / 500.0;

    SDL_Rect fillRect;
    fillRect.x = x;
    fillRect.y = y;
    fillRect.w = (int)(barWidth * fillRatio);
    fillRect.h = barHeight;

    Uint32 colors[] = {0xa373e6, 0x739de6, 0x73e6e0, 0x73e69b, 0xe6e373, 0xe6a373, 0xe67373, 0xe673d2};
    int numColors = sizeof(colors) / sizeof(colors[0]);
    int colorIndex = SDL_GetTicks() / 80 % numColors;

    Uint8 r = (colors[colorIndex] >> 16) & 0xFF;
    Uint8 g = (colors[colorIndex] >> 8) & 0xFF;
    Uint8 b = colors[colorIndex] & 0xFF;

    SDL_SetRenderDrawColor(app.renderer, r, g, b, 255);
    SDL_RenderFillRect(app.renderer, &fillRect);
}