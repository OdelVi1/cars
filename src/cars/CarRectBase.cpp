#include "cars\CarRectBase.h"

void CarRectBase::HandleCarCollision(CarRectBase& car)
{
	if (getCarBufferGlobalBounds().intersects(car.getGlobalBounds()))
		m_state->speedToZero();
	
}