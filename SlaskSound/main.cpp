#include <iostream>
#include "AudioLoader.h"

int main()
{
	AudioLoader loader;
	loader.loadFile("MyBlobHurts_FullMix.wav");
	loader.loadFile("MyBlobHurts_FullMix.sgaf");
	
	std::cout << "Comparing files results in " << (loader.compare(0, 1) ? "same " : "different ") << "audio!" << std::endl;

	return 0;
}