#include "game_loop.h"

#include <iostream>

#include "raylib.h"
#include "raymath.h"

#include "GameElements/player.h"
#include "GameElements/asteroid.h"
#include "start_menu.h"

namespace kuznickiAsteroid
{
	extern Music backgroundSong;

	extern Texture2D backgroundSprite;
	extern Texture2D buttonSprite;

	extern Sound bulletShootSound;

	extern int textFontSize = 26;

	Player player;

	Asteroid asteroids[60];

	static Texture2D asteroidSprite;
	Texture2D bulletSprite;

	Sound playerDeathSound;
	Sound asteroidDeathSound;

	static Button pauseButton;

	int screenOffset = 5;
	static const int initialAsteroids = 5;
	int maxAsteroids = 60;
	const int maxBullets = 50;
	static const float respawnTime = 5.0f;
	static float currentRespawnTime = 0.0f;

	bool isRespawning = false;

	static void InitSounds();
	static void InitGame();
	static void DrawUserInterface();

	static void InitSounds()
	{
		playerDeathSound = LoadSound("resources/audio/shipDeath.ogg");
		asteroidDeathSound = LoadSound("resources/audio/bulletShoot.ogg");

		SetSoundVolume(playerDeathSound, 0.03f);
		SetSoundVolume(asteroidDeathSound, 0.04f);
	}

	static void InitGame()
	{
		player = GeneratePlayer();
		for (int i = 0; i < maxAsteroids; i++)
		{
			asteroids[i].isAlive = false;
			asteroids[i].direction = { 0,0 };
			asteroids[i].radiusSize = AsteroidRadiusSize::Big;
			asteroids[i].speed = { 0,0 };
		}

		for (int i = 0; i < initialAsteroids; i++)
		{
			asteroids[i] = CreateAsteroid(i, AsteroidRadiusSize::Big);
		}

		asteroidSprite = LoadTexture("resources/textures/asteroid.png");

		pauseButton.body = { GetScreenWidth() / 2.0f, 30.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };
		pauseButton.text = "| |";
		pauseButton.buttonScreen = ProgramScreen::StartMenu;
	}

	void RunGame()
	{
		bool playing = true;

		bulletSprite = LoadTexture("resources/textures/bullets.png");

		InitSounds();
		InitGame();

		GameEndConditions condition = GameEndConditions::Game;


		while (playing)
		{
			UpdateMusicStream(backgroundSong);
			switch (condition)
			{
			case GameEndConditions::Game:
				Update();
				condition = CheckGameEndConditions();

				if (isRespawning)
					currentRespawnTime += GetFrameTime();

				if (currentRespawnTime >= respawnTime)
				{
					player.color = WHITE;
					player.isAlive = true;
					isRespawning = false;
					currentRespawnTime = 0.0f;
				}
				break;

			case GameEndConditions::Pause:
				BeginDrawing();
				DrawText("You are in pause, press Y to quit to menu or N to resume playing.", static_cast<int>(GetScreenWidth() / 2.0f - MeasureTextEx(GetFontDefault(), "You are in pause, press Y to quit to menu or N to resume playing.", static_cast<float>(textFontSize), 2).x / 2.0f), static_cast<int>(GetScreenHeight() / 4.0f), textFontSize, WHITE);
				EndDrawing();

				if (IsKeyPressed(KEY_Y))
				{
					playing = false;
				}
				else if (IsKeyPressed(KEY_N))
				{
					condition = GameEndConditions::Game;
				}
				break;

			case GameEndConditions::Lose:

				BeginDrawing();
				DrawText(TextFormat("You lost! Your final score was %2i", player.score), static_cast<int>(GetScreenWidth() / 2.0f - MeasureTextEx(GetFontDefault(), TextFormat("You lost! Your final score was %2i", player.score), static_cast<float>(textFontSize), 2).x / 2.0f), static_cast<int>(GetScreenHeight() / 4), textFontSize, RAYWHITE);
				DrawText("Press space to go back to main menu", static_cast<int>(GetScreenWidth() / 2.0f - MeasureTextEx(GetFontDefault(), "Press space to go back to main menu", static_cast<float>(textFontSize), 2).x / 2.0f), static_cast<int>(GetScreenHeight() / 4.0f + 40.0f), textFontSize, WHITE);
				EndDrawing();

				if (IsKeyPressed(KEY_SPACE))
				{
					playing = false;
				}

				break;
			default:

				break;
			}
		}

		UnloadTexture(player.shipSprite);
		UnloadTexture(player.bullets->sprite);
		UnloadTexture(asteroidSprite);

	}


	void Update()
	{
		UpdatePlayer();
		UpdateAsteroids();
		Draw();
	}

	GameEndConditions CheckGameEndConditions()
	{
		if (player.lives <= 0)
		{
			return GameEndConditions::Lose;
		}
		else if (IsKeyPressed(KEY_ESCAPE))
		{
			return GameEndConditions::Pause;
		}
		else if (CollisionPointRec(GetMousePosition(), { pauseButton.body.x - pauseButton.body.width / 2, pauseButton.body.y - pauseButton.body.height / 2 , pauseButton.body.width, pauseButton.body.height }))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				return GameEndConditions::Pause;
		}
		else
		{
			return GameEndConditions::Game;
		}
		return GameEndConditions::Game;
	}

	void Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(backgroundSprite, { static_cast<float>(0),static_cast<float>(0),static_cast<float>(backgroundSprite.width), static_cast<float>(backgroundSprite.height) }, { 0,0,static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) }, { 0,0 }, 0, RAYWHITE);
		DrawPlayer();
		DrawBullets(player.bullets);
		DrawAsteroid(asteroidSprite);
		DrawUserInterface();
		DrawTextAndButton(pauseButton.text, textFontSize, pauseButton.body, true);
		EndDrawing();
	}

	static void DrawUserInterface()
	{
		int scoreFontSize = 40;

		if (player.score == 0)
		{
			DrawText("000000", 0, 0, 40, RAYWHITE);
		}
		else if (player.score < 999)
		{
			DrawText(TextFormat("000%2i", player.score), 0, 0, scoreFontSize, RAYWHITE);
		}
		else if (player.score < 9999)
		{
			DrawText(TextFormat("00%2i", player.score), 0, 0, scoreFontSize, RAYWHITE);
		}
		else if (player.score < 99999)
		{
			DrawText(TextFormat("0%2i", player.score), 0, 0, scoreFontSize, RAYWHITE);
		}
		else
		{
			DrawText(TextFormat("%2i", player.score), 0, 0, scoreFontSize, RAYWHITE);
		}
	}
}