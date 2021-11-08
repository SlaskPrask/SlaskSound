#include <iostream>
#include <string>
#include <fstream>
#include "Helpers.h"

#pragma once

class WaveLoader
{
private:
	bool validateWaveFormat(std::ifstream* waveFile);
	void parseChunks(std::ifstream* waveFile);
	char checkHeader(char* header);

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
	
	bool parseFtmInfo(std::ifstream* waveFile, uint32_t chunkSize);

public:
	WaveLoader(std::string filePath);
};

