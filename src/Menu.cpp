#include "Menu.h"

Menu::Menu() : m_openPic(), m_texture(Graphics::getInstance().getTexture(GameTextures::GAME))
{
	m_openPic.setTexture(m_texture);
	auto winSize = Graphics::getInstance().getWindow().getSize();
	m_openPic.setScale(winSize.x / m_openPic.getLocalBounds().width,
		winSize.y / m_openPic.getLocalBounds().height);	
}

void Menu::draw()
{
	Graphics::getInstance().getInstance().getWindow().draw(m_openPic);
	for (auto& button : m_option)
	{
		button.first->draw();
	}
}

//This function is for the main event loop of a game menu, displaying the menu,
//drawing menu items, and handling various events related to the user's interactions with the menu.
void Menu::displayMenu()
{
	sf::Event e;
	while (true)
	{
		Graphics::getInstance().getWindow().clear();
		draw();
		Graphics::getInstance().getWindow().display();
		while (Graphics::getInstance().getWindow().pollEvent(e))
		{
			switch (e.type)
			{
				case sf::Event::Closed:
				{
					Graphics::getInstance().getWindow().close();
					return;
				}
				case sf::Event::MouseButtonReleased:
				{
					auto location = Graphics::getInstance().getWindow().mapPixelToCoords({ e.mouseButton.x, e.mouseButton.y });
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						for (int i = 0; i < m_option.size(); i++)
						{
							if (m_option[i].first->intersect(location))
							{
								m_option[i].second->execute();
								return;
							}
						}
					}
				}
			}
		}
	}
}


void Menu::add(std::pair<std::unique_ptr<BaseButton>, std::unique_ptr<Command>> c)
{
	m_option.emplace_back(std::pair < std::unique_ptr<BaseButton>, std::unique_ptr<Command>>(move(c.first), move(c.second)));
}