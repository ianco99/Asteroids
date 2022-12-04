#include "game_loop.h"
#include "raylib.h"
#include "raymath.h"
#include "bullet.h"
#include "asteroid.h"

namespace kuznickiAsteroid
{
	int maxAsteroids = 60;
	int screenOffset = 5;
	int initialAsteroids = 5;

	Player player;

	Asteroid asteroids[60];

	Texture2D bulletSprite;

	Sound playerDeathSound;
	Sound asteroidDeathSound;

	extern Music backgroundSong;

	extern Texture2D backgroundSprite;

	void DrawUserInterface();

	void RunGame()
	{
		bool playing = true;

		player = GeneratePlayer();

		playerDeathSound = LoadSound("audio/shipDeath.ogg");
		asteroidDeathSound = LoadSound("audio/bulletShoot.ogg");



		SetSoundVolume(playerDeathSound, .03f);
		SetSoundVolume(asteroidDeathSound, .04f);

		bulletSprite = LoadTexture("textures/bullets.png");

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
				DrawText("You are in pause, press Y to quit to menu or N to resume playing.", GetScreenWidth() / 2 - TextLength("You are in pause, press Y to quit to menu or N to resume playing."), GetScreenHeight() / 2, 22, RAYWHITE);
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

			case GameEndConditions::Win:

				break;

			case GameEndConditions::Lose:
				playing = false;
				break;

			default:
				break;
			}
		}

		//UnloadSound(playerDeathSound);
		//UnloadSound(asteroidDeathSound);
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
		DrawAsteroid();
		DrawUserInterface();
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