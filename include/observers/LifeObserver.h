#pragma once
#include "Observer.h"

class LifeObserver: public Observer
{
public:
    LifeObserver(): Observer() {};
    virtual ~LifeObserver() = default;
};