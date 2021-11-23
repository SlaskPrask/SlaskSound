#include "AudioEngine.h"



int main()
{
	AudioEngine engine;
	HRESULT hr;
	if (FAILED(hr = engine.initialize()))
	{
		return 1;
	}
	
	if (FAILED(hr = engine.loadData("MyBlobHurts_FullMix.sgaf")))
	{
		return 1;
	}

	if (FAILED(hr = engine.playAudio()))
	{
		return 1;
	}

	return 0;
}