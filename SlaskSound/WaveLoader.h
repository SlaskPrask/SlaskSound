#include <iostream>
#include <string>
#include <fstream>
#include "Helpers.h"
#include "AudioData.h"

#pragma once

class WaveLoader
{
private:
	bool validateWaveFormat();
	AudioData* parseChunks();
	char checkHeader(char* header);
	std::ifstream waveFile;
	struct
	{
		uint16_t audioFormat;
		uint16_t numChannels;
		uint32_t sampleRate;
		uint32_t byteRate;
		uint16_t blockAlign;
		uint16_t bitsPerSample;
		uint32_t channelSize;
	} ftmInfo;

	uint16_t audioFormat;
	
	bool parseFtmInfo(uint32_t chunkSize);
	char* readAudioData(uint32_t chunkSize);

public:
	WaveLoader();
	AudioData* loadFile(std::string filePath);
};

