#pragma once
#include <string>
#ifdef _WIN32
#include <xaudio2.h>
#endif

#include "FormatInfo.h"
#include "Debugger.h"

class AudioFile
{
private:
#ifdef _WIN32

	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;
	IXAudio2SourceVoice* pSourceVoice;

#endif // _WIN32
	bool readFormatInfo(HANDLE hFile, uint32_t& dataSize, DWORD* readBytes);
	bool readDataToBuffer(HANDLE hFile, uint32_t dataSize, DWORD *readBytes);
public:
	AudioFile(std::string path, IXAudio2* pXAudio2);

	~AudioFile();
	
	void play();
	void stop();
};

