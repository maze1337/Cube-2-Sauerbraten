#pragma once
#include "../Includes/Includes.h"

namespace Gui
{
	inline bool ESP;
	inline bool Aimbot;
	inline bool SilentAim;

	void Init(HWND hwnd);

	void Menu(bool &ShowMenu);
}