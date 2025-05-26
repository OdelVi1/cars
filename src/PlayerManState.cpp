#include "PlayerManState.h"

//The PlayerManState class is a derived class from the PlayerState class/
//representing the state of the player when they are walking or running (not in a car).

PlayerManState::PlayerManState(sf::Sprite& sprite): PlayerState(sprite, Direction_t::UP, REGULAR_STEP),
m_texture(Graphics::getInstance().getTexture(GameTextures::OBJECTS))
{
	m_moves.emplace_back(sf::IntRect(512, 56, 55, 38));
	m_moves.emplace_back(sf::IntRect(512, 127, 55, 38));
	m_moves.emplace_back(sf::IntRect(514, 202, 55, 38));
	
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(m_moves[0]);
	m_sprite.scale(MAN_SIZE / m_sprite.getGlobalBounds().width, MAN_SIZE / m_sprite.getGlobalBounds().width);
	
}

