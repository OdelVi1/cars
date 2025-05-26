#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "..\observers\FuelObserver.h"
#include "..\Player.h"
#include <vector>

const std::vector<sf::IntRect> FUEL_IMAGE_LOCATIONS{
	sf::IntRect(90, 628, 211, 149),
	sf::IntRect(357, 628, 211, 149),
	sf::IntRect(623, 628, 211, 149),
	sf::IntRect(90, 341, 211, 149),
	sf::IntRect(357, 341, 211, 149),
	sf::IntRect(623, 341, 211, 149)
};

class Fuel : public FuelObserver
{
public:
	Fuel(Player& player, sf::Vector2f position) : FuelObserver(),
		m_player(player),
		m_texture(Graphics::getInstance().getTexture(GameTextures::OBJECTS)),
		m_sprite(),
		m_displayFuel(false)
	{
		m_sprite.setTexture(m_texture);
		m_sprite.setScale(sf::Vector2f(0.5, 0.5));
		m_sprite.setTextureRect(FUEL_IMAGE_LOCATIONS[0]);
		m_sprite.setPosition(position);
		m_player.registerObserver(this);
		update(0);
	};
	~Fuel() { m_player.removeObserver(this); }
	void draw() { if (m_displayFuel)	Graphics::getInstance().getWindow().draw(m_sprite); }
	void virtual update(int value) override;
	void virtual displayFuel(bool display) override { m_displayFuel = display; }
private:
	Player& m_player;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool m_displayFuel;
};
