#include "WaveLoader.h"
#include <unordered_map>

#pragma once
class AudioLoader
{
private:
	std::unordered_map<std::string, uint16_t> formatKeys;
	WaveLoader waveLoader;
	AudioData* testAudio;
public:
	void loadFile(std::string filePath);
	AudioLoader();
	~AudioLoader();
};

