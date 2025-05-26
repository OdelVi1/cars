#pragma once
#include <SFML/Graphics.hpp>
#include "Mission.h"
#include "..\ObjectFactory.h"
#include "Player.h"

int const MONEY_GOAL = 10000;

class MissionBailOut: public Mission
{
public:
    MissionBailOut(Player& player);
    ~MissionBailOut() = default;
    void virtual update(int value) override;
    void virtual handleCollision() override;
    sf::FloatRect getMissionObjectGlobalBounds() { return m_policeStation.getGlobalBounds(); }
private:
    static bool m_registerMission;
    sf::RectangleShape m_policeStation;
};
