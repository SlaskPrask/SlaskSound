#include "AudioEngine.h"
#include "SlaskSoundEngine.h"

AudioEngine* engine = nullptr;

void InitializeEngine()
{
	engine->initialize();
}

void DestroyEngine()
{
	if (engine != nullptr)
	{
		delete engine;
	}
	engine = nullptr;
}

void LoadSGAF(const char* path)
{
	engine->loadData(path);
}

void PlayAudio(int index)
{
	engine->playAudio(index);
}

void StopAudio(int index)
{
	engine->stopAudio(index);
}

void RegisterErrorLogger(Callback func)
{
	Logger::registerLogCallback(func);
}