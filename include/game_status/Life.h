#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "..\observers\LifeObserver.h"
#include "..\Player.h"
#include <vector>

const std::vector<sf::IntRect> LIFE_IMAGE_LOCATIONS {
	sf::IntRect(819, 796, 160, 133),
	sf::IntRect(657, 796, 160, 133),
	sf::IntRect(494, 796, 160, 133),
	sf::IntRect(331, 796, 160, 133),
	sf::IntRect(167, 796, 160, 133),
	sf::IntRect(5, 796, 160, 133)
};

class Life: public LifeObserver
{
public:
	Life(Player& player, sf::Vector2f position) : LifeObserver(),
		m_player(player),
		m_texture(Graphics::getInstance().getTexture(GameTextures::OBJECTS)),
		m_sprite()
{
	m_sprite.setTexture(m_texture);

	m_player.registerObserver(this);
	update(5);

	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
	m_sprite.setPosition(position);
};
	~Life() { m_player.removeObserver(this); }
	void draw() { Graphics::getInstance().getWindow().draw(m_sprite); }
	void virtual update(int value) override { m_sprite.setTextureRect(LIFE_IMAGE_LOCATIONS[value]); }
private:
	Player& m_player;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
