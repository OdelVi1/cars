#include "missions\MissionBailOut.h"

//c-tor initializes the MissionBailOut object 
// with a mission text, player, and map start position, and sets the police station's position.

MissionBailOut::MissionBailOut(Player& player): 
	Mission("Bail out", player, sf::Vector2f(1400, 1300)), m_policeStation(sf::Vector2f(300, 300))
{
	m_policeStation.setPosition(1026, 2916);
	m_missionInfo.emplace_back("Hi. You will need to collect $10000\n more instructions will follow once you have it");
	m_missionInfo.emplace_back("Good. You have collected $10000.\n Now, go to the police station and pay bail for my guy!");

	setText(m_missionInfo[STEP_ZERO]); //new mission start from step zero 
}

void MissionBailOut::update(int value)
{ 
	if (m_missionStep == STEP_ZERO && value >= MONEY_GOAL)
	{
		m_missionStep++;
		setText(m_missionInfo[m_missionStep]);
	}
	Mission::update(value);
}

//Function to handle the collision of the player with the police station
void MissionBailOut::handleCollision()
{
	if (m_missionStep == STEP_ONE)
	{
		m_missionStep++;
		m_missionAcheived = true;
		setText("Mission Accomplished");
	}
}

// Static member that registers this mission in the ObjectFactory.
bool MissionBailOut::m_registerMission = ObjectFactory::registerMission([](Player& player) ->
	std::unique_ptr<Mission> { return std::make_unique<MissionBailOut>(player); });