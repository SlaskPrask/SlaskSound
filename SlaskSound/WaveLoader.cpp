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
	else if (Helpers::compareString(header, "fact", 4))
	{
		return 3;
	}
	return 0;

}

AudioData* WaveLoader::loadFile(std::string filePath)
{
	waveFile = std::ifstream(filePath, std::ios::binary);
	if (waveFile.is_open())
	{
		if (validateWaveFormat())
		{
			AudioData* data = parseChunks();
			waveFile.close();
			return data;
		}
		else
		{
			waveFile.close();
		}
	}

	std::cout << "Failed to load file: " << filePath << std::endl;
	return nullptr;
}


WaveLoader::WaveLoader()
{
	fmtInfo = { 0 };
	fmtBuffer = { 0 };
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

AudioData* WaveLoader::parseChunks()
{
	//only chunks we care about are the fmt chunk and data chunk
	//ignore the rest of the chunks
	
	char* chunkHeader = new char[4];
	char* chunkSize = new char[4];
	char* sampleData = nullptr;
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
		std::cout << chunkHeader << " size: " << parsedSize << std::endl;
		switch (checkHeader(chunkHeader))
		{
			case 1: //ftm 
				getFact = parseFtmInfo(parsedSize);
				allDataGotten |= 0b00000001;
				break;
			case 2: //data
				sampleData = readAudioData(parsedSize);
				allDataGotten |= 0b00000010;
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

	//should now create an audiodata file
	if (sampleData != nullptr)
		return new AudioData(fmtInfo, sampleData);
	else 
		return nullptr;
}

bool WaveLoader::parseFtmInfo(uint32_t chunkSize)
{
	waveFile.read((char*)&fmtBuffer, sizeof(fmtBuffer));
	fmtInfo.formatTag = fmtBuffer.audioFormat;
	fmtInfo.numChannels = fmtBuffer.numChannels;
	fmtInfo.sampleRate = fmtBuffer.sampleRate;
	fmtInfo.bitsPerSample = fmtBuffer.bitsPerSample;
	fmtInfo.blockAllign = fmtBuffer.blockAlign;

	if (chunkSize != 16)
	{
		//we might need to parse a fact chunk later
		waveFile.seekg((uint64_t)waveFile.tellg() + (chunkSize - 16));
		return true;
	}
	return false;
}

char* WaveLoader::readAudioData(uint32_t chunkSize)
{
	fmtInfo.dataSize = chunkSize;
	char* audioData = new char[chunkSize];
	uint16_t sampleSize = fmtBuffer.bitsPerSample / 8;
	waveFile.read((char*)audioData, chunkSize);
	return audioData;
}