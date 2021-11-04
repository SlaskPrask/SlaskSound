#include "WaveLoader.h"

char WaveLoader::checkHeader(char* header)
{
	if (Helpers::compareString(header, "fmt ", 4))
	{
		return 1;
	}
	else if (Helpers::compareString(header, "data", 4))
	{
		return 2;
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
		if (validateWaveFormat(&waveFile))
		{
			parseChunks(&waveFile);
		}
		waveFile.close();
	}
	else
	{
		std::cout << "Failed to load file: " << filePath << std::endl;
	}
}

bool WaveLoader::validateWaveFormat(std::ifstream* waveFile)
{
	char* buffer = new char[4];
	
	//first validate if it is a riff file
	waveFile->read((char*)buffer, sizeof(char) * 4);
	if (Helpers::compareString(buffer, "RIFF", 4))
	{
		//next, validate if it is a wave file
		waveFile->seekg(8);
		waveFile->read((char*)buffer, sizeof(char) * 4);
		if (Helpers::compareString(buffer, "WAVE", 4))
		{
			delete[] buffer;
			return true;
		}
	}
	delete[] buffer;
	return false;
}

void WaveLoader::parseChunks(std::ifstream* waveFile)
{
	//only chunks we care about are the fmt chunk and data chunk
	//ignore the rest of the chunk
	
	char* chunkHeader = new char[4];
	char* chunkSize = new char[4];
	uint64_t seekPosition;
	uint32_t parsedSize;
	char allDataGotten = 0;

	while (!waveFile->eof() && allDataGotten != 3)
	{
		//we assume the pointer is at start of the next chunk, so first get the chunk info
		waveFile->read((char*)chunkHeader, sizeof(char) * 4);
		waveFile->read((char*)chunkSize, sizeof(char) * 4);
		parsedSize = *chunkSize;
		seekPosition = waveFile->tellg();
		switch (checkHeader(chunkHeader))
		{
			case 1: //ftm 
				allDataGotten |= 0b00000001;
				break;
			case 2: //data
				allDataGotten |= 0b00000010;
				break;
			default:
				waveFile->seekg(seekPosition + parsedSize);
				break;
		}
	}
	std::cout << "Found all" << std::endl;
	delete[] chunkSize;
	delete[] chunkHeader;
}

