#pragma once
#include <SFML/Graphics.hpp>
#include "Fuel.h"
#include "Life.h"
#include "Score.h"
#include "Player.h"
class GameStatus
{
public:
	GameStatus(Player& player);
	~GameStatus() = default;
	void draw();
private:
	Life m_life;
	Score m_score;
	Fuel m_fuel;
	
};


