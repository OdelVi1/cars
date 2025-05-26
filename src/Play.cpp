#include "Play.h"

Play::Play(Game& game)
	:m_game(game)
{
}

void Play::execute()
{
	m_game.newGame();
}
