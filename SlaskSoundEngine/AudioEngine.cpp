#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
#ifdef _WIN32
	pXAudio2 = nullptr;
	pMasterVoice = nullptr;
#endif
}

AudioEngine::~AudioEngine()
{
#ifdef _WIN32
	pXAudio2->Release();
#endif
}

#ifdef _WIN32
HRESULT AudioEngine::initialize()
{
	//initialize xaudio2
	HRESULT hr;

	if (FAILED(hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
		return hr;
	
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return hr;

	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
		return hr;

	return 0;
}
#endif