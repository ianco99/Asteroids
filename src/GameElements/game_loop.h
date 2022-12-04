#pragma once
#include <iostream>
#include "Player.h"
#include "Asteroid.h"

namespace kuznickiAsteroid
{

	enum class GameEndConditions { Game, Pause, Win, Lose };

	GameEndConditions CheckGameEndConditions();

	void Update();
	void Draw();
}