#pragma once
#include <SFML/Graphics.hpp>
#include "Mission.h"
#include "..\ObjectFactory.h"
#include "Player.h"

class MissionDeliverPackage :public Mission
{
public:
    MissionDeliverPackage(Player& player);
    ~MissionDeliverPackage() = default;
    void virtual draw() override;
    void virtual handleCollision() override;
    sf::FloatRect virtual getMissionObjectGlobalBounds() override { return m_spritePtr->getGlobalBounds(); };
private:
    static bool m_registerMission;
    sf::Texture m_packageTexture;
    sf::Texture m_deliveryTexture;
    sf::Sprite m_packagePickup;
    sf::Sprite m_packageDelivery;
    std::unique_ptr<sf::Sprite> m_spritePtr;
};
