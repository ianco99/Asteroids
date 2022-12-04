#include "start_menu.h"

namespace kuznickiAsteroid
{
	void DrawTextAndButton(const char* text, float fontSize, Rectangle button, Texture2D buttonSprite, bool shouldDrawTexture, Color color);
	void RunGame();
	void MouseCollisions(Color& btnTint, Rectangle startBtnBounds, Rectangle buttonArtTextLinkBounds, Rectangle buttonBackgroundTextLinkBounds, Rectangle buttonShipTextLinkBounds, Rectangle buttonSfxTextLinkBounds, Rectangle buttonMusicTextLinkBounds);

	Texture2D backgroundSprite;

	ProgramScreen currentScreen;

	Music backgroundSong;

	void RunProject()
	{
		Texture2D buttonSprite;

		int offsetBtwnCredits = 40;
		int creditsFontSize = 26;
		bool shouldQuit = false;

		InitWindow(1024, 768, "Asteroids");
		InitAudioDevice();


		buttonSprite = LoadTexture("textures/button.png");
		backgroundSprite = LoadTexture("textures/back.png");

		backgroundSong = LoadMusicStream("audio/backgroundSong.ogg");
		backgroundSong.looping = true;



		Color btnTint = WHITE;

		Rectangle startBtnBounds = { GetScreenWidth() / 2 , GetScreenHeight() / 3, buttonSprite.width, buttonSprite.height };

		PlayMusicStream(backgroundSong);

		SetExitKey(KEY_F4);

		currentScreen = ProgramScreen::StartMenu;

		while (!WindowShouldClose() && !shouldQuit)
		{
			UpdateMusicStream(backgroundSong);

			SetMusicVolume(backgroundSong, .2f);

			switch (currentScreen)
			{
				BeginDrawing();

				ClearBackground(BLACK);

				DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);

				DrawText("ASTEROIDS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "ASTEROIDS", 60, 0).x / 2, GetScreenHeight() / 10, 60, RAYWHITE);

				//DrawTexturePro(buttonSprite, { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) }, startBtnBounds, { 0,0 }, 0, RAYWHITE);

				DrawTextAndButton("START", 26, startBtnBounds, buttonSprite, true, WHITE);

				EndDrawing();
				break;

			case kuznickiAsteroid::ProgramScreen::StartMenu:
				
				break;

			case kuznickiAsteroid::ProgramScreen::GameLoop:
				
				break;

			case kuznickiAsteroid::ProgramScreen::CreditsScreen:
				
				break;

			case kuznickiAsteroid::ProgramScreen::Quit:
				
				break;

			default:
				
				break;
			}




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
