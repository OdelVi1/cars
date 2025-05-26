#pragma once

#include "Object.h"
#include <iostream>
#include <typeinfo>
#include <functional>
#include <map>
#include <string>
#include <typeindex>

#include "Player.h"
#include <gifts/Gift.h>

// Sample struct for exception throwing
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(Object& a, Object& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(Object& object1, Object& object2);
std::type_index getParentTypeId(Object& object);