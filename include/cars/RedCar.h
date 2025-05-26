#pragma once
#include "CarRectBase.h"
#include <SFML/Graphics.hpp>
#include "../Graphics.h"
#include "ObjectFactory.h"

class RedCar: public CarRectBase
{
public:
	RedCar(RoadNode* roadNode, Direction_t direction): CarRectBase(sf::IntRect(643, 1190, 83, 175),
		Graphics::getInstance().getTexture(GameTextures::OBJECTS), roadNode, direction) {};
	~RedCar() = default;
private:
	static bool m_registerCar;
};
