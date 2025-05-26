#pragma once
#include "CarRectBase.h"
#include <SFML/Graphics.hpp>
#include "../Graphics.h"
#include "ObjectFactory.h"

class PoliceCar : public CarRectBase
{
public:
	PoliceCar(RoadNode* roadNode, Direction_t direction) : CarRectBase(sf::IntRect(638, 1654, 110, 205),
		Graphics::getInstance().getTexture(GameTextures::OBJECTS), roadNode, direction) {};
	~PoliceCar() = default;

private:
	static bool m_registerCar;
};
