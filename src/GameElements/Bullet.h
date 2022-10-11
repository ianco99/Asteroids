#pragma once
#include <raylib.h>

struct Bullet
{
	Texture2D sprite;

	Vector2 position;
	int size;
	Vector2 acceleration;
	Vector2 velocity;
	float angle;
	bool isActive;
};

void GenerateBullets(Bullet bullets[]);

void UpdateBullets(Bullet bullets[]);

void DrawBullets(Bullet bullets[]);