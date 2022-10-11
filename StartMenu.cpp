#include "StartMenu.h"

void RunGame();

Texture2D backgroundSprite;

void RunProject()
{
	InitWindow(1024, 768, "Asteroids");

	backgroundSprite = LoadTexture("textures/back.png");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);

		DrawText("Que onda wachin", GetScreenWidth() / 2, GetScreenHeight() / 2, 12, RAYWHITE);

		EndDrawing();

		if (IsKeyDown(KEY_SPACE))
		{
			RunGame();
		}
	}

	CloseWindow();
}