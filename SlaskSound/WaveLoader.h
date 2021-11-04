#include <iostream>
#include <string>
#include <fstream>
#include "Helpers.h"

#pragma once

class WaveLoader
{
private:
	bool validateWaveFormat(std::ifstream* waveFile);
	void parseChunks(std::ifstream* waveFile);
	char checkHeader(char* header);
public:
	WaveLoader(std::string filePath);
};

