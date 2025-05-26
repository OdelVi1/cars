#pragma once
#include "Graphics.h"
#include "Command.h"
class BaseButton
{
public:
	BaseButton(GameTextures);
	~BaseButton() = default;
	void draw();
	bool intersect(sf::Vector2f) const;
private:
	sf::Sprite m_button;
	std::unique_ptr<Command> m_Command;
};