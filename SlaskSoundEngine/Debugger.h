#pragma once
#ifdef _WIN32
#include <windows.h>
#include <system_error>
#endif
#include <functional>

class Logger
{
private:
	static std::function<void(const char*)> errFunc;
	static std::string parseError(HRESULT hr);
public:
	static void logError(std::string logInfo, HRESULT hr);
	static void logError(std::string logInfo, std::string err);
	static void registerLogCallback(std::function<void(const char*)> func);
};

