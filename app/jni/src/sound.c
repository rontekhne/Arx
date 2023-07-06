/* sound.c: functions that handles sound effects */

#include "common.h"
#include "sound.h"

static void loadSounds(void);

static Mix_Chunk *sounds[SND_MAX];
static Mix_Music *music;

void initSounds(void)
{
    memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
    music = NULL;
    loadSounds();
}

void loadMusic(char *filename)
{
    if (music != NULL) {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }
    music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
    Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
    sounds[SND_PLAYER_POWER] = Mix_LoadWAV("snd/player_power.ogg");
    sounds[SND_ENEMY_POWER] = Mix_LoadWAV("snd/enemy_power.ogg");
    sounds[SND_PLAYER_DIE] = Mix_LoadWAV("snd/player_die.ogg");
    sounds[SND_ENEMY_DIE] = Mix_LoadWAV("snd/enemy_die.ogg");
    sounds[SND_ENERGY] = Mix_LoadWAV("snd/energy.ogg");
    sounds[SND_MAGIC] = Mix_LoadWAV("snd/magic.ogg");
}