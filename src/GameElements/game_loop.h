#pragma once

namespace kuznickiAsteroid
{

	enum class GameEndConditions { Game, Pause, Lose };

	GameEndConditions CheckGameEndConditions();

	void RunGame();
	void Update();
	void Draw();
}