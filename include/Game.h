#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Graphics.h"
#include "Level.h"
#include "Menu.h"
#include "Play.h"
#include "BaseButton.h"
#include "Player.h"

//class Level;

class Game {
public:
    Game() = default;
    ~Game() = default;
    void newGame();
    void run();

private:
    //std::vector<std::unique_ptr<Level>> m_levels;
};
