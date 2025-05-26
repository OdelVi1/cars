#pragma once
#include "Graphics.h"
#include <SFML/Graphics.hpp>

const int DIVIDE_X = 4;
const int DIVIDE_Y = 10;
const float REDUCED_X = 260;
const int REDUCED_Y = 204;
const int TRANSPARENCY = 200;

class FullMap
{
public:
	FullMap();
	~FullMap() = default;
	void draw();
private:
	sf::Sprite m_entireMap;
	sf::View m_screenView;
};