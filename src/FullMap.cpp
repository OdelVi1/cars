#include "FullMap.h"

//class is responsible for managing the visual representation of the entire map.
//The map is rendered in a smaller size in a certain area of the window as a minimap.
FullMap::FullMap() :m_entireMap(Graphics::getInstance().getTexture(GameTextures::MAP)), m_screenView()
{
	m_entireMap.setTexture(Graphics::getInstance().getTexture(GameTextures::MAP));
	//m_entireMap.setPosition(float(Graphics::getInstance().getWindow().getSize().x) - REDUCED_X, float(Graphics::getInstance().getWindow().getSize().y) - REDUCED_Y);
	m_entireMap.setScale(0.15f, 0.15f);
	m_entireMap.setColor(sf::Color(m_entireMap.getColor().r, m_entireMap.getColor().g, m_entireMap.getColor().b, TRANSPARENCY));

	m_screenView.setViewport(sf::FloatRect(0.75f, 0.75f, 0.25f, 0.25f));
};

void FullMap::draw()
{
	//m_screenView.setCenter(playerPosition);
	sf::View currentView = Graphics::getInstance().getWindow().getView();
	// Set the view to the partial view and draw it
	Graphics::getInstance().getWindow().setView(m_screenView);
	Graphics::getInstance().getWindow().draw(m_entireMap);
	Graphics::getInstance().getWindow().setView(currentView);
}