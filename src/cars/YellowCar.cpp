#include "cars/YellowCar.h"

bool YellowCar::m_registerCar = ObjectFactory::registerCar("Yellow", 10,
	[](RoadNode* roadNode, Direction_t direction) ->
	std::shared_ptr<CarRectBase> { return std::make_shared<YellowCar>(roadNode, direction); });