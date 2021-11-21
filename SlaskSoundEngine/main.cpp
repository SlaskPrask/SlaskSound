#include "AudioEngine.h"

int main()
{
	AudioEngine engine;
	HRESULT hr;
	if (FAILED(hr = engine.initialize()))
	{
		std::cout << "Initialization failed: " << hr << std::endl;
	}

	return 0;
}