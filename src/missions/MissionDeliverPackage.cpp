#include "missions\MissionDeliverPackage.h"


MissionDeliverPackage::MissionDeliverPackage(Player& player) : Mission("Deliver Package", player, sf::Vector2f(2500, 3000)),
	m_packageTexture(Graphics::getInstance().getTexture(GameTextures::PACKAGE)),
	m_deliveryTexture(Graphics::getInstance().getTexture(GameTextures::DELIVERY)),
	m_packagePickup(m_packageTexture), m_packageDelivery(m_deliveryTexture)
{
	m_packagePickup.scale(30.f / m_packagePickup.getGlobalBounds().width, 30.f / m_packagePickup.getGlobalBounds().width);
	m_packagePickup.setPosition(3716.f, 2397.f); //at parking lot
	
	m_packageDelivery.scale(30.f / m_packageDelivery.getGlobalBounds().width, 30.f / m_packageDelivery.getGlobalBounds().width);
	m_packageDelivery.setPosition(1038.f, 2130.f); //near the pool
	m_missionInfo.emplace_back("Hi. you need to deliver the package near the orange traffic Cone in the parking lot\n more instructions will follow once you have it");
	m_missionInfo.emplace_back("Good. You have collected the package.\n Now, go to the delivery destination near the pool and deliver the package!");
	setText(m_missionInfo[STEP_ZERO]); //new mission start from step zero
	m_spritePtr = std::make_unique<sf::Sprite>(m_packagePickup);
}

//Function to handle the collision of the player with the package pickup and delivery points.
void MissionDeliverPackage::handleCollision()
{
	if (m_missionStep == STEP_ZERO)
	{
		m_missionStep++;
		setText(m_missionInfo[m_missionStep]);
		m_spritePtr = std::make_unique<sf::Sprite>(m_packageDelivery);
	}
	else if (m_missionStep == STEP_ONE)
	{
		m_missionAcheived = true;
		setText("Mission Accomplished");
	}
}

void MissionDeliverPackage::draw()
{
	sf::View currentView = Graphics::getInstance().getWindow().getView();
	// Set the view to the partial view and draw it
	Graphics::getInstance().getWindow().setView(m_partialMap.getScreenMapView());
	Graphics::getInstance().getWindow().draw(*m_spritePtr.get());
	// Restore to default view
	Graphics::getInstance().getWindow().setView(currentView);

	Mission::draw();
}

//Static member that registers this mission in the ObjectFactory
bool MissionDeliverPackage::m_registerMission = ObjectFactory::registerMission([](Player& player) ->
	std::unique_ptr<Mission> { return std::make_unique<MissionDeliverPackage>(player); });