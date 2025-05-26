#pragma once
#include <SFML/Graphics.hpp>
#include "cars/CarRectBase.h"
#include <chrono>

/*
max 4 ins and 4 outs of the intersection.
purpose is to prevent deadlock when all 4 directions want in.

The aim is to give a timed solution for cars to enter a junction
the simplest solution is (not the ideal):
4 entries to a junction, block 3 entries and allow just 1 every time,
for a certain amount of time.
than change to another entry.

Implementation:
4 entries are marked as direction:
Up,Down,Left,Right
Car wants to enter the jucntion with the Up direction,
it must wait until Up direction is Green.
Once an entry is blocked,
the junction will wait until it is cleared of cars until it will unblock another entry

An entry is open for 5 seconds than blocked.
if a car has already entered the junction, it must exist and then
another entry will be unblocked
*/

using namespace std::chrono;

int const OPEN_ENTRY_SECONDS = 5;
int const THREE_CARS_IN_JUNCTION = 3;

class Junction
{
public:
	Junction(sf::RectangleShape rect, std::vector<Direction_t> junctionEntries);
	~Junction() { m_carsInJunction.clear(); }

	sf::RectangleShape getRect() { return m_rect; }
	void addCarToJunction(RoadState* car);
	bool isCarInJunction(RoadState* car);
	bool isJunctionClear() { return m_carsInJunction.empty(); };
	void removeCarFromJunction(RoadState* car);
	bool isDirectionGreen(Direction_t direction);
	void updateJunctionEntries();
private:
	sf::RectangleShape m_rect;
	std::vector<Direction_t> m_junctionEntries;
	std::vector<RoadState*> m_carsInJunction;
	int m_openEntry;

	bool timePassed();

	std::chrono::time_point<std::chrono::steady_clock> m_startTime;
};
