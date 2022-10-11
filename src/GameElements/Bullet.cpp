#include "raylib.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "raymath.h"

using namespace kuznickiAsteroid;

extern Player player;

extern Asteroid asteroids[];

extern int maxAsteroids;


bool CheckCollisionBulletAsteroid(Bullet& bullet);
bool CheckCollisionBulletShip(Bullet& bullet);

void GenerateBullets(Bullet bullets[])
{
	for (int i = 0; i < 50; i++)
	{
		bullets[i].isActive = false;
		bullets[i].acceleration = { 400,400 };
		bullets[i].size = 3;
	}
}

void GiveBulletOrientation(Bullet& bullet)
{
	//Give bullet player's angle
	bullet.angle = player.angle;

	//Give bullet player's position
	bullet.position.x = player.body.x;
	bullet.position.y = player.body.y;

	//Give bullet a direction

	//Vector2 normalizedDir = { GetMouseX() / Vector2Length(GetMousePosition()), GetMouseY() / Vector2Length(GetMousePosition()) };
	//Vector2 normalizedDir = Vector2Normalize(player.acceleration);
	//Vector2 normalizedDir = Vector2Subtract(GetMousePosition(), {player.body.x, player.body.y});
	Vector2 direction = Vector2Subtract(GetMousePosition(), { player.body.x, player.body.y });

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

			float distance = sqrt((distX * distX) + (distY * distY));

			if (distance <= static_cast<double>(asteroids[i].size) + bullet.size)
			{
				switch (asteroids[i].size)
				{
				case AsteroidSize::Big:
					player.score += 500;
					break;
				case AsteroidSize::Medium:
					player.score += 250;
					break;
				case AsteroidSize::Small:
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
			DrawCircleV(bullets[i].position, bullets[i].size, RAYWHITE);
		}
	}

}