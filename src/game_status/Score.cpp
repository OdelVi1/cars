#include "game_status\Score.h"

Score::Score(Player & player, sf::Vector2f position) : ScoreObserver(),
	m_player(player),
	m_texture(Graphics::getInstance().getTexture(GameTextures::OBJECTS)),
	m_sprite(), m_font(), m_scoreText(), m_score()
{
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
	m_sprite.setTextureRect(SCORE_IMAGE_LOCATION);
	m_sprite.setPosition(position);
	m_player.registerObserver(this);
	if (!m_font.loadFromFile("ARIAL.TTF"))
	{
		std::cerr << "Could not find ARIAL.TTF font." << std::endl;
	}
	setText();
	update(0);
};

//function to set the text for the score display
void Score::setText()
{
	sf::Color textColor = sf::Color(sf::Color(252, 127, 12));
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(15);
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setFillColor(textColor);
	m_scoreText.setPosition(sf::Vector2f(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width + INCREASE_WIDTH,
		m_sprite.getGlobalBounds().top + (m_sprite.getGlobalBounds().height / DIVIDE)));
}

void Score::draw()
{
	Graphics::getInstance().getWindow().draw(m_sprite);
	Graphics::getInstance().getWindow().draw(m_scoreText);
}

void Score::update(int value)
{
	m_score = "SCORE: " + std::to_string(value);
	m_scoreText.setString(m_score);
}