#pragma once
#include <iostream>
#include "raylib.h"
#include "raymath.h"

struct Player
{
	Rectangle body;
	float angle;
	int lifes;
};

Player GeneratePlayer();
void Update(Player& player);
void UpdatePlayer(Player& player);
void DetectInput();
void ActionInput();


void Draw(Player player);
void DrawPlayer(Player player);