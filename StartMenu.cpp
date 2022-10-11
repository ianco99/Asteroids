#include "StartMenu.h"

void RunGame();

void RunProject()
{
	InitWindow(1024, 768, "Asteroids");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Que onda wachin", GetScreenWidth() / 2, GetScreenHeight() / 2, 12, RAYWHITE);

		EndDrawing();

		if (IsKeyDown(KEY_SPACE))
		{
			RunGame();
		}
	}

	CloseWindow();
}