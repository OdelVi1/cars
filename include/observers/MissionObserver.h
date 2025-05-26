#pragma once
#include "Observer.h"

class MissionObserver : public Observer
{
public:
    MissionObserver() : Observer() {};
    virtual ~MissionObserver() = default;
};