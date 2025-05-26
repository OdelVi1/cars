#include "missions\mission.h"

Mission::Mission(std::string missionText, Player& player, sf::Vector2f mapStartPosition) : 
	m_missionAcheived(false), m_text(), m_str(missionText), m_player(player), m_partialMap(mapStartPosition),
	m_missionInfo(), m_font(Graphics::getInstance().getArialFont()), m_missionStep(0), m_stepMessageShown(true),
	m_displayStartTime()
{
	m_player.registerObserver(this);
}

// Function to set the text of the mission
void Mission::setText(std::string str)
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::Black);
	m_text.setStyle(sf::Text::Bold);
	m_text.setString(str);
	m_text.setPosition(sf::Vector2f(Graphics::getInstance().getWindowCenter().x - m_text.getGlobalBounds().width / DIVIDE_TEXT_WIDTH,
		Graphics::getInstance().getWindowCenter().y - m_text.getGlobalBounds().height));
	m_stepMessageShown = false;
}

void Mission::draw()
{
	auto now = std::chrono::steady_clock::now();
	auto duration = duration_cast<seconds>(now - m_displayStartTime);

	//If the step message has not been shown, set the display start time to now
	//and indicate that the message has been shown
	if (!m_stepMessageShown)
	{
		m_displayStartTime = std::chrono::steady_clock::now();
		m_stepMessageShown = true;
	} 
	if (duration.count() < MESSAGE_DISPLAY_SECONDS)
	{
		Graphics::getInstance().getWindow().draw(m_text);
	}
}