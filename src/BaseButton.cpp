#include "BaseButton.h"

BaseButton::BaseButton(GameTextures ButtonTextures)
	:m_button(Graphics::getInstance().getTexture(ButtonTextures))
{
}

void BaseButton::draw()
{
	Graphics::getInstance().getWindow().draw(m_button);
}

bool BaseButton::intersect(sf::Vector2f location) const
{
	return m_button.getGlobalBounds().contains(location);
}
