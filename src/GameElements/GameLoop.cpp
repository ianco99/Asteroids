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
	player = GeneratePlayer();

	for (int i = 0; i < 5; i++)
	{
		asteroids[i] = CreateAsteroid(i, AsteroidSize::Big);
	}

	while (!WindowShouldClose())
	{
		Update(player, asteroids);
	}

	CloseWindow();

}


void Update(Player& player, Asteroid asteroids[])
{
	UpdatePlayer(player);
	UpdateAsteroids(asteroids);
	Draw(player, asteroids);
}

void Draw(Player player, Asteroid asteroids[])
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawPlayer(player);
	DrawBullets(player.bullets);
	DrawAsteroid(asteroids);
	EndDrawing();
}