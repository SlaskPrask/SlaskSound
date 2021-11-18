#include "AudioData.h"

bool AudioData::validate()
{
	return validFile;
}

AudioData::AudioData(char* samples, uint16_t numChannels,
	uint32_t sampleRate, uint16_t byteRate, 
	uint16_t bitSize, uint32_t channelSize)
{
	sampleData = samples;
	this->numChannels = numChannels;
	this->sampleRate = sampleRate;
	this->byteRate = byteRate;
	this->bitSize = bitSize;
	this->channelSize = channelSize;
	validFile = true;
}

AudioData::AudioData()
{
	//Couldn't create valid file
	validFile = false;
}

AudioData::~AudioData()
{
	delete[] sampleData;
}
