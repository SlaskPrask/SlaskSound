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
};