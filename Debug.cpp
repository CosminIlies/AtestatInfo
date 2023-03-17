#include "Debug.h"

void Debug::Log(const char* body)
{
	std::cout << "[Log]: " << body << '\n';
}

void Debug::Warning(const char* body)
{
	std::cout << "[Warning]: " << body << '\n';
}

void Debug::Error(const char* body)
{
	std::cerr << "[Error]: " << body << '\n';
}
