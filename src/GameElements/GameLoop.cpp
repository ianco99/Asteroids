#include "GameLoop.h"

void RunGame()
{
	Player player = GeneratePlayer();

	while (!WindowShouldClose())
	{
		Update(player);
	}

	//CloseWindow();

}

Player GeneratePlayer()
{
	return { {GetScreenWidth() / 5.0f, GetScreenHeight() / 5.0f, GetScreenWidth() / 5.0f+4, GetScreenHeight() / 5.0f + 10}, 0,3 };
}

void Update(Player& player)
{
	UpdatePlayer(player);
	//DetectInput();
	Draw(player);
}

void UpdatePlayer(Player& player)
{
	Vector2 pointTo = GetMousePosition();

	Vector2 playerPos = { player.body.x, player.body.y };

	Vector2 distance = { pointTo.x - playerPos.x, pointTo.y - playerPos.y };

	float angle = atan(distance.y / distance.y);

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
	if (IsKeyDown(MOUSE_BUTTON_LEFT))
	{

	}
}

void Draw(Player player)
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawPlayer(player);
	EndDrawing();
}

void DrawPlayer(Player player)
{
	DrawRectanglePro(player.body, { player.body.width/2, player.body.height/2 }, player.angle, RAYWHITE);
}