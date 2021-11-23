#pragma once
#include <iostream>
struct FormatInfo
{
	/*
		FormatTag			uint16
		NumberOfChannels	uint16
		SampleRate			uint32
		BitsPerSample		uint16
		BlockAllign			uint16
		DataSize			uint32
	*/
	uint16_t formatTag;
	uint16_t numChannels;
	uint32_t sampleRate;
	uint16_t bitsPerSample;
	uint16_t blockAllign;
	uint32_t dataSize;

	inline bool operator==(const FormatInfo& lhs)
	{
		return lhs.formatTag == formatTag &&
			lhs.numChannels == numChannels &&
			lhs.sampleRate == sampleRate &&
			lhs.bitsPerSample == bitsPerSample &&
			lhs.blockAllign == blockAllign;
	}
};