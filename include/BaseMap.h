#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"

class BaseMap {
public:
    BaseMap();
    virtual ~BaseMap() = default;
    virtual void draw()=0;
protected:
    sf::Sprite m_map;
};