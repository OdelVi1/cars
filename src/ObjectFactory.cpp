#include "ObjectFactory.h"
//The ObjectFactory allows an object of this type to be created in the future.


//This function attempts to find a gift with the provided name in the GiftMap.
//If the gift is found, it creates and returns a new unique pointer to the gift.
//If it is not found, it returns nullptr
std::unique_ptr<Gift> ObjectFactory::createGifts(const std::string& name, Player& player, sf::Vector2f position) {
	auto it = getGiftMap().find(name);
	if (it == getGiftMap().end())
		return nullptr;
	return it->second(player, position);
}

bool ObjectFactory::registerMission(std::unique_ptr<Mission>(*f)(Player&))
{
	getMissions().emplace_back(f);
	return true;
}

//creates a new Gift object. adds the name and function to the GiftMap,
bool ObjectFactory::registerGift(const std::string& name, std::unique_ptr<Gift>(*f)(Player&, sf::Vector2f))
{
	getGiftMap().emplace(name, f);
	return true;
}

//This function takes in three parameters: a string representing the name of the car,
//an integer representing the amount of this type of car, and a function pointer that creates a new CarRectBase object.
//It adds these details to CarMap and CarTypes. 
bool ObjectFactory::registerCar(const std::string& name, int amount, std::shared_ptr<CarRectBase>(*f)(RoadNode*, Direction_t))
{
	getCarMap().emplace(name, f);
	getCarTypes().emplace(name, amount);
	return true;
}

std::shared_ptr<CarRectBase> ObjectFactory::createCar(const std::string& name, RoadNode* roadNode, Direction_t direction)
{
	auto it = getCarMap().find(name);
	if (it == getCarMap().end())
		return nullptr;
	return it->second(roadNode, direction);
}

std::vector<std::unique_ptr<Mission>> ObjectFactory::createMissions(Player& player)
{
	std::vector<std::unique_ptr<Mission>> missions;
	for (auto& mission : getMissions())
	{
		missions.emplace_back(mission(player));
	}
	return missions;
}
