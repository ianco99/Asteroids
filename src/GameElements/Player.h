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
	int lifes;
};

Player GeneratePlayer();

void UpdatePlayer(Player& player);

void PointPlayer(Player& player);

void DetectInput(Player& player);
void ActionInput(Player& player);
void OnMoveInput(Player& player);
void OnShootInput(Player& player);

void GiveBulletOrientation(Player player, Bullet& bullet);

void MovePlayer(Player& player);

void CheckOutOfScreen(Player& player);

void DrawPlayer(Player player);
