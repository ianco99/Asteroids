#pragma once
#include "raylib.h"
#include "Bullet.h"

struct Player
{
	Texture2D shipSprite;

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

void PointPlayer();

void DetectInput();
void ActionInput();
void OnMoveInput();
void OnShootInput();

void GiveBulletOrientation(Bullet& bullet);

void MovePlayer();

void CheckOutOfScreen();
void CheckBulletsOutOfScreen();

void DrawPlayer();
