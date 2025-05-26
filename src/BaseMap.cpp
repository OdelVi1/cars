// BaseMap.cpp
#include "BaseMap.h"
#include "Graphics.h"

BaseMap::BaseMap()
{
	m_map.setTexture(Graphics::getInstance().getTexture(GameTextures::MAP));
}
