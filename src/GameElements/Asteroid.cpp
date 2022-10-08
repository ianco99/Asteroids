#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Asteroid.h"

extern int offset;

namespace kuznickiAsteroid
{
	void GiveAsteroidInitPosition(Asteroid& asteroid);
	void GiveAsteroidInitDirection(Asteroid& asteroid);

	Asteroid CreateAsteroid(int arrayPosition, AsteroidSize size)
	{
		Asteroid createdAsteroid;


		createdAsteroid.arrayPosition = arrayPosition;

		GiveAsteroidInitPosition(createdAsteroid);

		GiveAsteroidInitDirection(createdAsteroid);

		createdAsteroid.speedMultiplier = { 10.0f, 10.0f };

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

		case kuznickiAsteroid::SpawnSector::Top:

			posX = rand() % GetScreenWidth();
			posY = 0 - offset;
			break;

		case kuznickiAsteroid::SpawnSector::Right:

			posX = GetScreenWidth() + offset;
			posY = rand() % GetScreenHeight();
			break;

		case kuznickiAsteroid::SpawnSector::Down:

			posX = rand() % GetScreenWidth();
			posY = GetScreenHeight() + offset;
			break;

		case kuznickiAsteroid::SpawnSector::Left:

			posX = 0 - offset;
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

		for (int i = 0; i < 20; i++)
		{
			if (asteroids[i].isAlive)
			{
				MoveAsteroid(asteroids[i]);
				DrawAsteroid(asteroids[i]);
			}
		}
	}

	void AsteroidsOutOfScreen(Asteroid asteroids[])
	{
		for (int i = 0; i < 200; i++)
		{
			if (asteroids[i].isAlive)
			{
				if (asteroids[i].position.x <= 0)
				{
					asteroids[i].position.x = GetScreenWidth() - offset;
				}
				else if (asteroids[i].position.x >= GetScreenWidth())
				{
					asteroids[i].position.x = 0 + offset;
				}

				if (asteroids[i].position.y <= 0)
				{
					asteroids[i].position.y = GetScreenHeight() - offset;
				}
				if (asteroids[i].position.y >= GetScreenHeight())
				{
					asteroids[i].position.y = 0 + offset;
				}
			}
		}
	}

	void MoveAsteroid(Asteroid& asteroid)
	{
		//player.acceleration = Vector2Add(Vector2Multiply(player.speedMultiplier, normalizedDir), player.acceleration);
		//asteroid.position = asteroid.position + asteroid.speed;
		std::cout << asteroid.position.x;
		std::cout << asteroid.position.y;

		asteroid.position = Vector2Add(Vector2Multiply(asteroid.speed, { GetFrameTime(), GetFrameTime() }), asteroid.position);
	}

	void DrawAsteroid(Asteroid& asteroid)
	{
		DrawCircleV(asteroid.position, static_cast<int>(asteroid.size), RAYWHITE);
	}

	void DestroyAsteroid(Asteroid asteroids[], Asteroid& asteroid)
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

		asteroids[asteroid.arrayPosition] = asteroid;
	}
}