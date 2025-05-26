#include "cars/Lamborgini.h"

bool Lamborgini::m_registerCar = ObjectFactory::registerCar("Lambo", 1,
	[](RoadNode* roadNode, Direction_t direction) ->
	std::shared_ptr<CarRectBase> { return std::make_shared<Lamborgini>(roadNode, direction); });