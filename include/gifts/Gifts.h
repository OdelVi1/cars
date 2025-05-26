#pragma once
#include "Gift.h"
#include "../ObjectFactory.h"
#include <chrono>
#include <random>
#include <vector>
#include "Player.h"

using namespace std::chrono;

const int GIFT_DISTANCE = 500;
const int RANDOM_RANGE_SECONDS = 30;
const int RANDOM_RANGE_MIN_SECONDS = 30;
const int MAX_LifeGift_GIFTS = 7;

class Gifts
{
public:
	Gifts(Player& player);
	~Gifts() = default;
	std::vector<std::unique_ptr<Gift>>& getGifts() { return m_gifts; }
	void createGifts();
	void draw();
	void updateGifts();
private:
	Player& m_player;
	std::vector<std::unique_ptr<Gift>> m_gifts;
	std::chrono::time_point<std::chrono::steady_clock> m_lastCreateTime;
	int m_createInterval;
	int m_LifeGiftCounter;

	void createEqualDistanceGifts(std::string name);
	bool createTimedGifts(std::string name);
	void clearCollectedGifts();
};