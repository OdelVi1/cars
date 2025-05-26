#pragma once
#pragma once
#include "CarRectBase.h"
#include "../ObjectFactory.h"
#include "YellowCar.h"
#include "RedCar.h"
#include "PoliceCar.h"
const int VISITED = 60;
class Cars
{
public:
	Cars() : m_cars(), m_roads() {};
	~Cars() = default;
	std::vector<std::shared_ptr<CarRectBase>>& getCars() { return m_cars; }
	void createCars();
	void draw();
	void moveCars(sf::Time deltaTime);
private:
	std::vector<std::shared_ptr<CarRectBase>> m_cars;
	Roads m_roads;
};
