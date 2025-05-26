#include "game_status\GameStatus.h"

GameStatus::GameStatus(Player& player):
	m_life(player, sf::Vector2f(float(Graphics::getInstance().getWindow().getSize().x) / 5.f, 10.f)), 
	m_score(player, sf::Vector2f(float(Graphics::getInstance().getWindow().getSize().x) / 2.f, 10.f)),
	m_fuel(player, sf::Vector2f(float(Graphics::getInstance().getWindow().getSize().x) / 4.f * 3.f, 10.f)){}


void GameStatus::draw()
{
	m_life.draw();
	m_score.draw();
	m_fuel.draw();
}
