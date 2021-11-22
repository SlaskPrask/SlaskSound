#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
#ifdef _WIN32
	pXAudio2 = nullptr;
	pMasterVoice = nullptr;
	pSourceVoice = nullptr;
	wfx = { 0 };
	buffer = { 0 };
#endif
}

AudioEngine::~AudioEngine()
{
#ifdef _WIN32
	if (pSourceVoice != nullptr)
	{
		pSourceVoice->Stop(0);
		pSourceVoice->DestroyVoice();
	}
	pMasterVoice->DestroyVoice();
	pXAudio2->Release();
	delete[] buffer.pAudioData;
#endif
}

#ifdef _WIN32
HRESULT AudioEngine::initialize()
{
	//initialize xaudio2
	HRESULT hr;

	if (FAILED(hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
		return hr;
	
	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		return hr;

	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
		return hr;

	return S_OK;
}
#endif

HRESULT AudioEngine::loadData(std::string path)
{
	std::wstring str(path.begin(), path.end());
	HANDLE hFile = CreateFile(str.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return S_FALSE;
	}

	FormatInfo f = { 0 };

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwRead;
	if (0 == ReadFile(hFile, &f, sizeof(f), &dwRead, NULL))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	/*std::cout << "Format Tag: " << f.formatTag << std::endl <<
		"Number of Channels: " << f.numChannels << std::endl <<
		"Sample Rate: " << f.sampleRate << std::endl <<
		"Bits per Sample: " << f.bitsPerSample << std::endl <<
		"Block Allign: " << f.blockAllign << std::endl <<
		"Data Size: " << f.dataSize << std::endl;*/

	wfx.Format.wFormatTag = f.formatTag;
	wfx.Format.nChannels = f.numChannels;
	wfx.Format.nSamplesPerSec = f.sampleRate;
	wfx.Format.nBlockAlign = f.blockAllign;
	wfx.Format.wBitsPerSample = f.bitsPerSample;
	//can be calculated using (number of channels * samplesPerSec * bitsPerSample / 8)
	wfx.Format.nAvgBytesPerSec = f.numChannels * f.sampleRate * f.bitsPerSample / 8;
	//size is dependant on some stuff, test file is always 18 so
	wfx.Format.cbSize = 18;

	//populate the audio buffer
	BYTE* pDataBuffer = new BYTE[f.dataSize];

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwRead, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	if (0 == ReadFile(hFile, pDataBuffer, f.dataSize, &dwRead, NULL))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	buffer.AudioBytes = f.dataSize;
	buffer.pAudioData = pDataBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	return S_OK;
}

HRESULT AudioEngine::playAudio()
{
	HRESULT hr;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx)))
	{
		return hr;
	}

	if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer)))
	{
		return hr;
	}

	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		return hr;
	}

	return S_OK;
}

HRESULT AudioEngine::stopAudio()
{
	if (pSourceVoice != nullptr)
	{
		pSourceVoice->Stop(0);
		pSourceVoice->DestroyVoice();
		pSourceVoice = nullptr;
	}
	return S_OK;
}