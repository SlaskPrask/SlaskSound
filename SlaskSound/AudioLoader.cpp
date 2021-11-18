#include "AudioLoader.h"

AudioLoader::AudioLoader()
{
	formatKeys["wav"] = 1;
}

void AudioLoader::loadFile(std::string filePath)
{
	//check fileformat by extension
	std::string str = filePath.substr(filePath.find_last_of(".") + 1);

	switch (formatKeys[str])
	{
		case 1: //Wav
			testAudio = waveLoader.loadFile(filePath);
			break;
		default:
			break;
	}

	std::cout << testAudio->validate() << std::endl;
}


AudioLoader::~AudioLoader()
{
	delete testAudio;
}
