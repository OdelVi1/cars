#pragma once
#include <SFML/Graphics.hpp>
#include "Mission.h"
#include "..\ObjectFactory.h"
#include "Player.h"
#include "cars\RedCar.h"
#include "cars\YellowCar.h"
#include "cars\PoliceCar.h"
#include "cars\Lamborgini.h"
#include <typeinfo>
#include <typeindex>

class MissionStealLamborgini : public Mission
{
public:
    MissionStealLamborgini(Player& player);
    ~MissionStealLamborgini() = default;
    void virtual handleCollision() override;
    sf::FloatRect virtual getMissionObjectGlobalBounds() override { return m_missionRect; };
private:
    static bool m_registerMission;
    sf::RectangleShape m_stadium;
    sf::RectangleShape m_heliPad;
    sf::FloatRect m_missionRect;
    std::vector<std::type_index> m_carTypes;
    std::vector<std::shared_ptr<CarRectBase>> m_carsTaken;
  
};
