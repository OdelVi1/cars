#include "Drawable.h"

sf::Vector2f Drawable::getCenter()
{
	return sf::Vector2f(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width / DIVISION,
		m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height / DIVISION);
}