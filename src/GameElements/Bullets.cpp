#include "raymath.h"
#include "Player.h"

void GiveBulletOrientation(Player player, Bullet& bullet)
{
	//Give bullet player's angle
	bullet.angle = player.angle;

	//Give bullet player's position
	bullet.body.x = player.body.x;
	bullet.body.y = player.body.y;

	//Give bullet a direction

	Vector2 normalizedDir = { GetMouseX() / Vector2Length({(float)GetMouseX(), (float)GetMouseY()}), GetMouseY() / Vector2Length({(float)GetMouseX(), (float)GetMouseY()}) };

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
	//player.acceleration += Vector2Add(player.acceleration, normalizedDir);
	//player.acceleration = Vector2Add(Vector2Multiply(player.speedMultiplier, normalizedDir), player.acceleration);

	//Vector2 veloz = new Vector2(Vector2Add(Vector2Multiply({ bullet.acceleration.x, bullet.acceleration.y }, { normalizedDir.x,normalizedDir.y }), { bullet.velocity.x, bullet.velocity.y }));

	bullet.velocity = {Vector2Add(Vector2Multiply({ bullet.acceleration.x, bullet.acceleration.y }, { normalizedDir.x,normalizedDir.y }), { bullet.velocity.x, bullet.velocity.y }).x, Vector2Add(Vector2Multiply({ bullet.acceleration.x, bullet.acceleration.y }, { normalizedDir.x,normalizedDir.y }), { bullet.velocity.x, bullet.velocity.y }).x,
};
}

void UpdateBullets(Bullet bullets[])
{
	for (int i = 0; i < 50; i++)
	{
		if (bullets[i].isActive)
		{
			bullets[i].body.x = bullets[i].body.x + bullets[i].velocity.x * GetFrameTime();
			bullets[i].body.y = bullets[i].body.y + bullets[i].velocity.y * GetFrameTime();
		}
	}
}

void DrawBullets(Bullet bullets[])
{
	for (int i = 0; i < 50; i++)
	{
		if (bullets[i].isActive)
		{
			DrawRectanglePro(bullets[i].body, { bullets[i].body.width / 2, bullets[i].body.height / 2 }, bullets[i].angle, RAYWHITE);
		}
	}

}