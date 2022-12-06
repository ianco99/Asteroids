#include "credits_menu.h"

#include "raylib.h"

#include "start_menu.h"

float creditsFontSize = 26;
int offsetBtwnCredits = 40;

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
		float scrnWidth = static_cast<float>(GetScreenWidth());
		float scrnHeight = static_cast<float>(GetScreenHeight());

		backButton = { scrnWidth / 2.0f, scrnHeight - scrnHeight / 8.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };

		creditButtons[0].body = { static_cast<float>(scrnWidth / 2.0f - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 0).x / 2.0f), static_cast<float>(scrnHeight / 8.0f + offsetBtwnCredits * 3.0f), static_cast<float>(MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).x), static_cast<float>(MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).y )};
		creditButtons[0].link = "https://www.kenney.nl/assets/ui-pack";

		creditButtons[1].body = { scrnWidth / 2.0f - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 0).x / 2.0f, scrnHeight / 8.0f + offsetBtwnCredits * 5.0f, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).y };
		creditButtons[1].link = "https://opengameart.org/content/space-background-1";

		creditButtons[2].body = { scrnWidth / 2.0f - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 0).x / 2.0f, scrnHeight / 8.0f + offsetBtwnCredits * 7.0f, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).y };
		creditButtons[2].link = "https://www.kenney.nl/assets/space-shooter-extension";

		creditButtons[3].body = { scrnWidth / 2.0f - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 0).x / 2.0f, scrnHeight / 8.0f + offsetBtwnCredits * 9.0f, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).y };
		creditButtons[3].link = "https://www.kenney.nl/assets/sci-fi-sounds";

		creditButtons[4].body = { scrnWidth / 2.0f - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 0).x / 2.0f, scrnHeight / 8.0f + offsetBtwnCredits * 11.0f, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).y };
		creditButtons[4].link = "https://opengameart.org/content/space-music-out-there";

		backButtonCollision = { backButton.body.x - backButton.body.width / 2.0f, backButton.body.y - backButton.body.height / 2.0f , backButton.body.width, backButton.body.height };
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
		int textFont = 26;
		int scrnWidth = GetScreenWidth();
		int scrnHeight = GetScreenHeight();


		DrawText("CREDITS", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "CREDITS", static_cast<float>(textFont), 0).x / 2), scrnHeight / 10, textFont, RAYWHITE);

		DrawText("Button art by Kenney", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Button art by Kenney", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 2), textFont, RAYWHITE);

		DrawText("https://www.kenney.nl/assets/ui-pack", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 3), textFont, SKYBLUE);

		DrawText("Background art by Westbeam", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Background art by Westbeam", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8.0f + offsetBtwnCredits * 4), textFont, RAYWHITE);

		DrawText("https://opengameart.org/content/space-background-1", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 5), textFont, SKYBLUE);

		DrawText("Ship, asteroids and bullets art by Kenney", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Ship, asteroids and bullets art by Kenney", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 6), textFont, RAYWHITE);

		DrawText("https://www.kenney.nl/assets/space-shooter-extension", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 7), textFont, SKYBLUE);

		DrawText("SFX by Kenney", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "SFX by Kenney", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 8), textFont, RAYWHITE);

		DrawText("https://www.kenney.nl/assets/sci-fi-sounds", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 9), textFont, SKYBLUE);

		DrawText("Music by yd", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "Music by yd", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 10), textFont, RAYWHITE);

		DrawText("https://opengameart.org/content/space-music-out-there", static_cast<int>(scrnWidth / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", static_cast<float>(textFont), 0).x / 2), static_cast<int>(scrnHeight / 8 + offsetBtwnCredits * 11), textFont, SKYBLUE);

		DrawTextAndButton("BACK", textFont, backButton.body, true);

	}
}