#pragma once
#include "directions/Direction.h"

Direction_t Direction::keyToDirection(sf::Keyboard::Key direction)
{
	switch (direction)
	{
	case sf::Keyboard::Left:
		return Direction_t::LEFT;
	case sf::Keyboard::Right:
		return Direction_t::RIGHT;
	case sf::Keyboard::Up:
		return Direction_t::UP;
	case sf::Keyboard::Down:
		return Direction_t::DOWN;
	}
	return Direction_t::NONE;
}