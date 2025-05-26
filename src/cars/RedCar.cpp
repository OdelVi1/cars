#include "cars/RedCar.h"

bool RedCar::m_registerCar = ObjectFactory::registerCar("Red", 10,
	[](RoadNode* roadNode, Direction_t direction) ->
	std::shared_ptr<CarRectBase> { return std::make_shared<RedCar>(roadNode, direction); });