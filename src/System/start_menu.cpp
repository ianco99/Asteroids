#include "start_menu.h"

namespace kuznickiAsteroid
{
	void DrawTextAndButton(const char* text, float fontSize, Rectangle button, Texture2D buttonSprite, bool shouldDrawTexture, Color color);
	void RunGame();
	void MouseCollisions(Color& btnTint, Rectangle startBtnBounds, Rectangle buttonArtTextLinkBounds, Rectangle buttonBackgroundTextLinkBounds, Rectangle buttonShipTextLinkBounds, Rectangle buttonSfxTextLinkBounds, Rectangle buttonMusicTextLinkBounds);

	Texture2D backgroundSprite;


	Music backgroundSong;

	void RunProject()
	{
		Texture2D buttonSprite;

		InitWindow(1024, 768, "Asteroids");


		InitAudioDevice();


		buttonSprite = LoadTexture("textures/button.png");

		backgroundSprite = LoadTexture("textures/back.png");

		backgroundSong = LoadMusicStream("audio/backgroundSong.ogg");

		backgroundSong.looping = true;

		bool shouldQuit = false;

		int offsetBtwnCredits = 40;
		int creditsFontSize = 26;

		Color btnTint = WHITE;

		Rectangle startBtnBounds = { GetScreenWidth() / 2 , GetScreenHeight() / 3, buttonSprite.width, buttonSprite.height };
		Rectangle buttonCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 3, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).y };
		Rectangle backgroundCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 5, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).y };
		Rectangle gameAssetsCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 7, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).y };
		Rectangle sfxCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 9, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).y };
		Rectangle musicCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 11 - 6, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).y };
		//Rectangle startBtndest = { GetScreenWidth()/2 - buttonSprite.width, GetScreenHeight() / 4 - buttonSprite.height, buttonSprite.width, buttonSprite.height };
		//GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", 26, 0).x / 2
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

			DrawTextAndButton("START", 26, startBtnBounds, buttonSprite, true, WHITE);

			DrawText("CREDITS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "CREDITS", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 6, 26, RAYWHITE);

			DrawText("Button art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Button art by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 2, 26, RAYWHITE);


			DrawRectangleLinesEx(buttonCreditsTextBounds, 1, GREEN);
			DrawText("https://www.kenney.nl/assets/ui-pack", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 3, 26, SKYBLUE);

			DrawText("Background art by Westbeam", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Background art by Westbeam", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 4, 26, RAYWHITE);
			
			DrawRectangleLinesEx(backgroundCreditsTextBounds, 1, GREEN);
			DrawText("https://opengameart.org/content/space-background-1", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 5, 26, SKYBLUE);

			DrawText("Ship, asteroids and bullets art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Ship, asteroids and bullets art by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 6, 26, RAYWHITE);
			
			DrawRectangleLinesEx(gameAssetsCreditsTextBounds, 1, GREEN);
			DrawText("https://www.kenney.nl/assets/space-shooter-extension", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 7, 26, SKYBLUE);

			DrawText("SFX by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "SFX by Kenney", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 8, 26, RAYWHITE);

			DrawRectangleLinesEx(sfxCreditsTextBounds, 1, GREEN);
			DrawText("https://www.kenney.nl/assets/sci-fi-sounds", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 9, 26, SKYBLUE);


			DrawText("Music by yd", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Music by yd", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 10 - 20, 26, RAYWHITE);
			
			DrawRectangleLinesEx(musicCreditsTextBounds, 1, GREEN);
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

	void DrawTextAndButton(const char* text, float fontSize, Rectangle button, Texture2D buttonSprite, bool shouldDrawTexture, Color color)
	{
		Rectangle spriteSource = { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) };
		Rectangle spriteDestination = { button.x, button.y, button.width, button.height };
		Vector2 spriteOrigin = { buttonSprite.width / 2.0f, buttonSprite.height / 2.0f };

		if (shouldDrawTexture)
			DrawTexturePro(buttonSprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);

		DrawText(text, button.x - MeasureTextEx(GetFontDefault(), text, fontSize, 0).x / 2.0f, button.y - MeasureTextEx(GetFontDefault(), text, fontSize, 0).y / 2.0f, fontSize, BLACK);

		//DrawText("https://www.kenney.nl/assets/ui-pack", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", 26, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 3, 26, SKYBLUE);

		//DrawText(TextFormat(Button[i].text), static_cast<int>(Button[i].body.x + Button[i].body.width / 2 - MeasureTextEx(GetFontDefault(), Button[i].text, 42, 0).x / 2), static_cast<int>(Button[i].body.y + MeasureTextEx(GetFontDefault(), Button[i].text, 42, 0).y / 2), 42, WHITE);

	}
};
