#pragma once
#include <iostream>
#include "raylib.h"

struct Player
{
	Rectangle body;
	float angle;
	int lifes;
};

Player GeneratePlayer();
void DetectInput();
void ActionInput();
void DrawPlayer();