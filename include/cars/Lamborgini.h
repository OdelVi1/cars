#pragma once
#include "CarRectBase.h"
#include <SFML/Graphics.hpp>
#include "../Graphics.h"
#include "ObjectFactory.h"

class Lamborgini : public CarRectBase
{
public:
	Lamborgini(RoadNode* roadNode, Direction_t direction) : CarRectBase(sf::IntRect(489, 1186, 85, 189),
		Graphics::getInstance().getTexture(GameTextures::OBJECTS), roadNode, direction) {};
	~Lamborgini() = default;

private:
	static bool m_registerCar;
};
