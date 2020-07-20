#include "pch.h"
#include "Sound.h"

void Sound::SoundInit() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(SOUND_MAX);
	for (int i = 0; i < SOUND_MAX; i++) sound_list[i].sound = NULL;
	//sound_list = new sound_t[SOUND_MAX];
	sound_num = 0;
}
void Sound::Load(SOUND_TYPE type, int volume,const char* file) {

	Mix_Chunk* temp = Mix_LoadWAV(file);
	Mix_VolumeChunk(temp, (int)(volume * (float)MIX_MAX_VOLUME / 100.0));
	sound_list[sound_num] = { type,temp ,volume ,0};
	
	sound_num++;
}

void Sound::PlayMusic(int sound, int loop) {
	if (sound >= 0 && sound < SOUND_MAX && sound_list[sound].sound != NULL) {
		sound_list[sound].loops = loop;
		
	}
}

void Sound::Update() {
	for (int i = 0; i < SOUND_MAX; i++) {
		if (sound_list[i].sound == NULL)
			continue;
		if (sound_list[i].loops != 0) {
			Mix_PlayChannel(i, sound_list[i].sound, sound_list[i].loops);
			sound_list[i].loops = 0;
		}
			
	}
}

void Sound::SoundClose() {
	Mix_CloseAudio();
}
