#include "AudioEngine.h"
#include "SlaskSoundEngine.h"

static AudioEngine engine;

void InitializeEngine()
{
	engine.initialize();
}

void LoadSGAF(const char* path)
{
	engine.loadData(path);
}

void PlayAudio()
{
	engine.playAudio();
}

void StopAudio()
{
	engine.stopAudio();
}
