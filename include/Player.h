#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Moveable.h"
#include "PlayerManState.h"
#include <memory>
#include <cars/CarRectBase.h>
#include "observers/LifeObserver.h"
#include "observers/ScoreObserver.h"
#include "observers/FuelObserver.h"
#include "PlayerCar.h"

const int MAX_LIFE = 5;
const int MAX_FUEL = 5;
const int COIN_SCORE = 1000;
const int  SCAN_WIDTH = 30;
const int  SCAN_HEIGHT = 60;
const int  SCAN_ROTATION = 180;
const int  FUEL_PIC_VECTOR = 6;
const sf::Vector2f BUFFER_ZONE_SIZE = { 150, 100 }; // Change to desired dimensions

class Player: public Moveable
{
public:
	Player();
	~Player() = default;
	void setKeyboardDirection(sf::Keyboard::Key direction);
	void virtual move(sf::Time deltaTime) override;
	sf::Vector2f getBoundryOffset(sf::Vector2f center);
	void resetToBoundry(sf::Vector2f center);
	void resetToBoundryX(sf::Vector2f center);
	void resetToBoundryY(sf::Vector2f center);
	const int getLifeLevel();
	const int getScore();
	void reset();
	void changeState(std::vector<std::shared_ptr<CarRectBase>>& cars);
	bool isPlayerInCar(std::shared_ptr<CarRectBase>  car) { return m_playerCar == car; }
	std::shared_ptr<CarRectBase> getPlayerCar() { return m_playerCar; }
	void registerObserver(LifeObserver* pObserver) { m_lifeObservers.push_back(pObserver); }
	void registerObserver(ScoreObserver* pObserver) { m_scoreObservers.push_back(pObserver); }
	void registerObserver(FuelObserver* pObserver) { m_fuelObservers.push_back(pObserver);}
	void removeObserver(LifeObserver* pObserver);
	void removeObserver(ScoreObserver* pObserver);
	void removeObserver(FuelObserver* pObserver);
	void reduceALife();
	void reduceFuel();
	void addALife();
	void addCoinScore();

private:
	std::vector<LifeObserver*> m_lifeObservers;
	std::vector<ScoreObserver*> m_scoreObservers;
	std::vector<FuelObserver*> m_fuelObservers;
	int m_currentScore;
	int m_currentLife;
	int m_currentFuel;
	std::shared_ptr<CarRectBase> m_playerCar;
	std::shared_ptr<PlayerManState> m_playerMan;
	sf::RectangleShape m_carScanRect;
	void resetLife();
	void resetScore();
	void ejectCar();

	void NotifyLifeObservers();
	void NotifyScoreObservers();
	void NotifyFuelObservers();
	void NotifyDisplayFuelObservers(bool display);
};