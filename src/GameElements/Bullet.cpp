#include "raylib.h"
#include "Player.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "raymath.h"

extern Player player;

using namespace kuznickiAsteroid;
extern Asteroid asteroids[];

void GenerateBullets(Bullet bullets[])
{
	for (int i = 0; i < 50; i++)
	{
		bullets[i].isActive = false;
		bullets[i].acceleration = { 200,200 };
		bullets[i].body.width = 3;
		bullets[i].body.height = 3;
	}
}

void GiveBulletOrientation(Bullet& bullet)
{
	//Give bullet player's angle
	bullet.angle = player.angle;

	//Give bullet player's position
	bullet.body.x = player.body.x;
	bullet.body.y = player.body.y;

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
			if (CheckCollisionBullet(bullets[i]))
			{

			}
			else
			{
				bullets[i].body.x = bullets[i].body.x + bullets[i].velocity.x * GetFrameTime();
				bullets[i].body.y = bullets[i].body.y + bullets[i].velocity.y * GetFrameTime();
			}
		}
	}
}

bool CheckCollisionBullet(Bullet& bullet)
{

	//Collision circle-rectangle: http://www.jeffreythompson.org/collision-detection/circle-rect.php

	float testX = 
}

void DrawBullets(Bullet bullets[])
{
	for (int i = 0; i < 50; i++)
	{
		if (bullets[i].isActive)
		{
			DrawRectanglePro(bullets[i].body, { bullets[i].body.width / 2, bullets[i].body.height / 2 }, bullets[i].angle, RAYWHITE);
		}
	}

}