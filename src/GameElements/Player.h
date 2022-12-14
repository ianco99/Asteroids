#pragma once
#include "raylib.h"
#include "bullet.h"

namespace kuznickiAsteroid
{
	struct DefaultPlayerValues
	{
		float maxVelocityX = 900;
		float maxVelocityY = 900;
	};

	struct Player
	{
		DefaultPlayerValues defaultPlayerValues;

		Texture2D shipSprite;
		Color color;

		Vector2 position;
		Vector2 velocity;
		Vector2 acceleration;
		Bullet bullets[50]{};
		float angle;
		float radius;
		int lives;
		int score;
		bool isAlive;
	};

	Player GeneratePlayer();

	void UpdatePlayer();

	void GiveBulletOrientation(Bullet& bullet);

	void DrawPlayer();
};
