// PartialMap
#include "PartialMap.h"
#include <iostream>

//This class is in charge of the map view.
//As the player moves in the x direction and in the y direction,
//And creating a smooth scrolling effect while preventing the view from going beyond the map's bounds.

PartialMap::PartialMap(sf::Vector2f playerStartPos) : BaseMap(), m_playerStartPos(playerStartPos),
//m_map(Graphics::getInstance().getTexture(GameTextures::MAP)),
m_screenView(), m_roadMap(Graphics::getInstance().getTexture(GameTextures::ROAD_MAP))
{
    auto window_size = Graphics::getInstance().getWindow().getSize();
    
    // Initialize the large view to be the same size as the screen size
    m_screenView.reset(sf::FloatRect(m_playerStartPos.x, m_playerStartPos.y, 
        float(window_size.x), float(window_size.y)));
    m_roadMap.setColor(sf::Color::Yellow);
}

void PartialMap::draw() 
{
    Graphics::getInstance().getWindow().draw(m_map);
   // Graphics::getInstance().getWindow().draw(m_roadMap);
}

bool PartialMap::setViewXCenter(float playerXBoundryOffset)
{
    auto centerX = Graphics::getInstance().getWindowCenter().x;
    auto mapWidth = m_map.getGlobalBounds().width;
    sf::Vector2f screenViewCenter = m_screenView.getCenter();
    if (screenViewCenter.x + playerXBoundryOffset < centerX ||
        screenViewCenter.x + playerXBoundryOffset > mapWidth - centerX)
        return false;
    
    screenViewCenter.x += playerXBoundryOffset;
    m_screenView.setCenter(screenViewCenter);
    return true;
}

bool PartialMap::setViewYCenter(float playerYBoundryOffset)
{
    auto centerY = Graphics::getInstance().getWindowCenter().y;
    auto mapHeight = m_map.getGlobalBounds().height;
    sf::Vector2f viewCenter = m_screenView.getCenter();
    if (viewCenter.y + playerYBoundryOffset < centerY ||
        viewCenter.y + playerYBoundryOffset > mapHeight - centerY)
        return false;

    viewCenter.y += playerYBoundryOffset;
    m_screenView.setCenter(viewCenter);
    return true;
}

bool PartialMap::moveView(sf::Vector2f playerBoundryOffset) 
{
    auto center = Graphics::getInstance().getWindowCenter();
    sf::Vector2f viewCenter = m_screenView.getCenter();

    if (viewCenter.x + playerBoundryOffset.x < center.x)
        return false;
    viewCenter.x += playerBoundryOffset.x;
    if (viewCenter.y + playerBoundryOffset.y < center.y)
        return false;
    viewCenter.y += playerBoundryOffset.y;
   
    // Set the view center
    m_screenView.setCenter(viewCenter);
    return true;
}

void PartialMap::zoomOut()
{
    m_screenView.zoom(1.1f);
}

void PartialMap::zoomIn()
{
    m_screenView.zoom(0.9f);
}