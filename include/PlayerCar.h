#pragma once
#include "PlayerState.h"
#include <SFML/Graphics.hpp>
#include <cars/CarRectBase.h>

const float PLAYER_CAR_STEP = 110.f;

class PlayerCar : public PlayerState
{
public:
	PlayerCar(sf::Sprite& sprite) : PlayerState(sprite, Direction_t::NONE, PLAYER_CAR_STEP_SIZE), m_currentStep(0) {};
	~PlayerCar() = default;
	virtual void setDirection() override {};
	void virtual toggleMove() override {};
private:
	int m_currentStep;
};