#pragma once

class Helpers
{
public:
	static bool compareString(char* compare, const char* to, size_t size)
	{
		for (size_t i = 0; i < size; i++)
		{
			if (compare[i] != to[i])
				return false;
		}
		return true;
	}

	static uint16_t littleEndianToUInt16(char* data)
	{
		return (uint16_t)(data[0] | data[1] << 8);

	}

	static uint32_t littleEndianToUInt32(char* data)
	{
		return (uint32_t)(data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24);
	}
};