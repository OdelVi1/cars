#include "Game.h"

void Game::newGame()
{
	Graphics::getInstance().getMusic().openFromFile("background_music.wav");
	Graphics::getInstance().getMusic().setLoop(true);
	Player player;
	for (auto& mission : ObjectFactory::createMissions(player))
	{
		Level level = Level(player, *mission.get());
		Graphics::getInstance().getMusic().play();
		level.run();
		Graphics::getInstance().getMusic().stop();
		if (!mission->isMissionAchieved())
		{
			std::cout << "Level is over\n";
			break;
		}
	}
	std::cout << "Game is over\n";
}

void Game::run()
{
	Menu menu;
	menu.add(std::pair<std::unique_ptr<BaseButton>, std::unique_ptr<Play>>(std::make_unique<BaseButton>(GameTextures::PLAY_BUTTON), std::make_unique<Play>(*this)));
	while (Graphics::getInstance().getWindow().isOpen())
	{
		menu.displayMenu();
	}
}

