#pragma once
#include <SFML/Graphics.hpp>
#include "directions/Direction.h"
//#include "Node.h"
#include <memory>
#include <vector>

class RoadNode //: public Node
{
public:
	RoadNode(sf::Vector2f position, Direction_t direction): m_position(position), 
		m_direction(direction), m_nodeClear(true), m_visited(false) {}; // : Node(position),
		
	/*RoadNode(const RoadNode& r): Node(r.m_position)
	{
		m_direction = r.m_direction;
		m_neighbors = r.m_neighbors;
	}*/
	~RoadNode() = default;
	
	sf::Vector2f getPosition() { return m_position; };
	Direction_t getDirection() { return m_direction; };
	bool canGoToNode(std::shared_ptr<RoadNode> r)
	{
		return (m_position.x < r->m_position.x && ((m_direction == Direction_t::RIGHT || m_direction == Direction_t::ANY) && (r->m_direction != Direction_t::LEFT)) ||
			m_position.x > r->m_position.x && ((m_direction == Direction_t::LEFT || m_direction == Direction_t::ANY) && (r->m_direction != Direction_t::RIGHT)) ||
			m_position.y > r->m_position.y && ((m_direction == Direction_t::UP || m_direction == Direction_t::ANY) && (r->m_direction != Direction_t::DOWN )) ||
			m_position.y < r->m_position.y && ((m_direction == Direction_t::DOWN || m_direction == Direction_t::ANY) && (r->m_direction != Direction_t::UP)));
	}

	void clearVisited() { m_visited = false; }
	void setVisited() { m_visited = true; }
	bool getVisited() { return m_visited; }
	bool isNodeClear() { return m_nodeClear; }
	void clearNode() { m_nodeClear = true; }
	void occupyNode() { m_nodeClear = false; }

	std::vector<std::shared_ptr<RoadNode>>& getNeighbors() { return m_neighbors; };
	void addNeighbor(std::shared_ptr<RoadNode> node) { m_neighbors.emplace_back(node); };
	bool operator==(const RoadNode& other) const { return m_position == other.m_position; };
private:
	Direction_t m_direction;

	sf::Vector2f m_position;
	std::vector<std::shared_ptr<RoadNode>> m_neighbors;
	bool m_visited;
	bool m_nodeClear;
};