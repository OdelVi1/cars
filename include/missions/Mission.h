#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "..\observers\MissionObserver.h"
#include "PartialMap.h"
#include <chrono>

using namespace std::chrono;

const int SCORE_TO_WIN = 30000;
const int MESSAGE_DISPLAY_SECONDS = 7;
const int DIVIDE_TEXT_WIDTH = 2;
const int STEP_ONE = 1;
const int STEP_ZERO = 0;

class Mission: public ScoreObserver
{
public:
	Mission(std::string, Player&, sf::Vector2f);
	virtual ~Mission() = default;
	bool isMissionAchieved() { return m_missionAcheived; }
	void virtual draw(); 
	void virtual update(int value) override { m_missionAcheived = value >= SCORE_TO_WIN; };
	void setText(std::string);
	PartialMap& getPartialMap() { return m_partialMap; }
	sf::FloatRect virtual getMissionObjectGlobalBounds() = 0;
	void virtual handleCollision() = 0;
protected:
	sf::Font m_font;
	sf::Text m_text;
	Player& m_player;
	std::string m_str;
	std::vector<std::string> m_missionInfo;
	bool m_missionAcheived;
	PartialMap m_partialMap;
	int m_missionStep;
	sf::RectangleShape m_missionObject;
	bool m_stepMessageShown;
	std::chrono::time_point<std::chrono::steady_clock> m_displayStartTime;
};
