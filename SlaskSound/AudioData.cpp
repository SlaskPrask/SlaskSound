#include "AudioData.h"

AudioData::AudioData(char* samples)
{
	sampleData = samples;
}

AudioData::~AudioData()
{
	delete[] sampleData;
}
