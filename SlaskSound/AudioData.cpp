#include "AudioData.h"

void AudioData::printInfo()
{
	std::cout << "Format Tag: " << fileData.fmtInfo.formatTag << std::endl << 
		"Number of Channels: " << fileData.fmtInfo.numChannels << std::endl <<
		"Sample Rate: " << fileData.fmtInfo.sampleRate << std::endl <<
		"Bits per Sample: " << fileData.fmtInfo.bitsPerSample << std::endl <<
		"Block Allign: " << fileData.fmtInfo.blockAllign << std::endl <<
		"Data Size: " << fileData.fmtInfo.dataSize << std::endl;
}

bool AudioData::validate()
{
	return fileData.sampleData != nullptr;
}

bool AudioData::compare(AudioData* other)
{
	if (other->fileData.fmtInfo == fileData.fmtInfo)
	{
		for (uint32_t i = 0; i < fileData.fmtInfo.dataSize; i++)
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

AudioData::AudioData(FormatInfo fmtInfo, char* samples)
{
	fileData.fmtInfo = fmtInfo;
	fileData.sampleData = samples;
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
		//order of data here is important
		/*
			FormatTag			uint16
			NumberOfChannels	uint16
			SampleRate			uint32
			BitSize				uint16
			BlockAllign			uint16
			DataSize			uint32
			Data				?
		*/
		out.write(reinterpret_cast<char*>(&fileData.fmtInfo), sizeof(FormatInfo));
		out.write(fileData.sampleData, sizeof(char) * fileData.fmtInfo.dataSize);
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
			FormatTag			uint16
			NumberOfChannels	uint16
			SampleRate			uint32
			BitSize				uint16
			BlockAllign			uint16
			DataSize			uint32
			Data				DataSize (char*)
		*/
		in.read(reinterpret_cast<char*>(&fileData.fmtInfo), sizeof(FormatInfo));
		
		fileData.sampleData = new char[fileData.fmtInfo.dataSize];
		in.read(fileData.sampleData, sizeof(char) * fileData.fmtInfo.dataSize);

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
	fileData = { 0 };
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
