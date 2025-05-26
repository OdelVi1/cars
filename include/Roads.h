#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include <vector>
#include <memory>
#include "RoadNode.h"
#include <unordered_map>
#include <iostream>
#include <Junction.h>

const sf::Color RIGHT_ROAD_COLOR = sf::Color(0, 0, 0);
const sf::Color UP_ROAD_COLOR = sf::Color(0, 0, 1);
const sf::Color DOWN_ROAD_COLOR = sf::Color(0, 0, 2);
const sf::Color LEFT_ROAD_COLOR = sf::Color(102, 51, 74);
const sf::Color JUNCTION_COLOR = sf::Color(101, 130, 67);
const sf::Color JUNCTION_ENTRY_COLOR = sf::Color(0, 2, 0);
const int MAX_JUNCTION_WIDTH = 200;

struct KeyHasher
{
	std::size_t operator()(const sf::Vector2i& k) const
	{
		using std::hash;

		return ((hash<int>()(k.x)
			^ (hash<int>()(k.y) << 1)) >> 1);
	}
};

struct VectorComparator
{
	bool operator() (sf::Vector2i lhs, sf::Vector2f rhs) const
	{
		return lhs.x + lhs.y < rhs.x + rhs.y;
	}
};

struct VectorComparatorUnordered
{
	bool operator() (sf::Vector2i lhs, sf::Vector2i rhs) const
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}
};

typedef std::unordered_map<sf::Vector2i, std::shared_ptr<RoadNode>, KeyHasher> RoadMap;
typedef std::vector<std::unique_ptr<Junction>> JunctionEntries;

class Roads
{
public:
	Roads() {
		if (getRoadsMap().empty())
		{
			setRoadNodes();
			setRoadNeighbors();
		}
	};
	~Roads() = default;
	RoadMap& getRoadsMap()
	{
		static RoadMap m_roadMap;
		return m_roadMap;
	}
	JunctionEntries& getJunctionEntries()
	{
		static JunctionEntries m_junctions;
		return m_junctions;
	}
private:
	sf::Vector2f m_position;
	void setRoadNodes();
	void setJunctionEntries(int x, int y);
	void setRoadNeighbors();
	Direction_t getRoadDirection(unsigned int x, unsigned int y);

};
