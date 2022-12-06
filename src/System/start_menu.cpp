#include "start_menu.h"

#include "credits_menu.h"


namespace kuznickiAsteroid
{
	void InitWindowAndAudio();
	void InitButtons(Button buttons[]);
	void InitMouseCollisions(Button buttons[], Rectangle mouseCollisions[]);
	void RunGame();

	Texture2D backgroundSprite;
	Texture2D buttonSprite;

	ProgramScreen currentScreen;

	Music backgroundSong;

	int creditsFontSize = 26;
	int offsetBtwnCredits = 40;

	void RunProject()
	{

		backgroundSong.looping = true;

		Color btnTint = WHITE;

		InitWindowAndAudio();

		buttonSprite = LoadTexture("textures/button.png");
		backgroundSprite = LoadTexture("textures/back.png");
		backgroundSong = LoadMusicStream("audio/backgroundSong.ogg");

		Button buttons[4];
		InitButtons(buttons);

		InitButtonCredits();

		Rectangle mouseCollisions[4];
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

				if (CollisionPointRec(GetMousePosition(), mouseCollisions[0]))
				{
					selectedScreen = buttons[0].buttonScreen;

					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						currentScreen = selectedScreen;
					}
				}
				else if (CollisionPointRec(GetMousePosition(), mouseCollisions[1]))
				{
					selectedScreen = buttons[1].buttonScreen;

					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						currentScreen = selectedScreen;
					}
				}

				else if (IsKeyPressed(KEY_SPACE))
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
			case kuznickiAsteroid::ProgramScreen::Quit:
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

				DrawText("ASTEROIDS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "ASTEROIDS", 60, 0).x / 2, GetScreenHeight() / 10, 60, RAYWHITE);

				DrawTextAndButton(buttons[0].text, 26, buttons[0].body, true, WHITE);

				DrawTextAndButton(buttons[1].text, 26, buttons[1].body, true, WHITE);


				break;

			case kuznickiAsteroid::ProgramScreen::GameLoop:

				break;

			case kuznickiAsteroid::ProgramScreen::CreditsScreen:
				DrawCredits();
				break;

			case kuznickiAsteroid::ProgramScreen::Quit:

				break;

			default:

				break;
			}

			EndDrawing();
		}

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
		Rectangle startBtnBounds = { GetScreenWidth() / 2 , GetScreenHeight() / 3, buttonSprite.width, buttonSprite.height };
		buttons[0].body = startBtnBounds;
		buttons[0].buttonScreen = ProgramScreen::GameLoop;
		buttons[0].text = "START";
		buttons[0].link = " ";

		Rectangle creditsBtnBounds = { GetScreenWidth() / 2 , GetScreenHeight() / 2, buttonSprite.width, buttonSprite.height };
		buttons[1].body = creditsBtnBounds;
		buttons[1].buttonScreen = ProgramScreen::CreditsScreen;
		buttons[1].text = "CREDITS";
		buttons[1].link = " ";
	}

	void InitMouseCollisions(Button buttons[], Rectangle mouseCollisions[])
	{
		for (size_t i = 0; i < 4; i++)
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

	void DrawTextAndButton(const char* text, float fontSize, Rectangle button, bool shouldDrawTexture, Color color)
	{
		Rectangle spriteSource = { 0,0, static_cast<float>(buttonSprite.width),  static_cast<float>(buttonSprite.height) };
		Rectangle spriteDestination = { button.x, button.y, button.width, button.height };
		Vector2 spriteOrigin = { buttonSprite.width / 2.0f, buttonSprite.height / 2.0f };

		if (shouldDrawTexture)
			DrawTexturePro(buttonSprite, spriteSource, spriteDestination, spriteOrigin, 0.0f, WHITE);

		DrawText(text, button.x - MeasureTextEx(GetFontDefault(), text, fontSize, 0).x / 2.0f, button.y - MeasureTextEx(GetFontDefault(), text, fontSize, 0).y / 2.0f, fontSize, BLACK);

	}
};
