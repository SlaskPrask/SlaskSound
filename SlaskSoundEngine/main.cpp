#include "AudioEngine.h"
#include <system_error>

void printError(std::string data, HRESULT hr)
{
	std::cout << data << ": ErrorCode: " << std::hex << "0x" << hr << "\n" << std::system_category().message(hr) << std::endl;
}

int main()
{
	AudioEngine engine;
	HRESULT hr;
	if (FAILED(hr = engine.initialize()))
	{
		printError("Initialization failed", hr);
		return 1;
	}
	
	if (FAILED(hr = engine.loadData("MyBlobHurts_FullMix.sgaf")))
	{
		printError("Loading failed", hr);
		return 1;
	}

	if (FAILED(hr = engine.playAudio()))
	{
		printError("Playing failed", hr);
		return 1;
	}

	return 0;
}