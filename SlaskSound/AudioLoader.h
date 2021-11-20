#include "WaveLoader.h"
#include <unordered_map>

#pragma once
class AudioLoader
{
private:
	std::unordered_map<std::string, uint16_t> formatKeys;
	WaveLoader waveLoader;
	std::vector<AudioData*> audioFiles;
public:

	void loadFile(std::string filePath);
	void saveFile(AudioData* data, std::string path);
	AudioData* getAudio(uint32_t index);
	bool compare(uint32_t first, uint32_t second);
	AudioLoader();
	~AudioLoader();
};

