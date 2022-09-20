#include "GameLoop.h"

void RunGame()
{
	system("CLS");
	Player player = GeneratePlayer();

	Update(player);
	DetectInput();

	BeginDrawing();
	DrawRectangleRec(player.body, RAYWHITE);
	EndDrawing();
}

Player GeneratePlayer()
{
	return { {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 4, 10}, 3 };
}

void Update(Player& player)
{
	UpdatePlayer(player);
	DetectInput();
	Draw();
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

void Draw()
{
	BeginDrawing();
	DrawPlayer();
	EndDrawing();
}