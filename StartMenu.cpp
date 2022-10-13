#include "StartMenu.h"

void RunGame();

Texture2D backgroundSprite;
Texture2D buttonSprite;

void RunProject()
{

	InitWindow(1024, 768, "Asteroids");

	buttonSprite = LoadTexture("textures/button.png");

	backgroundSprite = LoadTexture("textures/back.png");

	bool shouldQuit = false;

	Color btnTint = RAYWHITE;

	Rectangle startBtnBounds = { GetScreenWidth()/2 - buttonSprite.width / 2, GetScreenHeight() / 2 - buttonSprite.height / 2 + 20, buttonSprite.width, buttonSprite.height };
	//Rectangle startBtndest = { GetScreenWidth()/2 - buttonSprite.width, GetScreenHeight() / 4 - buttonSprite.height, buttonSprite.width, buttonSprite.height };

	SetExitKey(KEY_F4);

	while (!WindowShouldClose() && !shouldQuit)
	{

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);

		

		//DrawTexturePro(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, startBtnBounds, { 0,0 }, 0, RAYWHITE);

		DrawTextureRec(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, { startBtnBounds.x, startBtnBounds.y }, btnTint);
		DrawText("START", startBtnBounds.x - 15 + startBtnBounds.width / 2 , startBtnBounds.y, 12, BLACK);

		EndDrawing();

		if (CheckCollisionPointRec(GetMousePosition(), startBtnBounds))
		{
			btnTint = BLUE;

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				RunGame();
			}
		}
		else
		{
			btnTint = RAYWHITE;
		}

		if (IsKeyDown(KEY_SPACE))
		{
			
		}
		else if (IsKeyPressed(KEY_ESCAPE))
		{
			shouldQuit = true;
		}
	}

	CloseWindow();
}