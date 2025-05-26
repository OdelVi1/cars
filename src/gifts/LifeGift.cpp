#include "gifts/LifeGift.h"
bool LifeGift::m_registerGift = ObjectFactory::registerGift("LifeGift",
	[](Player& player, sf::Vector2f position) -> 
	std::unique_ptr<Gift> { return std::make_unique<LifeGift>(player, position); });