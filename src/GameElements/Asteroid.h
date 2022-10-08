#pragma once
#include "raylib.h"

namespace kuznickiAsteroid
{
	enum class SpawnSector{Top, Right, Down, Left};
	enum class AsteroidSize {Big = 20, Medium = 10, Small = 6};

	struct Asteroid
	{
		Vector2 position;
		Vector2 speed;
		Vector2 speedMultiplier;
		Vector2 direction;

		float rotationSpeed;
		
		AsteroidSize size;	//
		int arrayPosition;	//This way is easier to know where in the array this asteroid is, when needed to destroy it or change it in some way

		bool isAlive;
	};

	Asteroid CreateAsteroid(int arrayPosition, AsteroidSize size);

	void UpdateAsteroids(Asteroid asteroids[]);

	void AsteroidsOutOfScreen(Asteroid asteroids[]);

	void MoveAsteroid(Asteroid& asteroid);

	void DrawAsteroid(Asteroid& asteroid);

	void DestroyAsteroid(Asteroid asteroids[], Asteroid& asteroid);
}

