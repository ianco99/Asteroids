﻿#include "game_loop.h"
#include "raylib.h"
#include "raymath.h"
#include "bullet.h"
#include "asteroid.h"
#include "System/start_menu.h"

namespace kuznickiAsteroid
{
	int maxAsteroids = 60;
	int screenOffset = 5;
	int initialAsteroids = 5;

	extern Music backgroundSong;

	extern Texture2D backgroundSprite;
	extern Texture2D buttonSprite;

	extern Sound bulletShootSound;
	
	Player player;

	Asteroid asteroids[60];

	Texture2D asteroidSprite;
	Texture2D bulletSprite;

	Sound playerDeathSound;
	Sound asteroidDeathSound;

	Button pauseButton;

	void InitSounds();
	void InitGame();
	void DrawUserInterface();

	void InitSounds()
	{
		playerDeathSound = LoadSound("audio/shipDeath.ogg");
		asteroidDeathSound = LoadSound("audio/bulletShoot.ogg");

		SetSoundVolume(playerDeathSound, .03f);
		SetSoundVolume(asteroidDeathSound, .04f);
	}

	void InitGame()
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

		asteroidSprite = LoadTexture("textures/asteroid.png");

		pauseButton.body = { GetScreenWidth() / 2.0f, 30.0f, static_cast<float>(buttonSprite.width), static_cast<float>(buttonSprite.height) };
		pauseButton.text = "| |";
		pauseButton.buttonScreen = ProgramScreen::StartMenu;
	}

	void RunGame()
	{
		bool playing = true;

		bulletSprite = LoadTexture("textures/bullets.png");

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
				break;

			case GameEndConditions::Pause:
				BeginDrawing();
				DrawText("You are in pause, press Y to quit to menu or N to resume playing.", GetScreenWidth() / 2.0f - MeasureTextEx(GetFontDefault(),"You are in pause, press Y to quit to menu or N to resume playing.",26, 2).x / 2.0f, GetScreenHeight() / 4, 22, RAYWHITE);
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
				playing = false;
				break;

			default:
				break;
			}
		}

		UnloadTexture(player.shipSprite);
		UnloadTexture(player.bullets->sprite);
		UnloadTexture(asteroidSprite);

		UnloadSound(playerDeathSound);
		UnloadSound(asteroidDeathSound);
		UnloadSound(bulletShootSound);
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
		DrawTextAndButton(pauseButton.text, 26, pauseButton.body, true, WHITE);
		EndDrawing();
	}

	void DrawUserInterface()
	{
		if (player.score == 0)
		{
			DrawText("000000", 0, 0, 40, RAYWHITE);
		}
		else if (player.score < 999)
		{
			DrawText(TextFormat("000%2i", player.score), 0, 0, 40, RAYWHITE);
		}
		else if (player.score < 9999)
		{
			DrawText(TextFormat("00%2i", player.score), 0, 0, 40, RAYWHITE);
		}
		else if (player.score < 99999)
		{
			DrawText(TextFormat("0%2i", player.score), 0, 0, 40, RAYWHITE);
		}
		else
		{
			DrawText(TextFormat("%2i", player.score), 0, 0, 40, RAYWHITE);
		}
	}
}