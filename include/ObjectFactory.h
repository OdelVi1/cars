#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include "gifts/Gift.h"
#include <SFML/Graphics.hpp>
#include "Roads.h"
#include <cars/CarRectBase.h>
#include "Player.h"
#include "missions/Mission.h"

using namespace std;

typedef std::vector<std::unique_ptr<Mission>(*)(Player&)> Missions;
typedef std::map<std::string, std::unique_ptr<Gift>(*)(Player&, sf::Vector2f)> giftMap;
typedef std::map<std::string, std::shared_ptr<CarRectBase>(*)(RoadNode*, Direction_t)> carMap;
typedef std::map<std::string, int> carTypes;
class ObjectFactory
{
public:
	static bool registerMission(std::unique_ptr<Mission>(*f)(Player&));
	static bool registerGift(const std::string& name, std::unique_ptr<Gift>(*f)(Player&, sf::Vector2f));
	static bool registerCar(const std::string& name, int amount, std::shared_ptr<CarRectBase>(*f)(RoadNode*, Direction_t));
	static std::unique_ptr<Gift> createGifts(const std::string& name, Player&, sf::Vector2f);
	static std::shared_ptr<CarRectBase> createCar(const std::string& name, RoadNode* roadNode, Direction_t direction);
	static std::vector < std::unique_ptr<Mission>> createMissions(Player&);
	static carTypes& getCarTypes()
	{
		static carTypes m_carTypesMap;
		return m_carTypesMap;
	}
private:
	static Missions& getMissions()
	{
		static Missions m_missions;
		return m_missions;
	}
	static giftMap& getGiftMap()
	{
		static giftMap m_giftMap;
		return m_giftMap;
	}
	static carMap& getCarMap()
	{
		static carMap m_carMap;
		return m_carMap;
	}
};
