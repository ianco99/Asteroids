#include "GameLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "Bullet.h"
#include "Asteroid.h"

void RunGame()
{
	Player player = GeneratePlayer();
	
	Asteroid asteroids[200];

	for (int i = 0; i < 5; i++)
	{
		asteroids[i] = CreateAsteroid(i,AsteroidSize::Big);
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
	Draw(player);
}

void Draw(Player player)
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawPlayer(player);
	DrawBullets(player.bullets);
	EndDrawing();
}