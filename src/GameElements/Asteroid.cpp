#include "asteroid.h"

#include <iostream>

#include "raylib.h"
#include "raymath.h"

namespace kuznickiAsteroid
{
	extern int maxAsteroids;
	extern int screenOffset;

	static int smallAsteroidCounter = 0;

	static const float bigSpeed = 120.0f;
	static const float mediumSpeed = 160.0f;
	static const float smallSpeed = 200.0f;

	extern kuznickiAsteroid::Asteroid asteroids[];
	extern Sound asteroidDeathSound;

	static void GiveAsteroidInitPosition(Asteroid& asteroid);
	static void GiveAsteroidInitDirection(Asteroid& asteroid);

	static void MoveAsteroid(Asteroid& asteroid);

	static bool ChangeAsteroidSize(Asteroid& asteroid);
	static void TrySpawningAnotherAsteroid();
	static void AsteroidsOutOfScreen();

	Asteroid CreateAsteroid(int arrayPosition, AsteroidRadiusSize radiusSize)
	{
		Asteroid createdAsteroid;

		createdAsteroid.speed = { 0,0 };

		createdAsteroid.arrayPosition = arrayPosition;

		if (static_cast<int>(AsteroidRadiusSize::Small) < static_cast<int>(radiusSize))
			GiveAsteroidInitPosition(createdAsteroid);

		GiveAsteroidInitDirection(createdAsteroid);

		switch (radiusSize)
		{
		case AsteroidRadiusSize::Big:
			createdAsteroid.speedMultiplier = { bigSpeed, bigSpeed };
			break;
		case AsteroidRadiusSize::Medium:
			createdAsteroid.speedMultiplier = { mediumSpeed, mediumSpeed };
			break;
		case AsteroidRadiusSize::Small:
			createdAsteroid.speedMultiplier = { smallSpeed, smallSpeed };
			break;
		default:
			break;
		}

		createdAsteroid.rotation = 0.0f;

		createdAsteroid.speed = Vector2Add(Vector2Multiply(createdAsteroid.speedMultiplier, createdAsteroid.direction), createdAsteroid.speed);

		createdAsteroid.radiusSize = radiusSize;

		createdAsteroid.isAlive = true;

		return createdAsteroid;
	}

	static void GiveAsteroidInitPosition(Asteroid& asteroid)
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

	static void GiveAsteroidInitDirection(Asteroid& asteroid)
	{
		Vector2 newDirection;

		newDirection.x = static_cast<float>(rand() % 20);
		newDirection.y = static_cast<float>(rand() % 20);

		int aux = rand() % 2 + 1;

		if (aux == 2)
		{
			newDirection.x *= -1;
		}

		aux = rand() % 2 + 1;

		if (aux == 1)
		{
			newDirection.y *= -1;
		}

		newDirection = Vector2Normalize(newDirection);

		asteroid.direction = newDirection;
	}

	void UpdateAsteroids()
	{
		AsteroidsOutOfScreen();

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				MoveAsteroid(asteroids[i]);
			}
		}
	}

	static void AsteroidsOutOfScreen()
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				if (asteroids[i].position.x < 0)
				{
					asteroids[i].position.x = static_cast<float>(GetScreenWidth() - screenOffset);
				}
				else if (asteroids[i].position.x > GetScreenWidth())
				{
					asteroids[i].position.x = 0.0f + screenOffset;
				}

				if (asteroids[i].position.y < 0)
				{
					asteroids[i].position.y = static_cast<float>(GetScreenHeight() - screenOffset);
				}
				if (asteroids[i].position.y > GetScreenHeight())
				{
					asteroids[i].position.y = 0.0f + screenOffset;
				}
			}
		}
	}

	static void MoveAsteroid(Asteroid& asteroid)
	{
		asteroid.position = Vector2Add(asteroid.position, { asteroid.speed.x * GetFrameTime(), asteroid.speed.y * GetFrameTime() });
	}

	void DrawAsteroid(Texture2D asteroidSprite)
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				Rectangle sourRect = { 0.0f,0.0f, static_cast<float>(asteroidSprite.width), static_cast<float>(asteroidSprite.height) };

				Rectangle destRect = { asteroids[i].position.x - static_cast<float>(asteroids[i].radiusSize),asteroids[i].position.y - static_cast<float>(asteroids[i].radiusSize) ,static_cast<float>(asteroids[i].radiusSize) * 2,static_cast<float>(asteroids[i].radiusSize) * 2 };

				DrawTexturePro(asteroidSprite, sourRect, destRect, { 0,0 }, 0, RAYWHITE);
			}
		}

	}

	void DestroyAsteroid(Asteroid& asteroid)
	{
		if (ChangeAsteroidSize(asteroid))
		{
			for (int i = 0; i < maxAsteroids; i++)
			{
				if (!asteroids[i].isAlive)
				{
					asteroids[i] = CreateAsteroid(i, asteroid.radiusSize);
					asteroids[i].position = Vector2Add(asteroid.position, { static_cast<float>(asteroid.radiusSize), static_cast<float>(asteroid.radiusSize) });
					break;
				}
			}
		}
		else
		{
			smallAsteroidCounter++;
			TrySpawningAnotherAsteroid();
		}

		asteroids[asteroid.arrayPosition] = asteroid;

	}

	static bool ChangeAsteroidSize(Asteroid& asteroid)
	{
		PlaySoundMulti(asteroidDeathSound);
		switch (asteroid.radiusSize)
		{
		case AsteroidRadiusSize::Big:
			asteroid.radiusSize = AsteroidRadiusSize::Medium;
			break;
		case AsteroidRadiusSize::Medium:
			asteroid.radiusSize = AsteroidRadiusSize::Small;
			break;
		case AsteroidRadiusSize::Small:
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

	static void TrySpawningAnotherAsteroid()
	{
		if (smallAsteroidCounter >= 4)
		{
			smallAsteroidCounter = 0;
			for (int i = 0; i < maxAsteroids; i++)
			{
				if (!asteroids[i].isAlive)
				{
					asteroids[i] = CreateAsteroid(i, AsteroidRadiusSize::Big);
					break;
				}
			}
		}
	}
}