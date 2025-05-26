#pragma once
#include "gifts/Gifts.h"
#include "Player.h"
#include "Graphics.h"
#include "cars/Cars.h"
#include "Roads.h"
#include "game_status\GameStatus.h"
#include "CollisionHandling.h"
#include "missions/Mission.h"
#include "FullMap.h"
#include <chrono>
#include <thread>

const int SHOW_LEVEL_OVER_TIME_MS = 3000;
const int  WIDTH_DIVIDE = 2;

class Level
{
public:
	Level(Player&, Mission&);
	~Level() = default;
    void run();
    bool getExitState() { return m_exit; }
private:
    sf::Clock m_clock;
    Cars m_cars;
    Player& m_player;
    Mission& m_mission;
    GameStatus m_gameStatus;
    Gifts m_gifts;
    bool m_isMoving;
    sf::Texture m_gameOverTexture;
    sf::Sprite m_gameOverSprite;
    sf::Sound m_sound;
    FullMap m_fullMap;
    bool m_exit;

    void checkCollisions();
    void processEvents();
    void movePlayer(sf::Time deltaTime);
    void moveObjects(sf::Time deltaTime);
    void draw();
    void drawMapObjects();
    bool isDirectionKeyPressed(sf::Event e);
    void createMapObjects();
    bool isLevelOver();
    bool isDirectionToPoint(sf::Vector2f, Direction_t, sf::Vector2f);
};