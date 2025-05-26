#pragma once
#include <SFML/Graphics.hpp>
#include "exceptions.h"
#include <SFML/Audio.hpp>
//this class is a singleton

enum class GameSounds
{
	GAME_OVER = 0,
	WIN,
	GAME_PRESENT_SOUND,
	CAR_STOLEN_SOUND,
	POLICE_SEIREN_SOUND
}; 
 
enum class GameTextures
{
	NEW_GAME = 0,
	MAP,
	PLAY_BUTTON,
	EXIT_BUTTON,
	BEKGROUND_MENU,
	ROAD_MAP,
	OBJECTS,
	LEVEL_WON,
	LEVEL_LOST,
	GAME,
	PACKAGE,
	DELIVERY,
	IMMUNITY,
	LAST// This must remain the last item
};

class Graphics
{
public:
	~Graphics() = default;
	static Graphics& getInstance();
	sf::RenderWindow& getWindow();
	sf::Image& getPixelMap() { return m_pixelMap; }
	sf::Image&	getRoadMap() { return m_roadMap; }
	sf::Texture& getTexture(GameTextures texture) { return m_textures[int(texture)]; }
	sf::Vector2f getWindowCenter() { return sf::Vector2f(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f); }
	sf::Font getArialFont() { return m_arialFont; };
	sf::SoundBuffer& getSoundBuffer(GameSounds gameSound) { return m_soundBuffer[int(gameSound)]; };
	sf::Music& getMusic() { return m_music; }
private:
	Graphics();
	void initVectorTexture();
	Graphics(const Graphics&) = default; //copy c-tor
	sf::RenderWindow m_window;
	std::vector <sf::Texture> m_textures;
	sf::Font m_arialFont;
	sf::Image m_pixelMap;
	sf::Image m_roadMap;
	std::vector < sf::SoundBuffer> m_soundBuffer;
	sf::Music m_music;
};