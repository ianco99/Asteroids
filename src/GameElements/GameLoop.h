#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"

struct Player
{
	Rectangle body;
	Vector2 acceleration;
	Vector2 speedMultiplier;
	float angle;
	int lifes;
};

struct Bullet
{
	Vector2 pos;
	Vector2 velocity;
	float angle;
};

Player GeneratePlayer();
void Update(Player& player);
void UpdatePlayer(Player& player);

void PointPlayer(Player& player);

void DetectInput(Player& player);
void ActionInput(Player& player);

void MovePlayer(Player& player);

void Draw(Player player);
void DrawPlayer(Player player);