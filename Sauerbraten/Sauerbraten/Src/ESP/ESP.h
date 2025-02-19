#pragma once
#include "../Includes/Includes.h"

namespace ESP
{
	void Box(Vector2 Bottom, Vector2 Top);
	void HealthBar(Vector2 Bottom, Vector2 Top, int Health);
	void Name(Vector2 Top, std::string Name);
}
