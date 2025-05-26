#include "State.h"

State::State(sf::Sprite& sprite, Direction_t direction, float stepSize, std::shared_ptr<DirectionStrategy> directionStrategy): 
	m_sprite(sprite), m_direction(direction), m_stepSize(stepSize), m_directionStrategy(directionStrategy),
	m_currentSpeed(stepSize)
{
	rotate(direction);
}

void State::setDirection(Direction_t direction)
{
	if (direction == Direction_t::NONE)
	{
		setDirection(); // If direction is NONE, call the no-argument setDirection
	}
	else
	{
		m_direction = direction;
	}
}

// Method to rotate the sprite by a certain degree
void State::rotate(float degree)
{
	m_sprite.setOrigin(getCenter());
	m_sprite.setRotation(degree);
}

//Overloaded method to rotate the sprite based on the direction
void State::rotate(Direction_t direction)
{
	switch (direction)
	{
	case Direction_t::LEFT:
		rotate(OBTUSE_ANGLE);
		break;
	case Direction_t::RIGHT:
		rotate(RIGHT_ANGLE);
		break;
	case Direction_t::UP:
		rotate(ZERO_ANGLE);
		break;
	case Direction_t::DOWN:
		rotate(FLAT_ANGLE);
		break;
	}
}

sf::Vector2f State::getCenter()
{
	auto s = m_sprite.getLocalBounds();
	return sf::Vector2f(s.left + s.width / 2, s.top + s.height / 2);
}

//Distance may be smaller if we are near a the window border
float State::getStepSize(sf::Time deltaTime)
{
	float step_size = m_currentSpeed * deltaTime.asSeconds();
	auto window_size = Graphics::getInstance().getPixelMap().getSize();

	// Check if the sprite is near the window border in each direction, 
	// if it is, adjust the step size to prevent the sprite from moving out of the window
	switch (m_direction)
	{
	case Direction_t::UP:
		if (m_sprite.getGlobalBounds().top > 0 && m_sprite.getGlobalBounds().top < step_size)
		{
			return m_sprite.getGlobalBounds().top;
		}
		break;
	case Direction_t::DOWN:
		if (m_sprite.getGlobalBounds().top + m_sprite.getGlobalBounds().height < window_size.y &&
			window_size.y - m_sprite.getGlobalBounds().top - m_sprite.getGlobalBounds().height < step_size)
		{
			return window_size.y - m_sprite.getGlobalBounds().top - m_sprite.getGlobalBounds().height;
		}
		break;
	case Direction_t::RIGHT:
		if (m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width < window_size.x &&
			window_size.x - m_sprite.getGlobalBounds().left - m_sprite.getGlobalBounds().width < step_size)
		{
			step_size = window_size.x - m_sprite.getGlobalBounds().left - m_sprite.getGlobalBounds().width;
		}
		break;
	case Direction_t::LEFT:
		if (m_sprite.getGlobalBounds().left > 0 && m_sprite.getGlobalBounds().left < step_size)
		{
			step_size = m_sprite.getGlobalBounds().left;
		}
		break;
	}
	return step_size;
}
