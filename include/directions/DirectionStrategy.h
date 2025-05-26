#pragma once
#include "RoadNode.h"
#pragma once

class DirectionStrategy
{
public:
	DirectionStrategy() = default;
	virtual ~DirectionStrategy() = default;
	virtual std::shared_ptr<RoadNode> getNextNode(std::shared_ptr<RoadNode>) = 0;

protected:
};
