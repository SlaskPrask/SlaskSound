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
	for (auto it : audioFiles)
	{
		delete it;
	}
#ifdef _WIN32
	pMasterVoice->DestroyVoice();
	pXAudio2->Release();
#endif
}

#ifdef _WIN32
bool AudioEngine::initialize()
{
	//initialize xaudio2
	HRESULT hr;

	if (FAILED(hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
	{
		if (hr != RPC_E_CHANGED_MODE)
		{		
			Logger::logError("Initializing audio thread", hr);
			return false;
		}
	}
	
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		Logger::logError("Creating XAudio", hr);
		return false;
	}

	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
	{
		Logger::logError("Creating master voice", hr);
		return false;
	}

	return true;
}
#endif

bool AudioEngine::loadData(std::string path)
{
	audioFiles.push_back(new AudioFile(path, pXAudio2));
}

void AudioEngine::playAudio(int index)
{
	if (index < audioFiles.size())
		audioFiles[index]->play();
}

void AudioEngine::stopAudio(int index)
{
	if (index < audioFiles.size())
		audioFiles[index]->stop();
}