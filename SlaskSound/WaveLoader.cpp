#include "WaveLoader.h"

char WaveLoader::checkHeader(char* header)
{
	std::cout << header << std::endl;
	if (Helpers::compareString(header, "fmt ", 4))
	{
		return 1;
	}
	else if (Helpers::compareString(header, "data", 4))
	{
		return 2;
	}
	else if (Helpers::compareString(header, "fact", 4))
	{
		return 3;
	}
	return 0;

}


WaveLoader::WaveLoader(std::string filePath)
{

	//Start by loading the file data into a bit stream or something
	
	//start by opening the file
	std::ifstream waveFile(filePath, std::ios::binary);
	if (waveFile.is_open())
	{
		if (validateWaveFormat())
		{
			parseChunks();
		}
		waveFile.close();
		std::cout << "Audio Format: " << ftmInfo.audioFormat
			<< "\nChannels: " << ftmInfo.numChannels
			<< "\nSample Rate: " << ftmInfo.sampleRate
			<< "\nByte Rate: " << ftmInfo.byteRate
			<< "\nBlock Align: " << ftmInfo.blockAlign
			<< "\nBits per Sample: " << ftmInfo.bitsPerSample << std::endl;
	}
	else
	{
		std::cout << "Failed to load file: " << filePath << std::endl;
	}
}

bool WaveLoader::validateWaveFormat()
{
	char* buffer = new char[4];
	bool res = false;
	//first validate if it is a riff file
	waveFile.read((char*)buffer, sizeof(char) * 4);
	if (Helpers::compareString(buffer, "RIFF", 4))
	{
		//next, validate if it is a wave file
		waveFile.seekg(8);
		waveFile.read((char*)buffer, sizeof(char) * 4);
		if (Helpers::compareString(buffer, "WAVE", 4))
		{
			res = true;
		}
	}
	delete[] buffer;
	return res;
}

void WaveLoader::parseChunks()
{
	//only chunks we care about are the fmt chunk and data chunk
	//ignore the rest of the chunks
	
	char* chunkHeader = new char[4];
	char* chunkSize = new char[4];
	uint64_t seekPosition;
	uint32_t parsedSize;
	char allDataGotten = 0;
	bool getFact = false;

	while (allDataGotten != 3 || getFact)
	{
		//we assume the pointer is at start of the next chunk, so first get the chunk info
		waveFile.read((char*)chunkHeader, sizeof(char) * 4);
		waveFile.read((char*)chunkSize, sizeof(char) * 4);
		parsedSize = Helpers::littleEndianToUInt32(chunkSize);
		seekPosition = waveFile.tellg();
		switch (checkHeader(chunkHeader))
		{
			case 1: //ftm 
				getFact = parseFtmInfo(parsedSize);
				allDataGotten |= 0b00000001;
				break;
			case 2: //data
				allDataGotten |= 0b00000010;
				waveFile.seekg(seekPosition + parsedSize);
				break;
			case 3: //fact: Is ignored for now, due to my file not having it :D
				getFact = false;
				waveFile.seekg(seekPosition + parsedSize);
				break;
			default:
				break;
		}
		waveFile.read((char*)chunkSize, 1);
		if (waveFile.eof())
		{
			break;
		}
		waveFile.seekg(seekPosition + parsedSize);
	}

	delete[] chunkSize;
	delete[] chunkHeader;
}

bool WaveLoader::parseFtmInfo(uint32_t chunkSize)
{
	waveFile.read((char*)&ftmInfo, sizeof(ftmInfo));
	if (chunkSize != sizeof(ftmInfo))
	{
		//we might need to parse a fact chunk later
		waveFile.seekg((uint64_t)waveFile.tellg() + (chunkSize - sizeof(ftmInfo)));
		return true;
	}
	return false;
}

void WaveLoader::readAudioData(uint32_t chunkSize)
{

}