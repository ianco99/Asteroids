#include "player.h"

#include "raylib.h"
#include "raymath.h"

#include "System/start_menu.h"
#include "asteroid.h"

namespace kuznickiAsteroid
{
	extern Player player;
	extern Asteroid asteroids[];

	extern Sound playerDeathSound;

	extern Texture2D buttonSprite;

	extern Button pauseButton;

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
		if (player.position.x <= 0)
		{
			player.position.x = GetScreenWidth() - screenOffset;
		}
		else if (player.position.x >= GetScreenWidth())
		{
			player.position.x = 0 + screenOffset;
		}

		if (player.position.y <= 0)
		{
			player.position.y = GetScreenHeight() - screenOffset;
		}
		if (player.position.y >= GetScreenHeight())
		{
			player.position.y = 0 + screenOffset;
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
				float distX = player.position.x - asteroids[i].position.x;
				float distY = player.position.y - asteroids[i].position.y;
				float distance = sqrt((static_cast<double>(distX) * static_cast<double>(distX)) + (static_cast<double>(distY) * static_cast<double>(distY)));

				//Collision circle-circle: http://www.jeffreythompson.org/collision-detection/circle-circle.php

				if (distance <= player.radius + static_cast<float>(asteroids[i].radiusSize))
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

		player.position.x = GetScreenWidth() / 2;
		player.position.y = GetScreenHeight() / 2;

		PlaySoundMulti(playerDeathSound);

		player.velocity = { 0,0 };
	}

	void PointPlayer()
	{
		Vector2 pointTo = GetMousePosition();

		Vector2 playerPos = { player.position.x , player.position.y };

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
		Vector2 pointDirection = Vector2Subtract(GetMousePosition(), { player.position.x, player.position.y });
		Vector2 normalizedDir = { pointDirection.x / Vector2Length(pointDirection), pointDirection.y / Vector2Length(pointDirection) };

		player.velocity = Vector2Add(Vector2Multiply(player.acceleration, normalizedDir), player.velocity);

		if (player.velocity.x > player.defaultPlayerValues.maxVelocityX)
			player.velocity.x = player.defaultPlayerValues.maxVelocityX;

		if (player.velocity.y > player.defaultPlayerValues.maxVelocityY)
			player.velocity.y = player.defaultPlayerValues.maxVelocityY;
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
		player.position.x = player.position.x + player.velocity.x * GetFrameTime();
		player.position.y = player.position.y + player.velocity.y * GetFrameTime();
	}

	void DrawPlayer()
	{
		Rectangle spriteSource = { 0,0, player.shipSprite.width, player.shipSprite.height };
		Rectangle spriteDestination = { player.position.x, player.position.y, player.radius * 2, player.radius * 2 };
		Vector2 spriteOrigin = { spriteDestination.width / 2.0f, spriteDestination.height / 2.0f };

		DrawCircleLines(player.position.x, player.position.y, player.radius, GREEN);
		DrawTexturePro(player.shipSprite, spriteSource, spriteDestination, spriteOrigin, player.angle, WHITE);
	}
}