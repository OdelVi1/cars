#pragma once
#include "Graphics.h"
#include <string>
#include <memory>
#include "Play.h"
#include "BaseButton.h"

class Menu
{
public:
	Menu();
	~Menu() = default;
	void displayMenu();
	void add(std::pair<std::unique_ptr<BaseButton>, std::unique_ptr<Command>>);
private:
	typedef std::pair<std::unique_ptr<BaseButton>, std::unique_ptr<Command>> Option;
	std::vector<Option> m_option;
	void draw();
	sf::Sprite m_openPic;
	sf::Texture m_texture;
	sf::View m_screenView;

};