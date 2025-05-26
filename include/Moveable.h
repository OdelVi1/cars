#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Drawable.h"
#include "Graphics.h"
const int  DIVIDE_BY_TWO = 2;


class Moveable:public Drawable
{
public:
	Moveable(): 
		m_state(), m_previousPosition() {};
	virtual ~Moveable() = default;

	void virtual move(sf::Time deltaTime);
	void move(float xOffset, float yOffset) { m_state->getSprite().move(xOffset, yOffset); };
	void revertLastMove() { m_sprite.setPosition(m_previousPosition); }
	void setDirection(Direction_t direction = Direction_t::NONE) { m_state->setDirection(direction); };
	Direction_t getDirection() { return m_state->getDirection(); }
	void stop() { m_state->speedToZero(); }
	void virtual draw() { m_state->draw(); }
	sf::Vector2f getPosition() { return m_state->getSprite().getPosition(); }
	void setPosition(sf::Vector2f pos) { m_state->getSprite().setPosition(pos); }
	sf::FloatRect virtual getGlobalBounds() override { return m_state->getSprite().getGlobalBounds(); };
	
protected:
	std::shared_ptr<State> m_state;
	sf::Vector2f m_previousPosition;

	bool outOfWindow();
	void revertPosition() { m_state->getSprite().setPosition(m_previousPosition); };
};