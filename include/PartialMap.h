#pragma once
#include "BaseMap.h"
#include <vector>
#include "Graphics.h"

class PartialMap : public BaseMap {
public:
    PartialMap(sf::Vector2f playerStartPos);
    ~PartialMap() override = default;
    void draw() override;
    bool moveView(sf::Vector2f playerBoundryOffset);
    bool setViewXCenter(float playerXBoundryOffset);
    bool setViewYCenter(float playerYBoundryOffset);
    sf::View& getScreenMapView() { return m_screenView; };
    void zoomOut();
    void zoomIn();
private:
    sf::Sprite m_roadMap;
    sf::View m_screenView;
    sf::Vector2f m_playerStartPos;

    const sf::Vector2f ENTIRE_MAP_SIZE = { 800, 600 }; // Change to desired dimensions
    const sf::Vector2f BUFFER_ZONE_POSITION = { 200, 200 }; // Change to desired position
};
