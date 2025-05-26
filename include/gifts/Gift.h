#pragma once
#include "Drawable.h"
#include <SFML/Graphics.hpp>
#include "Graphics.h"

int const GIFT_SIZE = 30;

class Gift:public Drawable
{
public:
	Gift(sf::Texture texture, sf::Vector2f position, sf::IntRect rect);
	virtual ~Gift() = default;
	virtual void Collect() { m_isCollected = true; };
	virtual void HandleGift() = 0;
	virtual bool isCollected() { return m_isCollected; }
	void placeGift() {};
private:
	sf::Texture m_giftTexture;
	sf::Vector2f m_position;
	bool m_isCollected;
};
