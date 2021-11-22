#include <iostream>
#include "AudioLoader.h"

int main()
{
	AudioLoader loader;
	loader.loadFile("MyBlobHurts_FullMix.wav");
	loader.getAudio(0)->printInfo();
	loader.saveFile(loader.getAudio(0), "MyBlobHurts_FullMix");
	//std::cout << "Comparing files results in " << (loader.compare(0, 1) ? "same " : "different ") << "audio!" << std::endl;

	return 0;
}