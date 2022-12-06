#include "bullet.h"

#include "raylib.h"
#include "raymath.h"

#include "player.h"
#include "asteroid.h"

namespace kuznickiAsteroid
{
	extern Player player;

	extern Asteroid asteroids[];

	extern int maxAsteroids;

	extern Texture2D bulletSprite;

	Sound bulletShootSound;

	extern const int maxBullets = 50;

	const int bigAsteroidPoints = 500;
	const int mediumAsteroidPoints = 250;
	const int smallAsteroidPoints = 100;

	bool CheckCollisionBulletAsteroid(Bullet& bullet);

	void GenerateBullets(Bullet bullets[])
	{
		bulletShootSound = LoadSound("resources/audio/asteroidExplosion.ogg");

		SetSoundVolume(bulletShootSound, .04f);

		for (int i = 0; i < maxBullets; i++)
		{
			bullets[i].isActive = false;
			bullets[i].acceleration = { 400,400 };
			bullets[i].radiusSize = 3;
		}
	}

	void GiveBulletOrientation(Bullet& bullet)
	{
		PlaySoundMulti(bulletShootSound);

		bullet.angle = player.angle;

		bullet.position.x = player.position.x;
		bullet.position.y = player.position.y;

		Vector2 direction = Vector2Subtract(GetMousePosition(), { player.position.x, player.position.y });

		direction = Vector2Normalize(direction);

		bullet.velocity.x = direction.x * bullet.acceleration.x;
		bullet.velocity.y = direction.y * bullet.acceleration.y;
	}


	void UpdateBullets(Bullet bullets[])
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].isActive)
			{
				if (CheckCollisionBulletAsteroid(bullets[i]))
				{
					bullets[i].isActive = false;
				}
				else
				{
					bullets[i].position.x = bullets[i].position.x + bullets[i].velocity.x * GetFrameTime();
					bullets[i].position.y = bullets[i].position.y + bullets[i].velocity.y * GetFrameTime();
				}
			}
		}
	}

	bool CheckCollisionBulletAsteroid(Bullet& bullet)
	{

		//Collision circle-circle: http://www.jeffreythompson.org/collision-detection/circle-circle.php

		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroids[i].isAlive)
			{
				double distX = static_cast<double>(asteroids[i].position.x) - bullet.position.x;
				double distY = static_cast<double>(asteroids[i].position.y) - bullet.position.y;

				double distance = sqrt((static_cast<double>(distX) * static_cast<double>(distX)) + (static_cast<double>(distY) * static_cast<double>(distY)));

				if (distance <= static_cast<double>(asteroids[i].radiusSize) + bullet.radiusSize)
				{
					switch (asteroids[i].radiusSize)
					{
					case AsteroidRadiusSize::Big:
						player.score += bigAsteroidPoints;
						break;
					case AsteroidRadiusSize::Medium:
						player.score += mediumAsteroidPoints;
						break;
					case AsteroidRadiusSize::Small:
						player.score += smallAsteroidPoints;
						break;
					default:
						break;
					}

					DestroyAsteroid(asteroids[i]);
					return true;
				}
			}

		}
		return false;
	}

	void DrawBullets(Bullet bullets[])
	{
		for (int i = 0; i < maxBullets; i++)
		{
			if (bullets[i].isActive)
			{
				Rectangle sourRect = { 0.0f,0.0f, static_cast<float>(bulletSprite.width), static_cast<float>(bulletSprite.height) };

				Rectangle destRect = { bullets[i].position.x - static_cast<float>(bullets[i].radiusSize),bullets[i].position.y - static_cast<float>(bullets[i].radiusSize) ,static_cast<float>(bullets[i].radiusSize) * 2,static_cast<float>(bullets[i].radiusSize) * 2 };

				DrawTexturePro(bulletSprite, sourRect, destRect, { 0,0 }, bullets[i].angle, RAYWHITE);
			}
		}

	}
}