#include "Player.h"
#include <iostream>

Player::Player() :Moveable(), m_playerMan(std::make_shared<PlayerManState>(m_sprite)),
m_currentScore(0), m_currentLife(4), m_carScanRect()
{
	m_state = m_playerMan;
	m_carScanRect.setSize(sf::Vector2f(getGlobalBounds().width + SCAN_WIDTH, SCAN_HEIGHT));
	m_carScanRect.setFillColor(sf::Color::Cyan);
	
	m_carScanRect.setOrigin(m_carScanRect.getGlobalBounds().width / DIVIDE_BY_TWO, 0);
	m_carScanRect.setPosition(getPosition());
}

void Player::move(sf::Time deltaTime)
{
	Moveable::move(deltaTime);
	if (m_playerCar)
	{
		NotifyFuelObservers();
		if (m_currentFuel <= 0)
		{
			ejectCar();
		}
	}
}

void Player::setKeyboardDirection(sf::Keyboard::Key direction)
{
	setDirection(Direction::keyToDirection(direction));
}

//The function in charge of the player Boundary Offset. 
//The offset is the distance the player has moved from the boundary.
sf::Vector2f Player::getBoundryOffset(sf::Vector2f center)
{
	float x = 0, y = 0;
	auto pos = getPosition();
	if (getPosition().x < center.x - BUFFER_ZONE_SIZE.x) 
	{
		x = getPosition().x - center.x + BUFFER_ZONE_SIZE.x;
	}
	else if (getPosition().x > center.x + BUFFER_ZONE_SIZE.x)
	{
		x = getPosition().x - center.x - BUFFER_ZONE_SIZE.x;
	}

	if (getPosition().y < center.y - BUFFER_ZONE_SIZE.y)
	{
		y = getPosition().y - center.y + BUFFER_ZONE_SIZE.y;
	}
	else if (getPosition().y > center.y + BUFFER_ZONE_SIZE.y)
	{
		y = getPosition().y - center.y - BUFFER_ZONE_SIZE.y;
	}
	return sf::Vector2f(x, y);
}

void Player::resetToBoundryX(sf::Vector2f center)
{
	auto offset = getBoundryOffset(center);
	Moveable::move(-offset.x, 0);
}

void Player::resetToBoundryY(sf::Vector2f center)
{
	auto offset = getBoundryOffset(center);
	Moveable::move(0, -offset.y);
}

const int Player::getLifeLevel()
{
	return m_currentLife;
}

const int Player::getScore()
{
	return m_currentScore;
}

//Started each level the player will turn back into a man.
//The amount of life will be maximum...
void Player::reset()
{
	m_state = m_playerMan;
	m_currentLife = MAX_LIFE;
	resetLife();
	m_currentScore = 0;
	resetScore();
}

void Player::removeObserver(LifeObserver* pObserver)
{
	m_lifeObservers.erase(remove(m_lifeObservers.begin(), m_lifeObservers.end(), pObserver), m_lifeObservers.end());
}

void Player::removeObserver(ScoreObserver* pObserver)
{
	m_scoreObservers.erase(remove(m_scoreObservers.begin(), m_scoreObservers.end(), pObserver), m_scoreObservers.end());
}

void Player::removeObserver(FuelObserver* pObserver)
{
	m_fuelObservers.erase(remove(m_fuelObservers.begin(), m_fuelObservers.end(), pObserver), m_fuelObservers.end());
}

void Player::reduceALife()
{
	m_currentLife--;
	NotifyLifeObservers();
}

void Player::reduceFuel()
{
	m_currentFuel--;
	NotifyFuelObservers();
}

void Player::addALife()
{
	m_currentLife++;
	if (m_currentLife >= MAX_LIFE)
		m_currentLife = MAX_LIFE;
	NotifyLifeObservers();
}

void Player::addCoinScore()
{
	m_currentScore += COIN_SCORE;
	NotifyScoreObservers();
}

void Player::resetLife()
{
	NotifyLifeObservers();
}

void Player::resetScore()
{
	NotifyScoreObservers();
}

void Player::resetToBoundry(sf::Vector2f center)
{
	auto offset = getBoundryOffset(center);
	Moveable::move(-offset.x, -offset.y);
}

void Player::ejectCar()
{
	m_state = m_playerMan;
	m_playerCar->setRoadState();
	m_sprite.setPosition(m_playerCar->getPosition());
	m_playerCar = nullptr;
	NotifyDisplayFuelObservers(false);
}

//The change state function is used to change the state of the player in the game.
//Switches the player between being a pedestrian and being in a car,
//depending on their current state and if there is a car nearby.
void Player::changeState(std::vector<std::shared_ptr<CarRectBase>>& cars)
{
	if (typeid(*m_state.get()) == typeid(PlayerCar))
	{
		ejectCar();
		return;
	}
	m_carScanRect.setPosition(getPosition());
	m_carScanRect.setRotation(m_sprite.getRotation() + SCAN_ROTATION);
	for (auto& car : cars)
	{
		if (m_carScanRect.getGlobalBounds().intersects(car->getGlobalBounds()))
		{
			m_state = std::make_shared<PlayerCar>(car->getSprite());
			m_playerCar = car;
			m_playerCar->setTakenState();
			NotifyDisplayFuelObservers(true);
			NotifyFuelObservers();
			break;
		}
	}
}

void Player::NotifyLifeObservers()
{
	for (auto& it : m_lifeObservers)
	{
		it->update(m_currentLife);
	}
}

void Player::NotifyScoreObservers()
{
	for (auto& it : m_scoreObservers)
	{
		it->update(m_currentScore);
	}
}

void Player::NotifyFuelObservers()
{
	if (m_playerCar)
		m_currentFuel = m_playerCar->getFuel();
	for (auto& it : m_fuelObservers)
	{
		it->update(m_currentFuel);
	}
}

void Player::NotifyDisplayFuelObservers(bool display)
{
	for (auto& it : m_fuelObservers)
	{
		it->displayFuel(display);
	}
}