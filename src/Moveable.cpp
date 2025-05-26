#include "Moveable.h"

// This function moves the object according to the amount of time that has passed
void Moveable::move(sf::Time deltaTime)
{
	m_previousPosition = m_state->getSprite().getPosition();
	m_state->move(deltaTime);

	// If the object has moved outside the window, return it to its previous position
	if (outOfWindow())
		revertPosition(); //return the player to previous position
}

// This function checks whether the object is outside the window
bool Moveable::outOfWindow()
{
	auto bounds = getGlobalBounds();

	// Check if the top of the object is above the window, or if the bottom of the object is below the window,
	// or if the left side of the object is to the left of the window, 
	//or if the right side of the object is to the right of the window.
	return (bounds.top < 0 ||
		bounds.top + bounds.height > Graphics::getInstance().getPixelMap().getSize().y ||
		bounds.left < 0 ||
		bounds.left + bounds.width > Graphics::getInstance().getPixelMap().getSize().x);
}