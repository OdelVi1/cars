#include "Level.h"

Level::Level(Player& player, Mission& mission) : m_player(player), m_mission(mission),
m_isMoving(false), m_gifts(m_player), m_cars(), m_gameStatus(m_player),
m_gameOverTexture(), m_gameOverSprite(), m_fullMap(), m_exit(false)
{
}

// This function runs the current level, resets the player, sets the player's position,
//creates map objects, and then enters the game loop
void Level::run()
{
    m_player.reset();
    m_player.setPosition(m_mission.getPartialMap().getScreenMapView().getCenter());
    //auto pos = m_player.getPosition();
    createMapObjects();
    while (Graphics::getInstance().getWindow().isOpen() && !isLevelOver())
    {
        sf::Time deltaTime = m_clock.restart();
        processEvents();
        movePlayer(deltaTime);
        moveObjects(deltaTime);
        checkCollisions();
        draw();
    }
}

// This function processes the events during the game loop
void Level::processEvents()
{
    sf::Event e;
    while (Graphics::getInstance().getWindow().pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            Graphics::getInstance().getWindow().close();
        }
        if (isDirectionKeyPressed(e))
        {
            m_isMoving = true;
            m_player.setKeyboardDirection(e.key.code);
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space)
        {
            m_player.changeState(m_cars.getCars());
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
        {
            m_exit = true;
            return;
        }
        if (e.type == sf::Event::MouseWheelScrolled)
        {
            auto s = e.mouseWheelScroll;
            if (s.delta == 1)
            {
                m_mission.getPartialMap().zoomIn();
            }
            else
            {
                m_mission.getPartialMap().zoomOut();
            }
        }
        if (e.type == sf::Event::KeyReleased)
        {
            m_isMoving = false;
        }
    }
}

bool Level::isLevelOver()
{
    if (m_mission.isMissionAchieved())
    {
        m_gameOverTexture = Graphics::getInstance().getTexture(GameTextures::LEVEL_WON);
        m_sound.setBuffer(Graphics::getInstance().getSoundBuffer(GameSounds::WIN));
        m_sound.play();
    }
    else if (m_player.getLifeLevel() == 0)
    {
        m_gameOverTexture = Graphics::getInstance().getTexture(GameTextures::LEVEL_LOST);
        m_sound.setBuffer(Graphics::getInstance().getSoundBuffer(GameSounds::GAME_OVER));
        m_sound.play();
    }
    else
    {
        return m_exit;
    }
    m_gameOverSprite.setTexture(m_gameOverTexture);
    auto windowCenter = Graphics::getInstance().getWindowCenter();
    sf::Vector2f position = sf::Vector2f(windowCenter.x - m_gameOverSprite.getGlobalBounds().width / WIDTH_DIVIDE,
        windowCenter.y - m_gameOverSprite.getGlobalBounds().height);
    m_gameOverSprite.setPosition(position);
    Graphics::getInstance().getWindow().draw(m_gameOverSprite);
    Graphics::getInstance().getWindow().display();
    std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_LEVEL_OVER_TIME_MS));
    return true;
}

// This function creates the objects in the map
void Level::createMapObjects()
{
    m_cars.createCars();
    m_gifts.createGifts();
}

void Level::checkCollisions()
{
    if (m_player.getGlobalBounds().intersects(m_mission.getMissionObjectGlobalBounds()))
    {
        m_mission.handleCollision();
    }

    for (auto& gift : m_gifts.getGifts())
    {
        if (gift != nullptr)
        {
             if(gift->getGlobalBounds().intersects(m_player.getGlobalBounds()))
                  processCollision(m_player,*gift);
        }
    }

    for (auto& car : m_cars.getCars())
    {
        if (car != nullptr && !m_player.isPlayerInCar(car))
        {
            if (car->getCarBufferGlobalBounds().intersects(m_player.getGlobalBounds()) ||
                 car->getGlobalBounds().intersects(m_player.getGlobalBounds()))
            {
                if (car->getGlobalBounds().intersects(m_player.getGlobalBounds()) &&
                    isDirectionToPoint(sf::Vector2f(m_player.getGlobalBounds().left, 
                        m_player.getGlobalBounds().top), m_player.getDirection(), car->getCenter()))
                {
                    m_player.stop();
                }
                processCollision(m_player, *car);
            }
        }
    }
    
    auto begin = m_cars.getCars().begin();
    for (; begin != m_cars.getCars().end(); ++begin)
        for (auto second = m_cars.getCars().begin() + 1; second != m_cars.getCars().end(); ++second)
        {
            if (begin->get() == second->get())
                continue;
            if ((begin->get()->getGlobalBounds().intersects(second->get()->getGlobalBounds()) ||
                begin->get()->getCarBufferGlobalBounds().intersects(second->get()->getGlobalBounds())) &&
                isDirectionToPoint(sf::Vector2f(begin->get()->getGlobalBounds().left,
                    begin->get()->getGlobalBounds().top), begin->get()->getDirection(), second->get()->getCenter()))
                processCollision(*begin->get(), *second->get());
        }
}

bool Level::isDirectionToPoint(sf::Vector2f point1, Direction_t direction, sf::Vector2f point2)
{
    switch (direction)
    {
    case Direction_t::RIGHT:
        if (point1.x <= point2.x)
            return true;
        return false;
    case Direction_t::DOWN:
        if (point1.y <= point2.y)
            return true;
        return false;
    case Direction_t::LEFT:
        if (point1.x >= point2.x)
            return true;
        return false;
    case Direction_t::UP:
        if (point1.y >= point2.y)
            return true;
        return false;
    default:
        return false;
    }
}

bool Level::isDirectionKeyPressed(sf::Event e)
{
    return (e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::Right ||
        e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Up ||
        e.key.code == sf::Keyboard::Down));
}

void Level::movePlayer(sf::Time deltaTime)
{
    if (!m_isMoving)
    {
        return;
    }
    m_player.move(deltaTime);
    sf::Vector2f offset = m_player.getBoundryOffset(m_mission.getPartialMap().getScreenMapView().getCenter());
    if (m_mission.getPartialMap().setViewXCenter(offset.x))
        m_player.resetToBoundryX(m_mission.getPartialMap().getScreenMapView().getCenter());

    if (m_mission.getPartialMap().setViewYCenter(offset.y))
        m_player.resetToBoundryY(m_mission.getPartialMap().getScreenMapView().getCenter());
}

void Level::moveObjects(sf::Time deltaTime)
{
    for (auto& junction: Roads().getJunctionEntries())
    {
        junction->updateJunctionEntries();
    }
    m_cars.moveCars(deltaTime);
}

void Level::drawMapObjects()
{
    sf::View currentView = Graphics::getInstance().getWindow().getView();
    // Set the view to the partial view and draw it
    Graphics::getInstance().getWindow().setView(m_mission.getPartialMap().getScreenMapView());
    m_mission.getPartialMap().draw();
    m_gifts.draw();
    m_cars.draw();
    m_player.draw();
    //Set the view to the original view
    Graphics::getInstance().getWindow().setView(currentView);
}
void Level::draw() 
{
    m_gifts.updateGifts();
    Graphics::getInstance().getWindow().clear();
    drawMapObjects();
    
    m_gameStatus.draw();
    m_fullMap.draw();
    m_mission.draw();
    Graphics::getInstance().getWindow().display();
}
