#include "directions/CarRandomDirection.h"

std::shared_ptr<RoadNode> CarRandomDirection::getNextNode(std::shared_ptr<RoadNode> currentNode)
{
	if (currentNode->getNeighbors().size() == ZERO_NEIGHBORS)
	{
		throw NoNeighborFound(currentNode->getPosition());
	}
	if (currentNode->getNeighbors().size() == ONE_NEIGHBORS)
		 return currentNode->getNeighbors()[0];
	else
	{
		auto r = rand() % currentNode->getNeighbors().size();
		return currentNode->getNeighbors()[r];
	}
}