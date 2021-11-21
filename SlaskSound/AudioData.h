#include <iostream>
#include <fstream>
#pragma once
class AudioData
{
private:
	struct
	{
		/*
			NumberOfChannels	uint16
			SampleRate			uint32
			ByteRate			uint16
			BitSize				uint16
			DataPerChannel		uint32
			Data				DataPerChannel * NumberOfChannels
		*/

		uint16_t numChannels;
		uint32_t sampleRate;
		uint16_t byteRate;
		uint16_t bitSize;
		uint32_t channelSize;

		char* sampleData;
	} fileData;

	bool writeData(std::ofstream& out);
	bool readData(std::ifstream& in);

public:
	void printInfo();
	bool validate();
	bool compare(AudioData* other);

	AudioData(char* samples, uint16_t numChannels, 
		uint32_t sampleRate, uint16_t byteRate, 
		uint16_t bitSize, uint32_t channelSize);
	bool saveAsSGAF(std::string path);
	AudioData(std::string path);
	AudioData();
	~AudioData();
};

