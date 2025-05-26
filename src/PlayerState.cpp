#include "PlayerState.h"

PlayerState::PlayerState(sf::Sprite& sprite, Direction_t direction, float stepSize) :
	State(sprite, direction, stepSize, nullptr), m_moves(), m_move(0), m_stepCounter(0.f)
{
	
};

void PlayerState::move(sf::Time deltaTime)
{
	float step_size = getStepSize(deltaTime);
	switch (m_direction)
	{
	case Direction_t::UP:
		m_sprite.move(0, -step_size);
		rotateUp();
		break;
	case Direction_t::DOWN:
		m_sprite.move(0, step_size);
		rotateDown();
		break;
	case Direction_t::RIGHT:
		m_sprite.move(step_size, 0);
		rotateRight();
		break;
	case Direction_t::LEFT:
		m_sprite.move(-step_size, 0);
		rotateLeft();
		break;
	}
	m_stepCounter += step_size;
	if (m_stepCounter >= MAN_WALK_INTERVAL)
	{
		toggleMove();
		m_stepCounter = 0;
	}
	speedToMax();
}

//Part of the player's walking animation
void PlayerState::toggleMove()
{
	m_sprite.setTextureRect(m_moves[m_move++]);
	if (m_move == m_moves.size())
		m_move = 0;
}