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

void stopMusic(void)
{
    //Mix_FadeOutMusic(1000);
    Mix_HaltMusic();
}

void playSound(int id, int channel)
{
    Mix_PlayChannel(channel, sounds[id], 0);
}

static void loadSounds(void)
{
    sounds[SND_PLAYER_POWER] = Mix_LoadWAV("snd/player_power.ogg");
    sounds[SND_ENEMY_POWER] = Mix_LoadWAV("snd/enemy_power.ogg");
    sounds[SND_PLAYER_DIE] = Mix_LoadWAV("snd/death.ogg");
    sounds[SND_ENEMY_DIE] = Mix_LoadWAV("snd/death.ogg");
    sounds[SND_IMPACT] = Mix_LoadWAV("snd/impact.ogg");
    sounds[SND_ENERGY] = Mix_LoadWAV("snd/energy.ogg");
    sounds[SND_MAGIC] = Mix_LoadWAV("snd/magic.ogg");
    sounds[SND_DETONA] = Mix_LoadWAV("snd/detona.ogg");
    sounds[SND_DETONA_EXPLOSION] = Mix_LoadWAV("snd/detona_explosion.ogg");
    sounds[SND_VIOLET] = Mix_LoadWAV("snd/violet_soul.ogg");
    sounds[SND_BLUE] = Mix_LoadWAV("snd/blue_soul.ogg");
    sounds[SND_CYAN] = Mix_LoadWAV("snd/cyan_soul.ogg");
    sounds[SND_GREEN] = Mix_LoadWAV("snd/green_soul.ogg");
    sounds[SND_YELLOW] = Mix_LoadWAV("snd/yellow_soul.ogg");
    sounds[SND_ORANGE] = Mix_LoadWAV("snd/orange_soul.ogg");
    sounds[SND_RED] = Mix_LoadWAV("snd/red_soul.ogg");
    sounds[SND_PINK] = Mix_LoadWAV("snd/pink_soul.ogg");
    sounds[SND_SOUL_OF_THE_TIME] = Mix_LoadWAV("snd/soul_of_the_time.ogg");
    sounds[SND_TAP] = Mix_LoadWAV("snd/tap.ogg");
}