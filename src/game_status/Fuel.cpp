#include "game_status\Fuel.h"

void Fuel::update(int  value)
{
	if (m_displayFuel)
	{
		int index = int(std::round(float((FUEL_IMAGE_LOCATIONS.size()) - 1) * value / 100));
		if (index < 0)
			index = 0;
		else if (index > FUEL_IMAGE_LOCATIONS.size() - 1)
		{
			index = int(FUEL_IMAGE_LOCATIONS.size()) - 1;
		}
		m_sprite.setTextureRect(FUEL_IMAGE_LOCATIONS[index]);
	}
}
