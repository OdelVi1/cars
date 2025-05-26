#pragma once
#include "DirectionStrategy.h"
#include <Exceptions.h>
#include "RoadNode.h"
const int ONE_NEIGHBORS = 1;
const int ZERO_NEIGHBORS = 0;

class CarRandomDirection :public DirectionStrategy
{
public:
	CarRandomDirection() = default;
	~CarRandomDirection() = default;
	virtual std::shared_ptr<RoadNode> getNextNode(std::shared_ptr<RoadNode>) override;

private:

};