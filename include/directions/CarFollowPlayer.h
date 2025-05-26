#pragma once

#include "DirectionStrategy.h"
class CarFollowPlayer :public DirectionStrategy
{
public:
	CarFollowPlayer() = default;
	~CarFollowPlayer() = default;
	virtual Node* getNextNode(Node*) override;
private:

};