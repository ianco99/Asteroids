#pragma once
#include "raylib.h"

namespace kuznickiAsteroid
{
	enum class ProgramScreen{StartMenu, GameLoop, CreditsScreen, RulesScreen,Quit};

	struct Button
	{
		Rectangle body;
		ProgramScreen buttonScreen;
		const char* text;
		const char* link;
	};

	void RunProject();
	bool CollisionPointRec(Vector2 point, Rectangle rec);
	void DrawTextAndButton(const char* text, int fontSize, Rectangle button, bool shouldDrawTexture);
}