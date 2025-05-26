#include "RoadState.h"
#include <queue>
#include <Roads.h>

RoadState::RoadState(sf::Sprite& sprite, sf::IntRect rect, sf::Texture& texture, RoadNode* roadNode, 
	Direction_t direction, std::shared_ptr<DirectionStrategy> dirStrat, 
	sf::CircleShape& carBuffer) :
	State(sprite, direction, CAR_STEP_SIZE, dirStrat), m_fuel(),
    m_previousNode(), m_currentNode(std::make_shared<RoadNode>(*roadNode)), m_nextNode(), m_currentStep(0.f),
	m_carBuffer(carBuffer), m_consequtiveMoveCounter(0)
{
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(rect);
	m_sprite.setPosition(roadNode->getPosition());
	auto carSize = m_sprite.getGlobalBounds();
	auto size = std::min(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	m_sprite.scale(CAR_WIDTH / size, CAR_WIDTH / size);
	m_sprite.setOrigin(getCenter());
}

std::shared_ptr<RoadNode> RoadState::getCarNode()
{
	auto pix = Graphics::getInstance().getWindow().mapCoordsToPixel(m_sprite.getPosition());
	for (int y = 0; y < int(m_sprite.getGlobalBounds().height); y++)
	{
		for (int x = 0; x < int(m_sprite.getGlobalBounds().width); x++)
		{
			auto it = Roads().getRoadsMap().find(sf::Vector2i(pix.x + x, pix.y + y));
			if (it != Roads().getRoadsMap().end())
			{
					return it->second;
			}
		}
	}
	return nullptr;
}

bool RoadState::isCarOnNode(std::shared_ptr<RoadNode> node)
{
	if (!node)
		return false;
	return m_sprite.getGlobalBounds().contains(node->getPosition());
}

void RoadState::setBuffer()
{
	auto carSize = m_sprite.getGlobalBounds();
	auto size = std::min(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	int bufferDistance = m_consequtiveMoveCounter < CONSECUTIVE_STEP_LIMIT ? m_consequtiveMoveCounter : CONSECUTIVE_STEP_LIMIT;

	m_carBuffer.setRadius(size / RADIUS_DIVIDE);
	m_carBuffer.setFillColor(sf::Color::Transparent);
	m_carBuffer.setOutlineColor(sf::Color::Red);
	m_carBuffer.setOutlineThickness(2);
	sf::Vector2f origin;
	if (m_direction == Direction_t::RIGHT)
	{
		origin = sf::Vector2f(carSize.left + carSize.width - size * NEAR_BUFFER+ bufferDistance, carSize.top);
	}
	else if (m_direction == Direction_t::LEFT)
	{
		origin = sf::Vector2f(carSize.left - size * FAR_BUFFER - bufferDistance, carSize.top);
	}
	else if (m_direction == Direction_t::UP)
	{
		origin = sf::Vector2f(carSize.left, carSize.top - size * FAR_BUFFER - bufferDistance);
	}
	else if (m_direction == Direction_t::DOWN)
	{
		origin = sf::Vector2f(carSize.left, carSize.top + carSize.height - size * NEAR_BUFFER + bufferDistance);
	}
	m_carBuffer.setPosition(origin);
}

void RoadState::move(sf::Time deltaTime)
{
	if (!isCarOnNode(m_currentNode))
	{
		auto node = getCarNode();
		if (!node)
			return;
		m_currentNode = node;
	}
	
	m_direction = m_currentNode->getDirection();
	rotate(m_direction);

	m_currentStep += m_currentSpeed * deltaTime.asSeconds();
	if (m_currentStep >= 1)
	{
		for (auto& junctionIt : Roads().getJunctionEntries())
		{
			if (m_carBuffer.getGlobalBounds().intersects(junctionIt->getRect().getGlobalBounds()) &&
				!(m_sprite.getGlobalBounds().intersects(junctionIt->getRect().getGlobalBounds())))
			{
				if (junctionIt->isDirectionGreen(m_direction) && junctionIt->isJunctionClear())
				{

					break; // car may enter the junction
				}
				else
				{
					m_consequtiveMoveCounter = 0;
					setBuffer();
					return; //Car will not enter the junction
				}
			}
		}
		setDirection();
		m_previousNode = m_currentNode;

		m_currentNode = m_nextNode;
		m_sprite.setPosition(m_currentNode->getPosition());
		if (m_currentNode->getDirection() != Direction_t::ANY && m_direction != m_currentNode->getDirection()) // This is a Juction
		{
				m_direction = m_currentNode->getDirection();
				rotate(m_direction);
		}
		
		for (auto& junctionIt : Roads().getJunctionEntries())
		{
			if (m_sprite.getGlobalBounds().intersects(junctionIt->getRect().getGlobalBounds()))
			{
				junctionIt->addCarToJunction(this);
				break;
			}
			else
			{
				junctionIt->removeCarFromJunction(this);
			}
		}
		m_currentStep = 0;
		m_consequtiveMoveCounter++;
	}
	else
	{
		m_consequtiveMoveCounter = 0;
	}
	speedToMax();
	setBuffer();
}