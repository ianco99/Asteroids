#include "StartMenu.h"

void RunGame();
void MouseCollisions(Color& btnTint, Rectangle startBtnBounds, Rectangle buttonArtTextLinkBounds, Rectangle buttonBackgroundTextLinkBounds, Rectangle buttonShipTextLinkBounds, Rectangle buttonSfxTextLinkBounds, Rectangle buttonMusicTextLinkBounds);

Texture2D backgroundSprite;
Texture2D buttonSprite;

Music backgroundSong;

void RunProject()
{

	InitWindow(1024, 768, "Asteroids");

	InitAudioDevice();


	buttonSprite = LoadTexture("textures/button.png");

	backgroundSprite = LoadTexture("textures/back.png");

	backgroundSong = LoadMusicStream("audio/backgroundSong.ogg");

	backgroundSong.looping = true;

	bool shouldQuit = false;

	int offsetBtwnCredits = 40;

	Color btnTint = RAYWHITE;

	Rectangle startBtnBounds = { GetScreenWidth() / 2 - buttonSprite.width / 2, GetScreenHeight() / 3 - buttonSprite.height / 2 + 20, buttonSprite.width, buttonSprite.height };
	//Rectangle startBtndest = { GetScreenWidth()/2 - buttonSprite.width, GetScreenHeight() / 4 - buttonSprite.height, buttonSprite.width, buttonSprite.height };

	PlayMusicStream(backgroundSong);

	SetExitKey(KEY_F4);

	while (!WindowShouldClose() && !shouldQuit)
	{
		UpdateMusicStream(backgroundSong);

		SetMusicVolume(backgroundSong, .2f);

		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);

		DrawText("ASTEROIDS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "ASTEROIDS", 60, 0).x / 2, GetScreenHeight() / 10, 60, RAYWHITE);

		//DrawTexturePro(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, startBtnBounds, { 0,0 }, 0, RAYWHITE);

		DrawTextureRec(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, { startBtnBounds.x, startBtnBounds.y }, btnTint);
		DrawText("START", startBtnBounds.x + startBtnBounds.width / 2 - MeasureTextEx(GetFontDefault(), "START", 12, 0).x, startBtnBounds.y + startBtnBounds.height / 2 - MeasureTextEx(GetFontDefault(), "START", 12, 0).y, 26, BLACK);

		DrawText("CREDITS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "CREDITS", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 6, 26, RAYWHITE);
		DrawText("Button art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Button art by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 2, 26, RAYWHITE);
		DrawText("https://www.kenney.nl/assets/ui-pack", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 3, 26, SKYBLUE);
		DrawText("Background art by Westbeam", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Background art by Westbeam", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 4, 26, RAYWHITE);
		DrawText("https://opengameart.org/content/space-background-1", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 5, 26, SKYBLUE);
		DrawText("Ship, asteroids and bullets art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Ship, asteroids and bullets art by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 6, 26, RAYWHITE);
		DrawText("https://www.kenney.nl/assets/space-shooter-extension", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 7, 26, SKYBLUE);

		DrawText("SFX by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "SFX by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 8, 26, RAYWHITE);
		DrawText("https://www.kenney.nl/assets/sci-fi-sounds", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 9, 26, SKYBLUE);


		DrawText("Music by yd", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Music by yd", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 10 - 20, 26, RAYWHITE);
		DrawText("https://opengameart.org/content/space-music-out-there", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 11 - 6, 26, SKYBLUE);

		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			shouldQuit = true;
		}
		else if (IsKeyPressed(KEY_SPACE))
		{
			RunGame();
		}
	}

	UnloadMusicStream(backgroundSong);

	UnloadTexture(backgroundSprite);
	UnloadTexture(buttonSprite);

	CloseAudioDevice();
	CloseWindow();
}
