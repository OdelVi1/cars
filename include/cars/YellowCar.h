#pragma once
#include "CarRectBase.h"
#include "../Graphics.h"
#include <SFML/Graphics.hpp>
#include "ObjectFactory.h"

class YellowCar : public CarRectBase
{
public:
	YellowCar(RoadNode* roadNode, Direction_t direction) : CarRectBase(sf::IntRect(643, 1410, 83, 175),
		Graphics::getInstance().getTexture(GameTextures::OBJECTS), roadNode, direction) {};
	~YellowCar() = default;

private:
	static bool m_registerCar;
};
