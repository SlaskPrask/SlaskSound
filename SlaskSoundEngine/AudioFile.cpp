#include "AudioFile.h"

bool AudioFile::readFormatInfo(HANDLE hFile, uint32_t &dataSize, DWORD *readBytes)
{
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
	{
		Logger::logError("Setting file pointer for FMT", HRESULT_FROM_WIN32(GetLastError()));
		return false;
	}
	
	FormatInfo fmt = { 0 };
	if (0 == ReadFile(hFile, &fmt, sizeof(fmt), readBytes, NULL))
	{
		Logger::logError("Reading FMT", HRESULT_FROM_WIN32(GetLastError()));
		return false;
	}

	wfx.Format.wFormatTag = fmt.formatTag;
	wfx.Format.nChannels = fmt.numChannels;
	wfx.Format.nSamplesPerSec = fmt.sampleRate;
	wfx.Format.nBlockAlign = fmt.blockAllign;
	wfx.Format.wBitsPerSample = fmt.bitsPerSample;
	//can be calculated using (number of channels * samplesPerSec * bitsPerSample / 8)
	wfx.Format.nAvgBytesPerSec = fmt.numChannels * fmt.sampleRate * fmt.bitsPerSample / 8;
	//size is dependant on some stuff, test file is always 18 so
	wfx.Format.cbSize = 18;

	dataSize = fmt.dataSize;
	return true;
}

bool AudioFile::readDataToBuffer(HANDLE hFile, uint32_t dataSize, DWORD* readBytes)
{
	//populate the audio buffer
	BYTE* pDataBuffer = new BYTE[dataSize];

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, *readBytes, NULL, FILE_BEGIN))
	{
		Logger::logError("Setting file pointer for data", HRESULT_FROM_WIN32(GetLastError()));
		return false;
	}

	if (0 == ReadFile(hFile, pDataBuffer, dataSize, readBytes, NULL))
	{
		Logger::logError("Reading Data", HRESULT_FROM_WIN32(GetLastError()));
		return false;
	}

	buffer.AudioBytes = dataSize;
	buffer.pAudioData = pDataBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	return true;
}

AudioFile::AudioFile(std::string path, IXAudio2* pXAudio2)
{
	wfx = { 0 };
	buffer = { 0 };

	std::wstring str(path.begin(), path.end());
	HANDLE hFile = CreateFile(str.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		Logger::logError("Invalid file handle", HRESULT_FROM_WIN32(GetLastError()));
		return;
	}
	
	DWORD dwRead;
	uint32_t dataSize;
	if (!readFormatInfo(hFile, dataSize, &dwRead))
		return;

	if (!readDataToBuffer(hFile, dataSize, &dwRead))
		return;

	HRESULT hr;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx)))
	{
		Logger::logError("Creating Source Voice", hr);
		return;
	}

	if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer)))
	{
		Logger::logError("Submitting buffer", hr);
		return;
	}
}


void AudioFile::play()
{
	HRESULT hr;

	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		Logger::logError("Starting audio", hr);
		return;
	}
}

void AudioFile::stop()
{
	pSourceVoice->Stop(0);
}

AudioFile::~AudioFile()
{
	if (pSourceVoice != nullptr)
	{
		pSourceVoice->Stop();
		pSourceVoice->DestroyVoice();
	}
	delete[] buffer.pAudioData;
}
