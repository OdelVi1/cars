#include "Junction.h"
Junction::Junction(sf::RectangleShape rect, std::vector<Direction_t> junctionEntries) :
	m_rect(rect), m_junctionEntries(junctionEntries), m_openEntry(0), m_carsInJunction()
{
	m_startTime = std::chrono::steady_clock::now();
};

bool Junction::isDirectionGreen(Direction_t direction)
{
	return m_junctionEntries[m_openEntry] == direction;
}

bool Junction::isCarInJunction(RoadState* car)
{
	auto it = std::find(m_carsInJunction.begin(), m_carsInJunction.end(), car);
	return it != m_carsInJunction.end();
}

void Junction::addCarToJunction(RoadState* car)
{
	if (!isCarInJunction(car))
	{
		m_carsInJunction.emplace_back(car);
	}
}

void Junction::removeCarFromJunction(RoadState* car)
{
	auto it = std::find(m_carsInJunction.begin(), m_carsInJunction.end(), car);
	if (it != m_carsInJunction.end())
	{
		m_carsInJunction.erase(it);
	}
}

void Junction::updateJunctionEntries()
{
	if (timePassed())
	{
		// junction_is_clear or overcrowded so let's release the jam
		if (m_carsInJunction.empty() || m_carsInJunction.size() >= THREE_CARS_IN_JUNCTION)
		{
			m_openEntry++;
			if (m_openEntry == m_junctionEntries.size())
				m_openEntry = 0;
			
			//Reset the start time
			m_startTime = std::chrono::steady_clock::now();
		}
	}
}

bool Junction::timePassed()
{
	auto now = std::chrono::steady_clock::now();
	auto elapsed_seconds = duration_cast<seconds>(now - m_startTime);
	return elapsed_seconds.count() >= OPEN_ENTRY_SECONDS; //3 seconds have passed
}