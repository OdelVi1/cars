#include "gifts/Gift.h"

Gift::Gift(sf::Texture texture, sf::Vector2f position, sf::IntRect rect) :m_giftTexture(texture), 
m_position(position),m_isCollected(false)
{
	m_sprite.setTexture(m_giftTexture);
	m_sprite.setTextureRect(rect);
	m_sprite.setPosition(position);
	auto size = std::min(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	m_sprite.scale(GIFT_SIZE / size, GIFT_SIZE / size);
}