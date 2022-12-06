#pragma once
#include "raylib.h"

#include "core_loop.h"

namespace kuznickiAsteroid
{
	struct Button
	{
		Rectangle body;
		ProgramScreen buttonScreen;
		const char* text;
		const char* link;
	};

	void StartButtons();
	void InitButtonsStart();
	bool CollisionPointRec(Vector2 point, Rectangle rec);
	void DrawStart();
	void DrawTextAndButton(const char* text, int fontSize, Rectangle button, bool shouldDrawTexture);
}