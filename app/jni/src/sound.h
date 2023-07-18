/* sound.h: header file for sound.c */

void initSounds(void);
void loadMusic(char *filename);
void playMusic(int loop);
void stopMusic(void);
void playSound(int id, int channel);