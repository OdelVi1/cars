#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class FontLoadException : public std::exception
{
public:
    FontLoadException(const std::string& message) : std::exception(("FontLoadException: " + message).c_str()) { }
};
class ImageLoadException: public std::exception
{
public:
    ImageLoadException(const std::string& message) : std::exception(message.c_str()) { }
};

class NoNeighborFound : public std::exception
{
public:
    NoNeighborFound(const sf::Vector2f & pos) : std::exception(("NoNeighborFound in position x: " + 
        std::to_string(pos.x) + " y: " + std::to_string(pos.y)).c_str()) { }
};