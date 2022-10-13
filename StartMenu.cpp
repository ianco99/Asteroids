#include "StartMenu.h"

void RunGame();
void MouseCollisions(Color& btnTint, Rectangle startBtnBounds);

Texture2D backgroundSprite;
Texture2D buttonSprite;

void RunProject()
{

	InitWindow(1024, 768, "Asteroids");

	buttonSprite = LoadTexture("textures/button.png");

	backgroundSprite = LoadTexture("textures/back.png");

	bool shouldQuit = false;

	int offsetBtwnCredits = 40;

	Color btnTint = RAYWHITE;

	Rectangle startBtnBounds = { GetScreenWidth()/2 - buttonSprite.width / 2, GetScreenHeight() / 3 - buttonSprite.height / 2 + 20, buttonSprite.width, buttonSprite.height };
	//Rectangle startBtndest = { GetScreenWidth()/2 - buttonSprite.width, GetScreenHeight() / 4 - buttonSprite.height, buttonSprite.width, buttonSprite.height };

	SetExitKey(KEY_F4);

	while (!WindowShouldClose() && !shouldQuit)
	{

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);

		DrawText("ASTEROIDS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "ASTEROIDS", 60, 0).x / 2, GetScreenHeight()/10, 60, RAYWHITE);

		//DrawTexturePro(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, startBtnBounds, { 0,0 }, 0, RAYWHITE);

		DrawTextureRec(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, { startBtnBounds.x, startBtnBounds.y }, btnTint);
		DrawText("START", startBtnBounds.x + startBtnBounds.width / 2 - MeasureTextEx(GetFontDefault(), "START", 12, 0).x, startBtnBounds.y + startBtnBounds.height / 2 - MeasureTextEx(GetFontDefault(), "START", 12, 0).y, 26, BLACK);

		DrawText("CREDITS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "CREDITS", 26, 0).x/2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 6, 26, RAYWHITE);
		DrawText("Button art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Button art by Kenney", 26, 0).x/2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight()/6 + offsetBtwnCredits + 26, 26, RAYWHITE);
		DrawText("Button art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Button art by Kenney", 26, 0).x/2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight()/6 + offsetBtwnCredits + 26, 26, RAYWHITE);
		DrawText("Ship, asteroids and bullets art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Ship, asteroids and bullets art by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight()/6 + offsetBtwnCredits*3 + 26, 26, RAYWHITE);
		DrawText("https://www.kenney.nl/assets/space-shooter-extension", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 6 + offsetBtwnCredits * 5, 26, SKYBLUE);
		EndDrawing();

		MouseCollisions(btnTint, startBtnBounds);

		if (IsKeyPressed(KEY_ESCAPE))
		{
			shouldQuit = true;
		}
	}

	CloseWindow();
}

void MouseCollisions(Color& btnTint, Rectangle startBtnBounds)
{
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


	//void OpenURL(const char* url);
}