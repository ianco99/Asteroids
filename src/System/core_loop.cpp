#include "start_menu.h"

#include "credits_menu.h"
#include "rules_menu.h"
#include "GameElements/game_loop.h"

namespace kuznickiAsteroid
{
	static void InitWindowAndAudio();

	extern Sound bulletShootSound;
	extern Sound playerDeathSound;
	extern Sound asteroidDeathSound;

	Texture2D backgroundSprite;
	Texture2D buttonSprite;

	ProgramScreen currentScreen;
	ProgramScreen selectedScreen;

	Music backgroundSong;

	void RunProject()
	{
		backgroundSong.looping = true;

		InitWindowAndAudio();

		buttonSprite = LoadTexture("resources/textures/button.png");
		backgroundSprite = LoadTexture("resources/textures/back.png");
		backgroundSong = LoadMusicStream("resources/audio/backgroundSong.ogg");

		InitButtonsStart();
		InitButtonCredits();
		InitButtonRules();

		currentScreen = ProgramScreen::StartMenu;


		bool shouldQuit = false;

		while (!shouldQuit)
		{
			UpdateMusicStream(backgroundSong);

			switch (currentScreen)
			{
			case kuznickiAsteroid::ProgramScreen::StartMenu:
				if (IsKeyPressed(KEY_ESCAPE))
				{
					shouldQuit = true;
				}

				StartButtons();

				if (IsKeyPressed(KEY_SPACE))
				{
					currentScreen = ProgramScreen::GameLoop;
				}
				else if (IsKeyPressed(KEY_F))
				{
					currentScreen = ProgramScreen::CreditsScreen;
				}
				break;
			case kuznickiAsteroid::ProgramScreen::GameLoop:
				RunGame();
				currentScreen = ProgramScreen::StartMenu;
				break;
			case kuznickiAsteroid::ProgramScreen::CreditsScreen:
				ButtonCredits();
				break;
			case kuznickiAsteroid::ProgramScreen::RulesScreen:
				ButtonRules();
				break;
			case kuznickiAsteroid::ProgramScreen::Quit:
				shouldQuit = true;
				break;
			default:
				break;
			}

			BeginDrawing();

			ClearBackground(BLACK);

			DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);

			switch (currentScreen)
			{

			case kuznickiAsteroid::ProgramScreen::StartMenu:
				DrawStart();
				break;

			case kuznickiAsteroid::ProgramScreen::CreditsScreen:
				DrawCredits();
				break;
			case kuznickiAsteroid::ProgramScreen::RulesScreen:
				DrawRules();
				break;
			default:

				break;
			}

			EndDrawing();
		}

		UnloadSound(playerDeathSound);
		UnloadSound(asteroidDeathSound);
		UnloadSound(bulletShootSound);
		UnloadMusicStream(backgroundSong);

		UnloadTexture(backgroundSprite);
		UnloadTexture(buttonSprite);

		CloseAudioDevice();
		CloseWindow();
	}

	void InitWindowAndAudio()
	{
		InitWindow(1024, 768, "Asteroids");
		SetExitKey(KEY_F4);
		InitAudioDevice();
		PlayMusicStream(backgroundSong);
		SetMusicVolume(backgroundSong, .2f);
	}
};
