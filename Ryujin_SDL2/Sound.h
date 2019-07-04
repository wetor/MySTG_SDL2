#pragma once
#include "global.h"
static int sound_num;
static sound_t sound_list[SOUND_MAX];

class Sound
{
public:
	/*声音初始化*/
	static void SoundInit();
	/*载入*/
	static void Load(SOUND_TYPE type, int volume, const char* file);
	/*播放音乐*/
	static void PlayMusic(int sound,int loop = 1);

	/*真正的播放声音*/
	static void Update();
	/*销毁*/
	static void SoundClose();

};

