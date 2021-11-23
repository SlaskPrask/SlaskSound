#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Debugger.h"
#ifdef _WIN32
#include <xaudio2.h>
#endif

#include "AudioFile.h"

class AudioEngine
{
private:
#ifdef _WIN32
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;

#endif
	std::vector<AudioFile*> audioFiles;

public:
	AudioEngine();
	~AudioEngine();
	bool initialize();
	bool loadData(std::string path);
	void playAudio(int index);
	void stopAudio(int index);
};

