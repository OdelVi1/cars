#pragma once
#include "Graphics.h"

enum class Direction_t { NONE, RIGHT, DOWN, LEFT, UP, ANY };

class Direction
{
public:
	static Direction_t keyToDirection(sf::Keyboard::Key direction);
};