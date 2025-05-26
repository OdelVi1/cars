#pragma once
#include "Observer.h"

class FuelObserver: public Observer
{
public:
    FuelObserver(): Observer() {};
    virtual ~FuelObserver() = default;
    void virtual displayFuel(bool display) = 0;
};