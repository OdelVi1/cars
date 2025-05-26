#pragma once
#include "State.h"

const int PLAYER_CAR_STEP_SIZE = 130;
const int FUEL_MULTIPLIER = 5;
class TakenCarState: public State
{
public:
	TakenCarState(sf::Sprite& sprite, Direction_t direction, int fuel) : 
		State(sprite, direction, PLAYER_CAR_STEP_SIZE, nullptr), m_currentFuel(fuel), m_stepCount(0) {};
	~TakenCarState() = default;
	void virtual move(sf::Time deltaTime) override { 
		m_stepCount++;
		if (m_stepCount >= 20)
		{
			m_currentFuel--;
			m_stepCount = 0;
		}
	}
	void virtual toggleMove() override {};
	void virtual setDirection() override {};
	int getFuel() { return m_currentFuel; }
private:
	int m_currentFuel;
	int m_stepCount;
};
