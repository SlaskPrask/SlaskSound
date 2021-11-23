#include "Debugger.h"

std::string Logger::parseError(HRESULT hr)
{
	return std::system_category().message(hr);
}

void Logger::logError(std::string logInfo, HRESULT hr)
{
	if (errFunc != nullptr)
	{
		errFunc((logInfo + ": " + parseError(hr)).c_str());
	}
}

void Logger::logError(std::string logInfo, std::string err)
{
	if (errFunc != nullptr)
	{
		errFunc((logInfo + ": " + err).c_str());
	}
}

void Logger::registerLogCallback(std::function<void(const char*)> func)
{
	errFunc = func;
}

std::function<void(const char*)> Logger::errFunc = nullptr;

