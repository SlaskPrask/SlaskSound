#include "AudioLoader.h"

AudioLoader::AudioLoader()
{
	formatKeys["wav"] = 1;
	formatKeys["ogg"] = 2;
	formatKeys["sgaf"] = 3;
}

void AudioLoader::loadFile(std::string filePath)
{
	//check fileformat by extension
	std::string str = filePath.substr(filePath.find_last_of(".") + 1);
	AudioData* data = nullptr;

	switch (formatKeys[str])
	{
		case 1: //Wav
			data = waveLoader.loadFile(filePath);
			break;
		case 2: //Ogg
			break;
		case 3: //SGAF
			data = new AudioData(filePath);
			break;
		default:
			break;
	}

	if (data != nullptr && data->validate())
	{
		audioFiles.push_back(data);
	}
	else
	{
		std::cout << "Failed to load file " << filePath << std::endl;
	}
}

void AudioLoader::saveFile(AudioData* data, std::string path)
{
	data->saveAsSGAF(path);
}

AudioData* AudioLoader::getAudio(uint32_t index)
{
	if (index < audioFiles.size())
		return audioFiles[index];

	return nullptr;
}

bool AudioLoader::compare(uint32_t first, uint32_t second)
{
	return getAudio(first)->compare(getAudio(second));
}

AudioLoader::~AudioLoader()
{
	for (auto it : audioFiles)
	{
		delete it;
	}
}
