#include <iostream>
#include <string>
#include <fstream>
#include "Helpers.h"

#pragma once

class WaveLoader
{
private:
	bool validateWaveFormat();
	void parseChunks();
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
	} ftmInfo;

	uint16_t audioFormat;
	
	bool parseFtmInfo(uint32_t chunkSize);
	void readAudioData(uint32_t chunkSize);

public:
	WaveLoader(std::string filePath);
};

