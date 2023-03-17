#pragma once
#include <iostream>

class Debug
{

public:
	static void Log(const char* body);
	static void Warning(const char* body);
	static void Error(const char* body);
};

