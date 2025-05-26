#pragma once
#include "Observer.h"

class ScoreObserver : public Observer
{
public:
    ScoreObserver(): Observer() {};
    virtual ~ScoreObserver() = default;
};