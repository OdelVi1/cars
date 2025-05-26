#pragma once
#include "Command.h"
#include "Game.h"

class Game;
class Play:public Command
{
public:
	Play(Game&);
	virtual ~Play()=default;
	 virtual void execute() override;
private:
	Game& m_game;

};
