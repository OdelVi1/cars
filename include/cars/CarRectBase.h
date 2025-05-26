#pragma once
#include <SFML/Graphics.hpp>
#include "Moveable.h"
#include <memory>
#include "RoadNode.h"
#include "RoadState.h"
#include "TakenCarState.h"
#include "directions/Direction.h"
#include <directions/CarRandomDirection.h>

class CarRectBase: public Moveable
{
public:
	CarRectBase(sf::IntRect rect, sf::Texture texture, RoadNode* roadNode, Direction_t direction) :
		Moveable(), m_texture(texture), m_inCollision(false), m_carBuffer(),
		m_roadState(std::make_shared<RoadState>(m_sprite, rect, m_texture, roadNode, direction,
			std::make_shared<CarRandomDirection>(), m_carBuffer)),
		m_takenState(std::make_shared<TakenCarState>(m_sprite,direction, rand() % 80 + 20))
	{
		m_state = m_roadState;
	};
	
	virtual ~CarRectBase() = default;
	void HandleCarCollision(CarRectBase& car);
	void drawBuffer() { Graphics::getInstance().getWindow().draw(m_carBuffer); }
	sf::FloatRect getCarBufferGlobalBounds() { return m_carBuffer.getGlobalBounds(); }
	Direction_t getDirection() { return m_state->getDirection(); }
	void setTakenState() { m_state = m_takenState; };
	void setRoadState() { m_state = m_roadState; };
	bool isTaken() { return typeid(*m_state.get()) == typeid(*m_takenState.get()); }
	sf::Sprite& getSprite() { return m_sprite; }
	int getFuel() { return m_takenState->getFuel(); }
protected:
	bool m_inCollision;
	sf::Texture m_texture;
	sf::CircleShape m_carBuffer;
	std::shared_ptr<RoadState> m_roadState;
	std::shared_ptr<TakenCarState> m_takenState;
};
