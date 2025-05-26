#include "Graphics.h"

//The Graphics class is a singleton that manages game resources such as textures,
//fonts, sounds, and the game window.

Graphics::Graphics()
	:m_window(sf::VideoMode(1500, 1000), "GTA",sf::Style::Fullscreen),
	m_textures(int(GameTextures::LAST), sf::Texture()),m_arialFont(),m_pixelMap(),
	m_roadMap(), m_soundBuffer(6, sf::SoundBuffer()), m_music()
{
	m_window.setFramerateLimit(60);
	initVectorTexture();
	m_pixelMap.loadFromFile("5000map.png");
	m_roadMap.loadFromFile("roads_map.png");

	if (!m_arialFont.loadFromFile("ARIAL.TTF"))
	{
		throw FontLoadException("ARIAL Font not found");
	}
	m_soundBuffer[int(GameSounds::GAME_OVER)].loadFromFile("game_over.wav");
	m_soundBuffer[int(GameSounds::WIN)].loadFromFile("win.wav");
	m_soundBuffer[int(GameSounds::GAME_PRESENT_SOUND)].loadFromFile("present.wav");
}

void Graphics::initVectorTexture()
{
	if (!m_textures[int(GameTextures::MAP)].loadFromFile("5000map.png")||
		!m_textures[int(GameTextures::PLAY_BUTTON)].loadFromFile("play.png")||
		!m_textures[int(GameTextures::ROAD_MAP)].loadFromFile("roads_map.png") ||
		!m_textures[int(GameTextures::OBJECTS)].loadFromFile("objects.png") ||
		!m_textures[int(GameTextures::LEVEL_WON)].loadFromFile("win.png") ||
		!m_textures[int(GameTextures::LEVEL_LOST)].loadFromFile("lose.png") ||
		!m_textures[int(GameTextures::GAME)].loadFromFile("game.png") ||
		!m_textures[int(GameTextures::PACKAGE)].loadFromFile("package.png") || 
		!m_textures[int(GameTextures::DELIVERY)].loadFromFile("winflag.png"))
	{
		throw ImageLoadException("Image not found");
	};
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		//m_textures[i].setSmooth(false);
	}
}

Graphics& Graphics::getInstance()
{
	static Graphics inst;
	return inst;
}
sf::RenderWindow& Graphics::getWindow()
{
	return m_window;
}