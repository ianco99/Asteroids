#pragma once
#include "raylib.h"

namespace kuznickiAsteroid
{
	enum class ProgramScreen{StartMenu, GameLoop, CreditsScreen, Quit};

	struct Button
	{
		Rectangle body;
		ProgramScreen buttonScreen;
		const char* text;
		const char* link;
	};

	void RunProject();
}