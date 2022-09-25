#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"

struct Bullet
{
	Rectangle body;
	Vector2 acceleration;
	Vector2 velocity;
	float angle;
	bool isActive;
};

struct Player
{
	Rectangle body;
	Vector2 acceleration;
	Vector2 speedMultiplier;
	Bullet bullets[50]{};
	float angle;
	int lifes;
};



void GenerateBullets(Bullet bullets[]);
void GiveBulletOrientation(Player player, Bullet& bullet);

void Update(Player& player);

Player GeneratePlayer();

void UpdatePlayer(Player& player);
void UpdateBullets(Bullet bullets[]);
void PointPlayer(Player& player);

void DetectInput(Player& player);
void ActionInput(Player& player);
void OnMoveInput(Player& player);
void OnShootInput(Player& player);
void MovePlayer(Player& player);
void DrawPlayer(Player player);
void DrawBullets(Bullet bullets[]);
void Draw(Player player);