#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Asteroid.h"

extern int maxAsteroids;
extern int screenOffset;

namespace kuznickiAsteroid
{
	void GiveAsteroidInitPosition(Asteroid& asteroid);
	void GiveAsteroidInitDirection(Asteroid& asteroid);

	Asteroid CreateAsteroid(int arrayPosition, AsteroidSize size)
	{
		Asteroid createdAsteroid;

		createdAsteroid.speed = { 0,0 };

		createdAsteroid.arrayPosition = arrayPosition;

		if(static_cast<int>(AsteroidSize::Small) < static_cast<int>(size))
			GiveAsteroidInitPosition(createdAsteroid);

		GiveAsteroidInitDirection(createdAsteroid);

		createdAsteroid.speedMultiplier = { 200.0f, 200.0f };

		createdAsteroid.speed = Vector2Add(Vector2Multiply(createdAsteroid.speedMultiplier, createdAsteroid.direction), createdAsteroid.speed);

		createdAsteroid.size = size;

		createdAsteroid.isAlive = true;

		return createdAsteroid;
	}

	void GiveAsteroidInitPosition(Asteroid& asteroid)
	{

		int posX = 0;
		int posY = 0;

		int result = rand() % 4;

		SpawnSector sector = (SpawnSector)result;

		switch (sector)
		{

		case SpawnSector::Top:

			posX = rand() % GetScreenWidth();
			posY = 0 - screenOffset;
			break;

		case SpawnSector::Right:

			posX = GetScreenWidth() + screenOffset;
			posY = rand() % GetScreenHeight();
			break;

		case SpawnSector::Down:

			posX = rand() % GetScreenWidth();
			posY = GetScreenHeight() + screenOffset;
			break;

		case SpawnSector::Left:

			posX = 0 - screenOffset;
			posY = rand() % GetScreenHeight();
			break;
		}
		asteroid.position = { static_cast<float>(posX), static_cast<float>(posY) };
	}

	void GiveAsteroidInitDirection(Asteroid& asteroid)
	{
		Vector2 newDirection;

		newDirection.x = rand() % 20;
		newDirection.y = rand() % 20;

		newDirection = Vector2Normalize(newDirection);

		asteroid.direction = newDirection;
	}

	void UpdateAsteroids(Asteroid asteroids[])
	{
		AsteroidsOutOfScreen(asteroids);

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				MoveAsteroid(asteroids[i]);
			}
		}
	}

	void AsteroidsOutOfScreen(Asteroid asteroids[])
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				if (asteroids[i].position.x < 0)
				{
					asteroids[i].position.x = GetScreenWidth() - screenOffset;
				}
				else if (asteroids[i].position.x > GetScreenWidth())
				{
					asteroids[i].position.x = 0 + screenOffset;
				}

				if (asteroids[i].position.y < 0)
				{
					asteroids[i].position.y = GetScreenHeight() - screenOffset;
				}
				if (asteroids[i].position.y > GetScreenHeight())
				{
					asteroids[i].position.y = 0 + screenOffset;
				}
			}
		}
	}

	void MoveAsteroid(Asteroid& asteroid)
	{
		//player.acceleration = Vector2Add(Vector2Multiply(player.speedMultiplier, normalizedDir), player.acceleration);
		//asteroid.position = asteroid.position + asteroid.speed;

			
		//player.body.x = player.body.x + player.acceleration.x * GetFrameTime();
		//player.body.y = player.body.y + player.acceleration.y * GetFrameTime();

		std::cout << asteroid.position.x;
		std::cout << asteroid.position.y;

		asteroid.position = Vector2Add(asteroid.position, { asteroid.speed.x * GetFrameTime(), asteroid.speed.y * GetFrameTime() });
	}

	void DrawAsteroid(Asteroid asteroids[])
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
				DrawCircleV(asteroids[i].position, static_cast<int>(asteroids[i].size), RAYWHITE);
		}

		
	}

	void DestroyAsteroid(Asteroid asteroids[], Asteroid& asteroid)
	{
		if (ChangeAsteroidSize(asteroid))	//Check if I need to generate another asteroid with lower size
		{
			for (int i = 0; i < maxAsteroids; i++)
			{
				if (!asteroids[i].isAlive)	//Find new position for lower size asteroid
				{
					asteroids[i] = CreateAsteroid(i, asteroid.size);
					asteroids[i].position = Vector2Add(asteroid.position, {static_cast<float>(asteroid.size), static_cast<float>(asteroid.size)});
				}
			}
		}
		
		asteroids[asteroid.arrayPosition] = asteroid;

		
	}

	bool ChangeAsteroidSize(Asteroid& asteroid)
	{
		switch (asteroid.size)
		{
		case AsteroidSize::Big:
			asteroid.size = AsteroidSize::Medium;
			break;
		case AsteroidSize::Medium:
			asteroid.size = AsteroidSize::Small;
			break;
		case AsteroidSize::Small:
			asteroid.isAlive = false;
			break;
		default:
			break;
		}

		if (asteroid.isAlive)
			return true;
		else
			return false;
	}
}