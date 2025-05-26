#pragma once
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "..\observers\ScoreObserver.h"
#include "..\Player.h"
#include <vector>
const int INCREASE_WIDTH = 20;
const int  DIVIDE = 2;

const sf::IntRect SCORE_IMAGE_LOCATION { sf::IntRect(838,971,136,145) };

class Score : public ScoreObserver
{
public:
	Score(Player& player, sf::Vector2f position);
	~Score() { m_player.removeObserver(this); }
	void draw();
	void virtual update(int value) override;
	
private:
	Player& m_player;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Font m_font;
	sf::Text m_scoreText;
	std::string m_score;
	void setText();
};
