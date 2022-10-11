#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Asteroid.h"

extern int maxAsteroids;
extern int screenOffset;

int smallAsteroidCounter = 0;

extern kuznickiAsteroid::Asteroid asteroids[];

namespace kuznickiAsteroid
{
	void GiveAsteroidInitPosition(Asteroid& asteroid);
	void GiveAsteroidInitDirection(Asteroid& asteroid);

	void TrySpawningAnotherAsteroid();

	Asteroid CreateAsteroid(int arrayPosition, AsteroidSize size)
	{
		Asteroid createdAsteroid;

		createdAsteroid.speed = { 0,0 };

		createdAsteroid.arrayPosition = arrayPosition;

		if (static_cast<int>(AsteroidSize::Small) < static_cast<int>(size))
			GiveAsteroidInitPosition(createdAsteroid);

		GiveAsteroidInitDirection(createdAsteroid);

		switch (size)
		{
		case kuznickiAsteroid::AsteroidSize::Big:
			createdAsteroid.speedMultiplier = { 120.0f, 120.0f };
			break;
		case kuznickiAsteroid::AsteroidSize::Medium:
			createdAsteroid.speedMultiplier = { 160.0f, 160.0f };
			break;
		case kuznickiAsteroid::AsteroidSize::Small:
			createdAsteroid.speedMultiplier = { 200.0f, 200.0f };
			break;
		default:
			break;
		}

		createdAsteroid.rotation = 0.0f;

		createdAsteroid.sprite = LoadTexture("textures/asteroid.png");

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
		bool isNegative;

		newDirection.x = rand() % 20;
		newDirection.y = rand() % 20;

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

	void AsteroidsOutOfScreen()
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
		asteroid.position = Vector2Add(asteroid.position, { asteroid.speed.x * GetFrameTime(), asteroid.speed.y * GetFrameTime() });
	}

	void DrawAsteroid()
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				//Rectangle sourRect = { 0,0,static_cast<float>(asteroids[i].sprite.width),static_cast<float>(asteroids[i].sprite.height) };
				//Rectangle destRect = { asteroids[i].position.x,asteroids[i].position.y,static_cast<float>(asteroids[i].sprite.width * static_cast<float>(asteroids[i].size)),static_cast<float>(asteroids[i].sprite.height * static_cast<float>(asteroids[i].size)) };
				//Vector2 texturePiv = { static_cast<float>((asteroids[i].sprite.width * static_cast<float>(asteroids[i].size)) / 2),static_cast<float>((asteroids[i].sprite.height * static_cast<float>(asteroids[i].size)) / 2) };

				//DrawTexturePro(asteroids[i].sprite, sourRect, destRect, texturePiv, asteroids[i].rotation, WHITE);
				//asteroids[i].sprite.width -= 100;
				//asteroids[i].sprite.height -= 100;

				Rectangle sourRect = { 0.0f,0.0f, static_cast<float>(asteroids[i].sprite.width), static_cast<float>(asteroids[i].sprite.height) };

				//Rectangle destRect = { asteroids[i].position.x - static_cast<float>(asteroids[i].size), asteroids[i].position.y - static_cast<float>(asteroids[i].size), asteroids[i].position.x + static_cast<float>(asteroids[i].size), asteroids[i].position.y + static_cast<float>(asteroids[i].size) };
				Rectangle destRect = { asteroids[i].position.x - static_cast<float>(asteroids[i].size),asteroids[i].position.y - static_cast<float>(asteroids[i].size) ,static_cast<float>(asteroids[i].size)*2,static_cast<float>(asteroids[i].size)*2};

				DrawTexturePro(asteroids[i].sprite, sourRect, destRect, { 0,0 }, 0, RAYWHITE);
				//DrawCircleV(asteroids[i].position, static_cast<int>(asteroids[i].size), GREEN);
			}
			//DrawTexturePro(asteroids[i].sprite, { 0.0f,0.0f, static_cast<float>(asteroids[i].sprite.width), static_cast<float>(asteroids[i].sprite.height) }, { asteroids[i].position.x - static_cast<int>(asteroids[i].size), asteroids[i].position.y - static_cast<int>(asteroids[i].size)}, { asteroids[i].position.x - static_cast<int>(asteroids[i].size) , asteroids[i].position.y - static_cast<int>(asteroids[i].size)  }, asteroids[i].rotation, RAYWHITE);
			//DrawTextureEx(asteroids[i].sprite, asteroids[i].position, asteroids[i].rotation, 1 / static_cast<float>(asteroids[i].size), RAYWHITE);
		}

	}

	void DestroyAsteroid(Asteroid& asteroid)
	{
		if (ChangeAsteroidSize(asteroid))	//Check if I need to generate another asteroid with lower size
		{
			for (int i = 0; i < maxAsteroids; i++)
			{
				if (!asteroids[i].isAlive)	//Find new position for lower size asteroid
				{
					asteroids[i] = CreateAsteroid(i, asteroid.size);
					asteroids[i].position = Vector2Add(asteroid.position, { static_cast<float>(asteroid.size), static_cast<float>(asteroid.size) });
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

	void TrySpawningAnotherAsteroid()
	{
		if (smallAsteroidCounter >= 4)
		{
			smallAsteroidCounter = 0;
			for (int i = 0; i < maxAsteroids; i++)
			{
				if (!asteroids[i].isAlive)
				{
					asteroids[i] = CreateAsteroid(i, AsteroidSize::Big);
					break;
				}
			}
		}
	}
}