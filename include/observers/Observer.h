#pragma once

class Observer
{
public:
	Observer() {};
	virtual ~Observer() = default;
	void virtual update(int value) = 0;
protected:
};
