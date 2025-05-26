#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Object.h"
const int DIVISION = 2;

class Drawable: public Object
{
public:
	Drawable() : m_sprite() {};
	virtual ~Drawable() = default;
	void draw() { Graphics::getInstance().getWindow().draw(m_sprite); }
	sf::FloatRect virtual getGlobalBounds() { return m_sprite.getGlobalBounds(); };
	sf::Vector2f getCenter();
protected:
	sf::Sprite m_sprite;
};