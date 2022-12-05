#include "credits_menu.h"

#include "raylib.h"

extern int creditsFontSize = 26;
extern int offsetBtwnCredits = 40;

void DrawCredits()
{
	Rectangle buttonCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 3, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/ui-pack", creditsFontSize, 2).y };
	Rectangle backgroundCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 5, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-background-1", creditsFontSize, 2).y };
	Rectangle gameAssetsCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 7, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/space-shooter-extension", creditsFontSize, 2).y };
	Rectangle sfxCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 9, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://www.kenney.nl/assets/sci-fi-sounds", creditsFontSize, 2).y };
	Rectangle musicCreditsTextBounds = { GetScreenWidth() / 2 - MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 0).x / 2, GetScreenHeight() - GetScreenHeight() / 3 - GetScreenHeight() / 4 + offsetBtwnCredits * 11 - 6, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).x, MeasureTextEx(GetFontDefault(), "https://opengameart.org/content/space-music-out-there", creditsFontSize, 2).y };

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

}