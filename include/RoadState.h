#pragma once
#include "State.h"
#include <memory>
#include "RoadNode.h"
#include <iostream>

const int CAR_WIDTH = 65;
const float CAR_STEP_SIZE = 110.f;
const int  RADIUS_DIVIDE = 2;
const float FAR_BUFFER = 0.1f;
const float NEAR_BUFFER = 0.9f;
const int CONSECUTIVE_STEP_LIMIT = 10;

class RoadState :public State
{
public:
	RoadState(sf::Sprite&, sf::IntRect, sf::Texture& texture, RoadNode*, Direction_t,
		std::shared_ptr<DirectionStrategy>, sf::CircleShape& carBuffer);
	~RoadState() = default;
	void virtual move(sf::Time deltaTime) override;
	void virtual setDirection() override { m_nextNode = m_directionStrategy->getNextNode(m_currentNode); };
	void virtual toggleMove() override {};
	//void percantageChangeFuel();
	//void changeFuel();
protected:
	int m_fuel;
	std::shared_ptr<RoadNode> m_previousNode;
	std::shared_ptr<RoadNode> m_currentNode;
	std::shared_ptr<RoadNode> m_nextNode;
	float m_currentStep;
	sf::CircleShape& m_carBuffer;
	int m_consequtiveMoveCounter;

	bool isCarOnNode(std::shared_ptr<RoadNode> node);
	std::shared_ptr<RoadNode> getCarNode();
	void setBuffer();
};