#include "missions\MissionStealLamborgini.h"

MissionStealLamborgini::MissionStealLamborgini(Player& player) : 
	Mission("Steal Lamborgini", player, sf::Vector2f(250, 2800)),
	m_stadium(), m_heliPad(), m_carTypes(), m_missionRect(),
	m_carsTaken()
{
	m_missionInfo.emplace_back("Hi. For this mission you will steal cars and put them inside the Stadium ring.\n First, take a red car");
	m_missionInfo.emplace_back("Now, take a yellow car and put it next to the red car you have taken");
	m_missionInfo.emplace_back("Now, take a police car and put it next to other cars you have taken");
	m_missionInfo.emplace_back("Good. Now, for the last car, take a Lamborgini and put it next to the Helicopter.\n Remember, there is only one in the city so make sure you have enough fuel to get there or you will fail! \n ");

	m_stadium.setPosition(3090, 835);
	m_stadium.setSize(sf::Vector2f(895, 420));
	m_heliPad.setPosition(2270, 1050);
	m_heliPad.setSize(sf::Vector2f(290, 320));
	m_missionRect = m_stadium.getGlobalBounds();

	m_carTypes.emplace_back(typeid(RedCar));
	m_carTypes.emplace_back(typeid(YellowCar));
	m_carTypes.emplace_back(typeid(PoliceCar));
	m_carTypes.emplace_back(typeid(Lamborgini));

	setText(m_missionInfo[m_missionStep]);
}

//Function to handle the collision of the player with the mission objects.
//Collions happens if the car is the type the step required and only if it is in Taken State
//And if the previous cars are in place
void MissionStealLamborgini::handleCollision()
{
	if (!m_player.getPlayerCar())
		return;

	if (typeid(*m_player.getPlayerCar().get()) == m_carTypes[m_missionStep])
	{
		// Advance until the last step
		m_missionStep++;
		std::cout << m_missionStep << std::endl;
		if (m_missionStep == m_carTypes.size())
		{
			m_missionAcheived = true;
			setText("Mission Accomplished");
			return;
		}
		if (m_carTypes[m_missionStep] == typeid(Lamborgini))
		{
			m_missionRect = m_heliPad.getGlobalBounds();
		}
		setText(m_missionInfo[m_missionStep]);
	}
}

bool MissionStealLamborgini::m_registerMission = ObjectFactory::registerMission([](Player& player) ->
	std::unique_ptr<Mission> { return std::make_unique<MissionStealLamborgini>(player); });