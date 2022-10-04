#include "GameLoop.h"
#include "raylib.h"
#include "raymath.h"
#include "Bullet.h"

void RunGame()
{
	Player player = GeneratePlayer();

	while (!WindowShouldClose())
	{
		Update(player);
	}

	CloseWindow();

}


void Update(Player& player)
{
	UpdatePlayer(player);
	CheckOutOfScreen(player);
	Draw(player);
}

void Draw(Player player)
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawPlayer(player);
	DrawBullets(player.bullets);
	EndDrawing();
}