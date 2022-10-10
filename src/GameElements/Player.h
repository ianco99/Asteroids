#pragma once
#include "raylib.h"
#include "Bullet.h"

struct Player
{
	Rectangle body;
	Vector2 acceleration;
	Vector2 speedMultiplier;
	Bullet bullets[50]{};
	float angle;
	int lives;
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

void DrawPlayer();
