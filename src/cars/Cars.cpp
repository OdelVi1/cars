#include "cars\Cars.h"

void Cars::draw()
{
	for (auto& car : m_cars)
	{
		if (car != nullptr)
		{
			car->draw();
		}
	}
}

void Cars::moveCars(sf::Time deltaTime)
{
	for (auto& car : m_cars)
	{
		if (car != nullptr)
		{
			car->move(deltaTime);
		}
	}
}

void Cars::createCars()
{
	m_cars.clear();
	int carTypeCounter = 0;
	for (auto& nodeIt : m_roads.getRoadsMap())
	{
		nodeIt.second->clearVisited();
	}
	for (auto& carType : ObjectFactory::getCarTypes())
	{
		carTypeCounter = 0;
		for (auto& nodeIt : m_roads.getRoadsMap())
		{
			if (nodeIt.second->getVisited())
				continue;
			auto node = nodeIt.second;
			int nodeCounter = 0;
			while (node->getNeighbors().size() == 1 && nodeCounter < VISITED)
			{
				node->setVisited();
				nodeCounter++;
				if (node->getDirection() != nodeIt.second->getDirection())
				{
					nodeCounter = 0;
				}
				for (auto& car : m_cars) // check if node is collliding with an existing car
				{
					if (car->getGlobalBounds().contains(node->getPosition()))
					{
						nodeCounter = 0;
						break;
					}
				}
				node = node->getNeighbors()[0];
			}
			//got 20 pixels free of cars and turns (1 neighbor)
			if (nodeCounter >= VISITED)
			{
				m_cars.emplace_back(ObjectFactory::createCar(carType.first, nodeIt.second.get(), nodeIt.second->getDirection()));
				carTypeCounter++;
			}
			//Go to next car type when reached required amount
			if (carTypeCounter == carType.second)
			{
				break;
			}
		}
	}
	if (m_cars.empty())
	{
		std::cout << "did not place any car\n";
	}
}