#include "GameLoop.h"

void RunGame()
{
	Player player = GeneratePlayer();

	while (!WindowShouldClose())
	{
		Update(player);
	}

	CloseWindow();

}

Player GeneratePlayer()
{
	Player player;

	player.body = { GetScreenWidth() / 2.0f - 5, GetScreenHeight() / 2.0f - 5, 10, 10 };
	player.acceleration = { 0,0 };
	player.speedMultiplier = { .5,.5 };
	player.angle = 0;
	player.lifes = 3;

	GenerateBullets(player.bullets);

	return player;
}

void GenerateBullets(Bullet bullets[])
{
	for (int i = 0; i < sizeof(bullets) / sizeof(bullets[0]); i++)
	{
		bullets[i].isActive = false;
		bullets[i].velocity = { 1,1 };
	}
}

void Update(Player& player)
{
	UpdatePlayer(player);
	//DetectInput();
	Draw(player);
}

void UpdatePlayer(Player& player)
{
	PointPlayer(player);

	DetectInput(player);

	MovePlayer(player);
}

void PointPlayer(Player& player)
{
	Vector2 pointTo = GetMousePosition();

	Vector2 playerPos = { player.body.x , player.body.y };

	Vector2 distance = { pointTo.x - playerPos.x, pointTo.y - playerPos.y };

	float angle = atan(distance.y / distance.x);

	angle = angle * 180 / PI;

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

void DetectInput(Player& player)
{
	ActionInput(player);
}

void ActionInput(Player& player)
{

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		OnMoveInput(player);
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		OnShootInput(player);
	}
}

void OnMoveInput(Player& player)
{
	Vector2 normalizedDir = { GetMouseX() / Vector2Length(GetMousePosition()), GetMouseY() / Vector2Length(GetMousePosition()) };

	//esto es malisimo
	if (GetMouseX() < player.body.x)
	{
		normalizedDir.x *= -1;
	}
	if (GetMouseY() < player.body.y)
	{
		normalizedDir.y *= -1;
	}

	//player.acceleration = Vector2Multiply(Vector2Add(player.acceleration, normalizedDir), player.speedMultiplier);
	player.acceleration = Vector2Add(player.acceleration, normalizedDir);
}

void OnShootInput(Player& player)
{

	for (int i = 0; i < sizeof(player.bullets)/sizeof(player.bullets[0]); i++)
	{
		if (!player.bullets[i].isActive)
		{
			player.bullets[i].isActive = true;
			GiveBulletOrientation(player, player.bullets[i]);
			break;
		}
	}
}

void GiveBulletOrientation(Player player, Bullet& bullet)
{
	bullet.angle = player.angle;
	bullet.pos = { player.body.x, player.body.y };
}

void MovePlayer(Player& player)
{
	player.body.x = player.body.x + player.acceleration.x * GetFrameTime();
	player.body.y = player.body.y + player.acceleration.y * GetFrameTime();
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
	DrawRectanglePro(player.body, { player.body.width / 2	, player.body.height / 2 }, player.angle, RAYWHITE);
}