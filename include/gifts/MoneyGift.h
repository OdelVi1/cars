#pragma once
#include "Gift.h"
#include "Graphics.h"
#include <SFML/Graphics.hpp>
#include "ObjectFactory.h"
#include "Player.h"

class MoneyGift: public Gift
{
public:
	MoneyGift(Player& player, sf::Vector2f position) : 
		Gift(Graphics::getInstance().getTexture(GameTextures::OBJECTS), position, 
			sf::IntRect(835, 977, 137, 137)),
	m_player(player) {};
	~MoneyGift() = default;
	virtual void HandleGift() override { m_player.addCoinScore();
	m_sound.setBuffer(Graphics::getInstance().getSoundBuffer(GameSounds::GAME_PRESENT_SOUND));
	m_sound.play(); };
private:
	static bool m_registerGift;
	Player& m_player;
	sf::Sound m_sound;
};