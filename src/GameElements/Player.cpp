#include "raylib.h"
#include "raymath.h"
#include "Player.h"
#include "Asteroid.h"

using namespace kuznickiAsteroid;

extern Player player;
extern Asteroid asteroids[];

extern Sound playerDeathSound;

extern int screenOffset;
extern int maxAsteroids;

bool CheckCollisionPlayerAsteroid();

void KillPlayer();

Player GeneratePlayer()
{
	Player player;

	player.shipSprite = LoadTexture("textures/playerShip.png");

	player.position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	player.radius = 20.0f;
	player.velocity = { 0,0 };
	player.acceleration = { 2.5f, 2.5f };
	player.angle = 0;
	player.lives = 3;
	player.score = 0;
	player.isAlive = true;

	GenerateBullets(player.bullets);

	return player;
}

void UpdatePlayer()
{
	CheckOutOfScreen();

	if (CheckCollisionPlayerAsteroid())
	{
		KillPlayer();
		return;
	}

	PointPlayer();

	DetectInput();

	MovePlayer();

	CheckOutOfScreen();

	UpdateBullets(player.bullets);
}

void CheckOutOfScreen()
{
	if (player.body.x <= 0)
	{
		player.body.x = GetScreenWidth() - screenOffset;
	}
	else if (player.body.x >= GetScreenWidth())
	{
		player.body.x = 0 + screenOffset;
	}

	if (player.body.y <= 0)
	{
		player.body.y = GetScreenHeight() - screenOffset;
	}
	if (player.body.y >= GetScreenHeight())
	{
		player.body.y = 0 + screenOffset;
	}


	CheckBulletsOutOfScreen();
}

void CheckBulletsOutOfScreen()
{
	for (int i = 0; i < 50; i++)
	{
		if (player.bullets[i].position.x <= 0)
		{
			player.bullets[i].isActive = false;
		}
		else if (player.bullets[i].position.x >= GetScreenWidth())
		{
			player.bullets[i].isActive = false;
		}

		if (player.bullets[i].position.y <= 0)
		{
			player.bullets[i].isActive = false;
		}
		if (player.bullets[i].position.y >= GetScreenHeight())
		{
			player.bullets[i].isActive = false;
		}
	}
}


bool CheckCollisionPlayerAsteroid()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		if (asteroids[i].isAlive)
		{
			//Collision circle-rectangle: http://www.jeffreythompson.org/collision-detection/circle-rect.php

			float testX = asteroids[i].position.x;
			float testY = asteroids[i].position.y;

			if (asteroids[i].position.x < player.body.x)
			{
				testX = player.body.x;
			}

			else if (asteroids[i].position.x > player.body.x + player.body.width)
			{
				testX = player.body.x + player.body.width;
			}

			if (asteroids[i].position.y < player.body.y)
			{
				testY = player.body.y;
			}

			else if (asteroids[i].position.y > player.body.y + player.body.height)
			{
				testY = player.body.y + player.body.height;
			}

			float distX = asteroids[i].position.x - testX;
			float distY = asteroids[i].position.y - testY;
			float distance = sqrt((distX * distX) + (distY * distY));

			if (distance <= static_cast<float>(asteroids[i].size))
			{
				return true;
			}
		}
	}
	return false;

}

void KillPlayer()
{
	player.lives--;
	player.isAlive = false;

	player.body.x = GetScreenWidth() / 2;
	player.body.y = GetScreenHeight() / 2;

	PlaySoundMulti(playerDeathSound);

	player.velocity = {0,0};
}

void PointPlayer()
{
	Vector2 pointTo = GetMousePosition();

	Vector2 playerPos = { player.body.x , player.body.y };

	Vector2 distance = { pointTo.x - playerPos.x, pointTo.y - playerPos.y };

	float angle = atan(distance.y / distance.x);

	angle = angle * 180 / PI;

	if (distance.x > 0 && distance.y < 0) //Quad 4
	{
		angle += 360;
	}
	else if (distance.x < 0 && distance.y < 0) //Quad 3
	{
		angle += 180;
	}
	else if (distance.x < 0 && distance.y > 0) //Quad 2
	{
		angle += 180;
	}

	player.angle = angle;
}

void DetectInput()
{
	ActionInput();
}

void ActionInput()
{

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		OnMoveInput();
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		OnShootInput();
	}
}

void OnMoveInput()
{
	Vector2 pointDirection = Vector2Subtract(GetMousePosition(), { player.body.x, player.body.y });
	Vector2 normalizedDir = { pointDirection.x / Vector2Length(pointDirection), pointDirection.y / Vector2Length(pointDirection) };

	player.velocity = Vector2Add(Vector2Multiply(player.acceleration, normalizedDir), player.velocity);
}

void OnShootInput()
{

	for (int i = 0; i < 50; i++)
	{
		if (!player.bullets[i].isActive)
		{
			player.bullets[i].isActive = true;
			GiveBulletOrientation(player.bullets[i]);
			break;
		}
	}
}


void MovePlayer()
{
	player.body.x = player.body.x + player.velocity.x * GetFrameTime();
	player.body.y = player.body.y + player.velocity.y * GetFrameTime();
}

void DrawPlayer()
{
	//DrawTextureEx(player.shipSprite, { player.body.x+player.body.width/2 , player.body.y+player.body.height }, player.angle, 0.2f,RAYWHITE);
	//DrawTextureRec(player.shipSprite, player.body, { player.body.x, player.body.y }, RAYWHITE);
	//DrawRectanglePro(player.body, { player.body.width / 2	, player.body.height / 2 }, player.angle, RAYWHITE);
	DrawCircleLines(player.body.x, player.body.y, player.body.width, GREEN);
	DrawTexturePro(player.shipSprite, { 0.0f,0.0f, static_cast<float>(player.shipSprite.width), static_cast<float>(player.shipSprite.height) }, player.body, { player.body.width / 2, player.body.height / 2 }, player.angle, RAYWHITE);
}