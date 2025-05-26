#include "cars/PoliceCar.h"

bool PoliceCar::m_registerCar = ObjectFactory::registerCar("Police", 6,
	[](RoadNode* roadNode, Direction_t direction) ->
	std::shared_ptr<CarRectBase> { return std::make_shared<PoliceCar>(roadNode, direction); });