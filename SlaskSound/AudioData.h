#include <iostream>
#pragma once
class AudioData
{
private:
	uint16_t numChannels;	
	uint32_t sampleRate;
	uint16_t byteRate;
	uint16_t bitSize;
	uint32_t channelSize;

	char* sampleData;
	bool validFile;

public:
	bool validate();

	AudioData(char* samples, uint16_t numChannels, 
		uint32_t sampleRate, uint16_t byteRate, 
		uint16_t bitSize, uint32_t channelSize);
	AudioData();
	~AudioData();
};

