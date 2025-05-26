#include "gifts/Gifts.h"

Gifts::Gifts(Player& player) : m_player(player), m_gifts(), 
m_lastCreateTime(), m_createInterval(), m_LifeGiftCounter(0)
{
    m_lastCreateTime = std::chrono::steady_clock::now();

    // Randomly set the interval for creating gifts
    m_createInterval = rand() % RANDOM_RANGE_SECONDS + RANDOM_RANGE_MIN_SECONDS;
}

void Gifts::createGifts()
{
    m_gifts.clear();
    createEqualDistanceGifts("MoneyGift");
}

//Function to create equal distance gifts using the provided name
void Gifts::createEqualDistanceGifts(std::string name)
{
    for (float row = 100.f; row < Graphics::getInstance().getPixelMap().getSize().y; row += GIFT_DISTANCE)
    {
        for (float col = 100.f; col < Graphics::getInstance().getPixelMap().getSize().x; col += GIFT_DISTANCE)
        {
            m_gifts.emplace_back(ObjectFactory::createGifts(name, m_player, sf::Vector2f(col, row)));
        }
    }
}

// Function to create gifts at a time interval using the provided name
bool Gifts::createTimedGifts(std::string name)
{
    auto now = std::chrono::steady_clock::now();
    auto duration = duration_cast<seconds>(now - m_lastCreateTime);
    if (duration.count() > m_createInterval)
    {
        auto windowSize = Graphics::getInstance().getPixelMap().getSize();

        // Randomly generate a position within the window size
        float rand_x = float(rand() % windowSize.x);
        float rand_y = float(rand() % windowSize.y);
        m_gifts.emplace_back(ObjectFactory::createGifts(name, m_player, sf::Vector2f(rand_x, rand_y)));

        // Reset the last create time to current time
        m_lastCreateTime = now;

        // Reset the create interval to a new random value
        m_createInterval = rand() % RANDOM_RANGE_SECONDS + RANDOM_RANGE_MIN_SECONDS;
        return true;
    }
    return false;
}

// Function to clear the gifts that were collected
void Gifts::clearCollectedGifts()
{
    if (m_gifts.empty())
        return;
    m_gifts.erase(std::remove_if(m_gifts.begin(), m_gifts.end(),
        [](auto const& g) { return g->isCollected(); }), m_gifts.end());
}

void Gifts::updateGifts()
{
    clearCollectedGifts();
    if (m_LifeGiftCounter <= MAX_LifeGift_GIFTS)
    {
        if (createTimedGifts("LifeGift"))
        {
            m_LifeGiftCounter++;
        }
    }
}

void Gifts::draw()
{
    for (auto& gift : m_gifts)
    {
        if (gift != nullptr)
        {
            gift->draw();
        }
    }
}