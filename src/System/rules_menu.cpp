#include "rules_menu.h"

#include "raylib.h"

#include "start_menu.h"


namespace kuznickiAsteroid
{
	extern Texture2D buttonSprite;
	extern ProgramScreen currentScreen;

	extern int textFontSize;

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

		DrawText("RULES", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "RULES", 26, 0).x / 2), static_cast<int>(GetScreenHeight() / 10), textFontSize, RAYWHITE);

		DrawText("Mouse right click to move spaceship", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Mouse right click to move spaceship", static_cast<float>(textFontSize), 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 2), textFontSize, WHITE);

		DrawText("Mouse left click to shoot bullets", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Mouse left click to shoot bullets", static_cast<float>(textFontSize), 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 3), textFontSize, WHITE);

		DrawText("Esc in GAME to pause / Left click on PAUSE button to pause", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Esc in GAME to pause / Left click on PAUSE button to pause", static_cast<float>(textFontSize), 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 4), textFontSize, WHITE);

		DrawText("Game is infinite, so play as much as you like/can!", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Game is infinite, so play as much as you like/can!", static_cast<float>(textFontSize), 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 5), textFontSize, WHITE);

		DrawText("Player has 3 lives, when crashing into an asteroid they lose 1 life", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Player has 3 lives, when crashing into an asteroid they lose 1 life", static_cast<float>(textFontSize), 0).x / 2), static_cast<int>(GetScreenHeight() / 8 + offsetBtwnText * 6), textFontSize, WHITE);

		DrawTextAndButton("BACK", textFontSize, backButtonRules.body, true);

	}
}