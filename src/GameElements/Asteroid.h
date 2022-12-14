#pragma once
#include "raylib.h"

namespace kuznickiAsteroid
{
	enum class SpawnSector { Top, Right, Down, Left };
	enum class AsteroidRadiusSize { Big = 20, Medium = 10, Small = 6 };

	struct Asteroid
	{
		Vector2 position;
		Vector2 speed;
		Vector2 speedMultiplier;
		Vector2 direction;

		float rotationSpeed;
		float rotation;

		AsteroidRadiusSize radiusSize;
		int arrayPosition;	//This way is easier to know where in the array this asteroid is, when needed to destroy it or change it in some way

		bool isAlive;
	};

	Asteroid CreateAsteroid(int arrayPosition, AsteroidRadiusSize radiusSize);

	void UpdateAsteroids();

	void DrawAsteroid(Texture2D asteroidSprite);

	void DestroyAsteroid(Asteroid& asteroid);
}

