#include "Roads.h"

// Create the Nodes that together, will act as roads
void Roads::setRoadNodes()
{
	int nodes = 0;
	for (unsigned int y = 0; y < Graphics::getInstance().getRoadMap().getSize().y; y++)
	{
		for (unsigned int x = 0; x < Graphics::getInstance().getRoadMap().getSize().x; x++)
		{
			setJunctionEntries(x, y);
			Direction_t direction = getRoadDirection(x, y);
			if (direction == Direction_t::NONE)
			{
				continue;
			}
			nodes++;
			auto coords = Graphics::getInstance().getWindow().mapPixelToCoords(sf::Vector2i(x, y));
			getRoadsMap().emplace(std::make_pair(sf::Vector2i(x, y), std::make_shared<RoadNode>(coords, direction)));
		}
	}
}

//Checking all entries to the junction according to colors
//All junctions are stored in a vector
void Roads::setJunctionEntries(int x, int y)
{
	sf::Color color;
	color = Graphics::getInstance().getRoadMap().getPixel(x, y);
	
	if (color != JUNCTION_ENTRY_COLOR)
		return;
	std::vector<Direction_t> junctionEntries;
	unsigned int i;
	for (i = 1; i < MAX_JUNCTION_WIDTH &&
		i + y < Graphics::getInstance().getRoadMap().getSize().y && 
		i + x < Graphics::getInstance().getRoadMap().getSize().x; i++)
	{
		if (Graphics::getInstance().getRoadMap().getPixel(x + i, y) == JUNCTION_ENTRY_COLOR)
		{
			if (Graphics::getInstance().getRoadMap().getPixel(x, y + i) == JUNCTION_ENTRY_COLOR &&
				Graphics::getInstance().getRoadMap().getPixel(x + i, y + i) == JUNCTION_ENTRY_COLOR)
			{
				auto rect = sf::RectangleShape(sf::Vector2f(float(i), float(i)));
				rect.setOutlineColor(sf::Color::Yellow);
				rect.setOutlineThickness(2);
				rect.setPosition(Graphics::getInstance().getWindow().mapPixelToCoords(sf::Vector2i(x, y)));

				for (unsigned int j = 1; j < i; j++)
				{
					//left side, Right direction is entry
					if (getRoadDirection(x, y + j) == Direction_t::RIGHT)
					{
						junctionEntries.emplace_back(Direction_t::RIGHT);
					}
					if (getRoadDirection(x + i, y + j) == Direction_t::LEFT)
					{
						junctionEntries.emplace_back(Direction_t::LEFT);
					}
					if (getRoadDirection(x + j, y + i) == Direction_t::UP)
					{
						junctionEntries.emplace_back(Direction_t::UP);
					}
					if (getRoadDirection(x + j, y) == Direction_t::DOWN)
					{
						junctionEntries.emplace_back(Direction_t::DOWN);
					}
				}

				getJunctionEntries().emplace_back(std::make_unique<Junction>(rect, junctionEntries));
			}
			break;
		}
	}
}
//Check if the pixel is of Road Color and return the direction
Direction_t Roads::getRoadDirection(unsigned int x, unsigned int y)
{
	sf::Color color = Graphics::getInstance().getRoadMap().getPixel(x, y);
	if (color == LEFT_ROAD_COLOR)
		return Direction_t::LEFT;
	if (color == RIGHT_ROAD_COLOR)
		return Direction_t::RIGHT;
	if (color == UP_ROAD_COLOR)
		return Direction_t::UP;
	if (color == DOWN_ROAD_COLOR)
		return Direction_t::DOWN;
	else if (color == JUNCTION_COLOR)
		return Direction_t::ANY;
	return Direction_t::NONE;
}

//The setRoadNeighbors function is designed to create links between neighboring nodes on the road.
//It works by looping through every node in Roads Map and find his neighbors.
//neighbor is node lies in a feasible direction based on the direction of the center node 
//(excluding diagonals, as those aren't valid for movements on a grid). 
//For example, if the center node is going left,
//it will skip checking the node to the right and any node that is not horizontally aligned.
void Roads::setRoadNeighbors()
{
	for (auto& centerNode : getRoadsMap())
	{
		for (int y = -1; y < 2; y++)
		{
			for (int x = -1; x < 2; x++)
			{
				if (std::abs(x) == std::abs(y) ) //skip diagonals and center points
					continue;
				else if (centerNode.second->getDirection() == Direction_t::LEFT && (x == 1 || y != 0)) //Skip neighbor to the right if going left
					continue;
				else if (centerNode.second->getDirection() == Direction_t::RIGHT && (x == -1 || y != 0)) //Skip neighbor to the left if going right
					continue;
				else if (centerNode.second->getDirection() == Direction_t::UP && (y == 1 || x != 0)) //Skip neighbor below if going up
					continue;
				else if (centerNode.second->getDirection() == Direction_t::DOWN && (y == -1 || x != 0)) //Skip neighbor above if going down
					continue;
				sf::Vector2i neighborKey = sf::Vector2i(centerNode.first.x + x, centerNode.first.y + y);
				auto neighborNode = getRoadsMap().find(neighborKey);
				if (neighborNode != getRoadsMap().end())
				{
					if (centerNode.second->canGoToNode(neighborNode->second))
						centerNode.second->addNeighbor(neighborNode->second);
				}
			}
		}
		if (centerNode.second->getNeighbors().size() == 0)
		{
			std::cout << "no neighbors\n";
		}
	}
}