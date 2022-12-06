#include "rules_menu.h"

#include "raylib.h"

#include "start_menu.h"


namespace kuznickiAsteroid
{
	extern Texture2D buttonSprite;
	extern ProgramScreen currentScreen;

	Button backButtonRules;

	Rectangle backButtonRulessCollision;

	int offsetBtwnText = 60;

	void InitButtonRules()
	{
		backButtonRules = { GetScreenWidth() / 2.0f, GetScreenHeight() - GetScreenHeight() / 8.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };

		backButtonRulessCollision = { backButtonRules.body.x - backButtonRules.body.width / 2, backButtonRules.body.y - backButtonRules.body.height / 2 , backButtonRules.body.width, backButtonRules.body.height };
	}

	void ButtonRules()
	{

		if (CollisionPointRec(GetMousePosition(), backButtonRulessCollision))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = ProgramScreen::StartMenu;
			}
		}
	}

	void DrawRules()
	{
		int scrnWidth = GetScreenWidth();

		DrawText("RULES", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "RULES", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 10), 26, RAYWHITE);

		DrawText("Mouse right click to move spaceship", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Mouse right click to move spaceship", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 2), 26, WHITE);

		DrawText("Mouse left click to shoot bullets", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Mouse left click to shoot bullets", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 3), 26, WHITE);

		DrawText("Esc in GAME to pause / Left click on PAUSE button to pause", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Esc in GAME to pause / Left click on PAUSE button to pause", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 4), 26, WHITE);

		DrawText("Game is infinite, so play as much as you like/can!", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Game is infinite, so play as much as you like/can!", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 5), 26, WHITE);

		DrawText("Player has 3 lives, when crashing into an asteroid they lose 1 life", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Player has 3 lives, when crashing into an asteroid they lose 1 life", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 6), 26, WHITE);

		//DrawText("https://www.kenney.nl/assets/space-shooter-extension", scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 7, 26, SKYBLUE);

		//DrawText("SFX by Kenney", scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "SFX by Kenney", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 8, 26, RAYWHITE);

		//DrawText("https://www.kenney.nl/assets/sci-fi-sounds", scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 9, 26, SKYBLUE);

		//DrawText("Music by yd", scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Music by yd", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 10, 26, RAYWHITE);

		//DrawText("https://opengameart.org/content/space-music-out-there", scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 11, 26, SKYBLUE);

		DrawTextAndButton("BACK", 26, backButtonRules.body, true);

	}
}