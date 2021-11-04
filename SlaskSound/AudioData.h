#include <iostream>
#pragma once
class AudioData
{
private:
	uint16_t numChannels;
	
	uint32_t sampleRate;
	uint16_t bitRate;

	void** sampleData;

public:
};

