#pragma once
#include "Gift.h"
#include "Graphics.h"
#include <SFML/Graphics.hpp>
#include "ObjectFactory.h"
#include "Player.h"

class LifeGift : public Gift
{
public:
	LifeGift(Player& player, sf::Vector2f position) : 
		Gift(Graphics::getInstance().getTexture(GameTextures::OBJECTS), position, 
			sf::IntRect(2, 795, 162, 134)),
	m_player(player) {};
	~LifeGift() = default;
	virtual void HandleGift() override { m_player.addALife(); };

private:
	static bool m_registerGift;
	Player& m_player;
};