#pragma once
#include <iostream>
#include <Windows.h>

#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)


namespace Console
{
	void Init();

	void Shutdown();
}
