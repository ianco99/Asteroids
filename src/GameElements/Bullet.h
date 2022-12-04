#pragma once
#include <raylib.h>

namespace kuznickiAsteroid
{
	struct Bullet
	{
		Texture2D sprite;

		Vector2 position;
		int radiusSize;
		Vector2 acceleration;
		Vector2 velocity;
		float angle;
		bool isActive;
	};

	void GenerateBullets(Bullet bullets[]);

	void UpdateBullets(Bullet bullets[]);

	void DrawBullets(Bullet bullets[]);
}