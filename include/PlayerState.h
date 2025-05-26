#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <memory>

const int MAN_SIZE = 30;
const int MAN_WALK_INTERVAL = 15;

class PlayerState :public State
{
public:
	PlayerState(sf::Sprite&, Direction_t, float stepSize);
	~PlayerState() = default;
	void virtual move(sf::Time deltaTime) override;
	void virtual toggleMove() override;

protected:
	std::vector<sf::IntRect> m_moves;
	int m_move;
	float m_stepCounter;
};