#include "GameLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "Bullet.h"
#include "Asteroid.h"

int maxAsteroids = 60;
int screenOffset = 5;

Player player;

Asteroid asteroids[200];

void DrawUserInterface();

void RunGame()
{
	bool playing = true;

	player = GeneratePlayer();

	for (int i = 0; i < 5; i++)
	{
		asteroids[i] = CreateAsteroid(i, AsteroidSize::Big);
	}

	GameEndConditions condition = GameEndConditions::Game;

	while (playing)
	{
		switch (condition)
		{
		case GameEndConditions::Game:
			Update();
			condition = CheckGameEndConditions();
			break;

		case GameEndConditions::Pause:

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
	else
	{
		return GameEndConditions::Game;
	}
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
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