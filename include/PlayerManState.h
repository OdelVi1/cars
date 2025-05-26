#pragma once
#include "PlayerState.h"
#include <SFML/Graphics.hpp>

const float REGULAR_STEP = 100.f;

class PlayerManState : public PlayerState
{
public:
	PlayerManState(sf::Sprite& sprite);
	~PlayerManState() = default;
	virtual void setDirection() override {};
private:
	sf::Texture m_texture;
};