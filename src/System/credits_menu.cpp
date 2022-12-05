#include "credits_menu.h"

#include "raylib.h"

#include "start_menu.h"

extern int creditsFontSize = 26;
extern int offsetBtwnCredits = 40;

const int maxCreditsButtons = 5;

namespace kuznickiAsteroid
{
	extern ProgramScreen currentScreen;
	extern Texture2D buttonSprite;

	Button creditButtons[maxCreditsButtons];

	Button backButton;

	Rectangle backButtonCollision;

	void InitButtonCredits()
	{
		backButton = { GetScreenWidth() / 2.0f, GetScreenHeight() - GetScreenHeight() / 8.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };

		creditButtons[0].body = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 0).x / 2, GetScreenHeight() / 8.0f + offsetBtwnCredits * 3, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).y };
		creditButtons[0].link = "https://www.kenney.nl/assets/ui-pack";

		creditButtons[1].body = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 0).x / 2, GetScreenHeight() / 8.0f + offsetBtwnCredits * 5, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).y };
		creditButtons[1].link = "https://opengameart.org/content/space-background-1";

		creditButtons[2].body = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 0).x / 2, GetScreenHeight() / 8.0f + offsetBtwnCredits * 7, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).y };
		creditButtons[2].link = "https://www.kenney.nl/assets/space-shooter-extension";

		creditButtons[3].body = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 0).x / 2, GetScreenHeight() / 8.0f + offsetBtwnCredits * 9, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).y };
		creditButtons[3].link = "https://www.kenney.nl/assets/sci-fi-sounds";

		creditButtons[4].body = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 0).x / 2, GetScreenHeight() / 8.0f + offsetBtwnCredits * 11, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).y };
		creditButtons[4].link = "https://opengameart.org/content/space-music-out-there";

		backButtonCollision = { backButton.body.x - backButton.body.width / 2, backButton.body.y - backButton.body.height / 2 , backButton.body.width, backButton.body.height };
	}

	void ButtonCredits()
	{
		for (int i = 0; i < maxCreditsButtons; i++)
		{
			if (CollisionPointRec(GetMousePosition(), creditButtons[i].body))
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					OpenURL(creditButtons[i].link);
				}
			}
		}

		if (CollisionPointRec(GetMousePosition(), backButtonCollision))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				currentScreen = ProgramScreen::StartMenu;
			}
		}
	}

	void DrawCredits()
	{

		DrawText("CREDITS", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "CREDITS", 26, 0).x / 2, GetScreenHeight() / 10, 26, RAYWHITE);

		DrawText("Button art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Button art by Kenney", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 2, 26, RAYWHITE);

		DrawRectangleLinesEx(creditButtons[0].body, 1, GREEN);
		DrawText("https://www.kenney.nl/assets/ui-pack", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 3, 26, SKYBLUE);

		DrawText("Background art by Westbeam", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Background art by Westbeam", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 4, 26, RAYWHITE);

		DrawRectangleLinesEx(creditButtons[1].body, 1, GREEN);
		DrawText("https://opengameart.org/content/space-background-1", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 5, 26, SKYBLUE);

		DrawText("Ship, asteroids and bullets art by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Ship, asteroids and bullets art by Kenney", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 6, 26, RAYWHITE);

		DrawRectangleLinesEx(creditButtons[2].body, 1, GREEN);
		DrawText("https://www.kenney.nl/assets/space-shooter-extension", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 7, 26, SKYBLUE);

		DrawText("SFX by Kenney", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "SFX by Kenney", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 8, 26, RAYWHITE);

		DrawRectangleLinesEx(creditButtons[3].body, 1, GREEN);
		DrawText("https://www.kenney.nl/assets/sci-fi-sounds", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 9, 26, SKYBLUE);


		DrawText("Music by yd", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "Music by yd", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 10, 26, RAYWHITE);

		DrawRectangleLinesEx(creditButtons[4].body, 1, GREEN);
		DrawText("https://opengameart.org/content/space-music-out-there", GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", 26, 0).x / 2, GetScreenHeight() / 8 + offsetBtwnCredits * 11, 26, SKYBLUE);

		DrawTextAndButton("BACK", 26, backButton.body, true, WHITE);

	}
}