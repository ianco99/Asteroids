#include "GameLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "Bullet.h"
#include "Asteroid.h"

int maxAsteroids = 60;
int screenOffset = 5;

Player player;

Asteroid asteroids[200];

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
	EndDrawing();
}