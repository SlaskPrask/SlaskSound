#include <iostream>
#pragma once
class AudioData
{
private:
	uint16_t numChannels;	
	uint32_t sampleRate;
	uint16_t bitRate;
	uint16_t bitSize;

	char* sampleData;

public:
	AudioData(char* samples);
	~AudioData();
};

