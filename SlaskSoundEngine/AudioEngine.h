#pragma once
#include <iostream>
#include <string>
#ifdef _WIN32
#include <xaudio2.h>
#endif


class AudioEngine
{
private:
#ifdef _WIN32
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;
#endif
public:
	AudioEngine();
	~AudioEngine();
	HRESULT initialize();
};

