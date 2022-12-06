#include "start_menu.h"

#include "credits_menu.h"
#include "rules_menu.h"


namespace kuznickiAsteroid
{
	void InitWindowAndAudio();
	void InitButtons(Button buttons[]);
	void InitMouseCollisions(Button buttons[], Rectangle mouseCollisions[]);
	void RunGame();

	extern Sound bulletShootSound;
	extern Sound playerDeathSound;
	extern Sound asteroidDeathSound;

	Texture2D backgroundSprite;
	Texture2D buttonSprite;

	ProgramScreen currentScreen;

	Music backgroundSong;

	const int startMenuButtons = 4;

	const int textFontSize = 26;
	int offsetBtwnCredits = 40;

	void RunProject()
	{


		backgroundSong.looping = true;

		Color btnTint = WHITE;

		InitWindowAndAudio();

		buttonSprite = LoadTexture("resources/textures/button.png");
		backgroundSprite = LoadTexture("resources/textures/back.png");
		backgroundSong = LoadMusicStream("resources/audio/backgroundSong.ogg");

		Button buttons[startMenuButtons];
		InitButtons(buttons);

		InitButtonCredits();
		InitButtonRules();

		Rectangle mouseCollisions[startMenuButtons];
		InitMouseCollisions(buttons, mouseCollisions);


		currentScreen = ProgramScreen::StartMenu;
		ProgramScreen selectedScreen;

		bool shouldQuit = false;

		while (!WindowShouldClose() && !shouldQuit)
		{
			UpdateMusicStream(backgroundSong);

			switch (currentScreen)
			{
			case kuznickiAsteroid::ProgramScreen::StartMenu:
				if (IsKeyPressed(KEY_ESCAPE))
				{
					shouldQuit = true;
				}

				for (int i = 0; i < startMenuButtons; i++)
				{
					if (CollisionPointRec(GetMousePosition(), mouseCollisions[i]))
					{
						selectedScreen = buttons[i].buttonScreen;

						if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
						{
							currentScreen = selectedScreen;
						}
					}
				}

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

				DrawText("ASTEROIDS", static_cast<int>(GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "ASTEROIDS", 60, 0).x / 2), static_cast<int>(GetScreenHeight() / 10), 60, RAYWHITE);

				for (int i = 0; i < startMenuButtons; i++)
				{
					DrawTextAndButton(buttons[i].text, textFontSize, buttons[i].body, true);
				}

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

	void InitButtons(Button buttons[])
	{
		Rectangle startBtnBounds = { static_cast<float>(GetScreenWidth()) / 2.0f , static_cast<float>(GetScreenHeight()) / 3.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };
		buttons[0].body = startBtnBounds;
		buttons[0].buttonScreen = ProgramScreen::GameLoop;
		buttons[0].text = "START";
		buttons[0].link = " ";

		Rectangle creditsBtnBounds = { static_cast<float>(GetScreenWidth()) / 2.0f , static_cast<float>(GetScreenHeight()) / 2.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };
		buttons[1].body = creditsBtnBounds;
		buttons[1].buttonScreen = ProgramScreen::CreditsScreen;
		buttons[1].text = "CREDITS";
		buttons[1].link = " ";

		Rectangle rulesBtnBounds = { static_cast<float>(GetScreenWidth() / 2.0f), static_cast<float>(GetScreenHeight() - GetScreenHeight() / 3.0f), static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };
		buttons[2].body = rulesBtnBounds;
		buttons[2].buttonScreen = ProgramScreen::RulesScreen;
		buttons[2].text = "RULES";
		buttons[2].link = " ";

		Rectangle quitBtnBounds = { static_cast<float>(GetScreenWidth() / 2.0f), static_cast<float>(GetScreenHeight() - GetScreenHeight() / 8.0f), static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };
		buttons[3].body = quitBtnBounds;
		buttons[3].buttonScreen = ProgramScreen::Quit;
		buttons[3].text = "QUIT";
		buttons[3].link = " ";
	}

	void InitMouseCollisions(Button buttons[], Rectangle mouseCollisions[])
	{
		for (size_t i = 0; i < startMenuButtons; i++)
		{
			mouseCollisions[i] = { buttons[i].body.x - buttons[i].body.width / 2, buttons[i].body.y - buttons[i].body.height / 2 ,buttons[i].body.width, buttons[i].body.height };
		}
	}

	bool CollisionPointRec(Vector2 point, Rectangle rec)
	{
		if (point.x >= rec.x &&
			point.x <= rec.x + rec.width &&
			point.y >= rec.y &&
			point.y <= rec.y + rec.height)
		{
			return true;
		}

		return false;
	}

	void DrawTextAndButton(const char* text, int fontSize, Rectangle button, bool shouldDrawTexture)
	{
		Rectangle spriteSource = { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) };
		Rectangle spriteDestination = { button.x, button.y, button.width, button.height };
		Vector2 spriteOrigin = { buttonSprite.width / 2.0f, buttonSprite.height / 2.0f };

		if (shouldDrawTexture)
			DrawTexturePro(buttonSprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);

		DrawText(text, static_cast<int>(button.x - MeasureTextEx(GetFontDefault(), text, static_cast<float>(fontSize), 0).x / 2.0f), static_cast<int>(button.y - MeasureTextEx(GetFontDefault(), text, static_cast<float>(fontSize), 0).y / 2.0f), fontSize, BLACK);

	}
};
