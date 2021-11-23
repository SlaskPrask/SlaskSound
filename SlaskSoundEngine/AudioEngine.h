#pragma once
#include <iostream>
#include <string>
#include <functional>
#ifdef _WIN32
#include <xaudio2.h>
#include <system_error>
#endif

struct FormatInfo
{
	/*
		FormatTag			uint16
		NumberOfChannels	uint16
		SampleRate			uint32
		BitsPerSample		uint16
		BlockAllign			uint16
		DataSize			uint32
	*/
	uint16_t formatTag;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint16_t bitsPerSample;
	uint16_t blockAllign;
	uint32_t dataSize;

	inline bool operator==(const FormatInfo& lhs)
	{
		return lhs.formatTag == formatTag &&
			lhs.numChannels == numChannels &&
			lhs.sampleRate == sampleRate &&
			lhs.bitsPerSample == bitsPerSample &&
			lhs.blockAllign == blockAllign;
	}
};

class AudioEngine
{
private:
#ifdef _WIN32
	IXAudio2* pXAudio2;
	IXAudio2MasteringVoice* pMasterVoice;
	IXAudio2SourceVoice* pSourceVoice;


	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
#endif

	std::function<void(const char*)> errFunc;
	std::string parseError(HRESULT hr);
public:
	AudioEngine();
	~AudioEngine();
	bool initialize();
	bool loadData(std::string path);
	bool playAudio();
	bool stopAudio();
	void registerErrorLogger(std::function<void (const char*)> callback);
	void logError(std::string place, std::string errorMsg);
};

