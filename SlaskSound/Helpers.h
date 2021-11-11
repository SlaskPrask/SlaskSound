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
		return (uint16_t)(
			(data[0] & 0xff) | 
			(data[1] & 0xff) << 8);
	}
	

	static uint32_t littleEndianToUInt32(char* data)
	{
		return (uint32_t)(
			(data[0] & 0xff) | 
			(data[1] & 0xff) << 8 |
			(data[2] & 0xff) << 16 |
			(data[3] & 0xff) << 24);
	}

	static float littleEndianToFloat(char* data)
	{
		float retVal;
		char* returnFloat = (char*)&retVal;
		returnFloat[0] = data[3];
		returnFloat[1] = data[2];
		returnFloat[2] = data[1];
		returnFloat[3] = data[0];
		return retVal;
	}
};