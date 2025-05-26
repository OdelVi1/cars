#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Graphics.h"
#include "directions/Direction.h"
#include "directions/DirectionStrategy.h"

const int ZERO_ANGLE = 0;
const int RIGHT_ANGLE = 90;
const int FLAT_ANGLE = 180;
const int OBTUSE_ANGLE = 270;

class State
{
public:
	State(sf::Sprite& sprite, Direction_t direction,  float stepSize, std::shared_ptr<DirectionStrategy> directionStrategy);
	virtual ~State() = default;
	//State(sf::Sprite& sprite): m_sprite(sprite){};

	void virtual draw() { Graphics::getInstance().getWindow().draw(m_sprite); }
	void virtual move(sf::Time deltaTime) = 0;
	void virtual toggleMove() = 0;

	Direction_t getDirection() { return m_direction; };
	void setDirection(Direction_t direction);
	virtual void setDirection() = 0;

	sf::Sprite& getSprite() { return m_sprite; };

	void rotateUp() { rotate(ZERO_ANGLE); }
	void rotateRight() { rotate(RIGHT_ANGLE); }
	void rotateDown() { rotate(FLAT_ANGLE); }
	void rotateLeft() { rotate(OBTUSE_ANGLE); }
	void setDirectionStrategy(std::shared_ptr<DirectionStrategy> ptr_strategy) { m_directionStrategy = ptr_strategy; };
	void speedToZero() { m_currentSpeed = 0.f; }
	void speedToMax() { m_currentSpeed = m_stepSize; }
	float getSpeed() { return m_currentSpeed; }
	void setSpeed(float speed) { m_currentSpeed = speed; }
	void scaleDownSpeed(float factor) { m_currentSpeed *= (1 - factor); }
protected:
	sf::Sprite& m_sprite;
	Direction_t m_direction;
	float m_stepSize;
	float m_currentSpeed;
	std::shared_ptr<DirectionStrategy> m_directionStrategy;
	
	void rotate(float degree);
	void rotate(Direction_t direction);
	sf::Vector2f getCenter();
	float getStepSize(sf::Time deltaTime);
};