#include "AudioData.h"

void AudioData::printInfo()
{
	std::cout << "Number of Channels: " << fileData.numChannels << std::endl <<
		"Sample Rate: " << fileData.sampleRate << std::endl <<
		"Byte Rate: " << fileData.byteRate << std::endl <<
		"Bit Size: " << fileData.bitSize << std::endl <<
		"Data per Channel: " << fileData.channelSize << std::endl;
}

bool AudioData::validate()
{
	return fileData.sampleData != nullptr;
}

bool AudioData::compare(AudioData* other)
{
	if (other->fileData.numChannels == fileData.numChannels &&
		other->fileData.sampleRate == fileData.sampleRate &&
		other->fileData.byteRate == fileData.byteRate &&
		other->fileData.bitSize == fileData.bitSize &&
		other->fileData.channelSize == fileData.channelSize)
	{
		uint32_t size = fileData.numChannels * fileData.channelSize;
		for (uint32_t i = 0; i < size; i++)
		{
			if (other->fileData.sampleData[i] != fileData.sampleData[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

AudioData::AudioData(char* samples, uint16_t numChannels,
	uint32_t sampleRate, uint16_t byteRate, 
	uint16_t bitSize, uint32_t channelSize)
{
	fileData.sampleData = samples;
	fileData.numChannels = numChannels;
	fileData.sampleRate = sampleRate;
	fileData.byteRate = byteRate;
	fileData.bitSize = bitSize;
	fileData.channelSize = channelSize;
}

bool AudioData::saveAsSGAF(std::string path)
{
	std::ofstream file(path + ".sgaf", std::ios::binary);
	if (file.is_open())
	{
		if (writeData(file))
		{
			file.close();
			return true;
		}
		file.close();
	}
	
	return false;
}

bool AudioData::writeData(std::ofstream& out)
{
	try
	{
		uint32_t dataSize = fileData.numChannels * fileData.channelSize;
		//order of data here is important
		/*
			NumberOfChannels	uint16
			SampleRate			uint32
			ByteRate			uint16
			BitSize				uint16
			DataPerChannel		uint32
			Data				DataPerChannel * NumberOfChannels
		*/
		out.write(reinterpret_cast<char*>(&fileData.numChannels), sizeof(uint16_t));
		out.write(reinterpret_cast<char*>(&fileData.sampleRate), sizeof(uint32_t));
		out.write(reinterpret_cast<char*>(&fileData.byteRate), sizeof(uint16_t));
		out.write(reinterpret_cast<char*>(&fileData.bitSize), sizeof(uint16_t));
		out.write(reinterpret_cast<char*>(&fileData.channelSize), sizeof(uint32_t));

		out.write(fileData.sampleData, sizeof(char) * dataSize);
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error saving file due to:\n" << e.what() << std::endl;
		return false;
	}
}

bool AudioData::readData(std::ifstream& in)
{
	try
	{
		//order of data here is important
		/*
			NumberOfChannels	uint16
			SampleRate			uint32
			ByteRate			uint16
			BitSize				uint16
			DataPerChannel		uint32
			Data				DataPerChannel * NumberOfChannels
		*/
		in.read(reinterpret_cast<char*>(&fileData.numChannels), sizeof(uint16_t));
		in.read(reinterpret_cast<char*>(&fileData.sampleRate), sizeof(uint32_t));
		in.read(reinterpret_cast<char*>(&fileData.byteRate), sizeof(uint16_t));
		in.read(reinterpret_cast<char*>(&fileData.bitSize), sizeof(uint16_t));
		in.read(reinterpret_cast<char*>(&fileData.channelSize), sizeof(uint32_t));

		uint32_t dataSize = fileData.numChannels * fileData.channelSize;
		fileData.sampleData = new char[dataSize];
		in.read(fileData.sampleData, sizeof(char) * dataSize);

		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error loading file due to:\n" << e.what() << std::endl;
		return false;
	}
}

AudioData::AudioData()
{
	//Couldn't create valid file
	fileData.sampleData = nullptr;
}

AudioData::AudioData(std::string path)
{
	std::ifstream file(path, std::ios::binary);
	fileData.sampleData = nullptr;
	if (file.is_open())
	{
		if (readData(file))
		{

		}
	}
}

AudioData::~AudioData()
{
	if (fileData.sampleData != nullptr)
		delete[] fileData.sampleData;
}
