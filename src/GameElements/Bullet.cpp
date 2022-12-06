#include "raylib.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "raymath.h"

namespace kuznickiAsteroid
{
	extern Player player;

	extern Asteroid asteroids[];

	extern int maxAsteroids;

	extern Texture2D bulletSprite;

	Sound bulletShootSound;

	bool CheckCollisionBulletAsteroid(Bullet& bullet);

	void GenerateBullets(Bullet bullets[])
	{
		bulletShootSound = LoadSound("resources/audio/asteroidExplosion.ogg");

		SetSoundVolume(bulletShootSound, .04f);

		for (int i = 0; i < 50; i++)
		{
			bullets[i].isActive = false;
			bullets[i].acceleration = { 400,400 };
			bullets[i].radiusSize = 3;
		}
	}

	void GiveBulletOrientation(Bullet& bullet)
	{
		PlaySoundMulti(bulletShootSound);
		//Give bullet player's angle
		bullet.angle = player.angle;

		//Give bullet player's position
		bullet.position.x = player.position.x;
		bullet.position.y = player.position.y;

		//Give bullet a direction

		//Vector2 normalizedDir = { GetMouseX() / Vector2Length(GetMousePosition()), GetMouseY() / Vector2Length(GetMousePosition()) };
		//Vector2 normalizedDir = Vector2Normalize(player.acceleration);
		//Vector2 normalizedDir = Vector2Subtract(GetMousePosition(), {player.body.x, player.body.y});
		Vector2 direction = Vector2Subtract(GetMousePosition(), { player.position.x, player.position.y });

		direction = Vector2Normalize(direction);

		bullet.velocity.x = direction.x * bullet.acceleration.x;
		bullet.velocity.y = direction.y * bullet.acceleration.y;
	}


	void UpdateBullets(Bullet bullets[])
	{
		for (int i = 0; i < 50; i++)
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
				float distX = asteroids[i].position.x - bullet.position.x;
				float distY = asteroids[i].position.y - bullet.position.y;

				float distance = sqrt((static_cast<double>(distX) * static_cast<double>(distX)) + (static_cast<double>(distY) * static_cast<double>(distY)));

				if (distance <= static_cast<double>(asteroids[i].radiusSize) + bullet.radiusSize)
				{
					switch (asteroids[i].radiusSize)
					{
					case AsteroidRadiusSize::Big:
						player.score += 500;
						break;
					case AsteroidRadiusSize::Medium:
						player.score += 250;
						break;
					case AsteroidRadiusSize::Small:
						player.score += 100;
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
		for (int i = 0; i < 50; i++)
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