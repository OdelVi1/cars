#include "gifts/MoneyGift.h"


bool MoneyGift::m_registerGift = ObjectFactory::registerGift("MoneyGift",
	[](Player& player, sf::Vector2f position) -> 
	std::unique_ptr<Gift> { return std::make_unique<MoneyGift>(player, position); });