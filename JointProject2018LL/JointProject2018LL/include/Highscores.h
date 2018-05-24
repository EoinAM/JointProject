#ifndef HIGHSCORES
#define HIGHSCORES

#include <SFML\Graphics.hpp>
#include "LevelLoader.h"
#include "UiLibrary.h" 
#include "Xbox360Controller.h"
#include "Global.h"

class HighscoreScreen
{
public:
	HighscoreScreen(GameData & t_level, sf::Font &t_font);
	~HighscoreScreen();

	void update();
	void render(sf::RenderWindow &t_window);
	void newScore(float t_newScore, std::string t_newName);
	void buttonPress(Xbox360Controller t_controller, GameState & t_gamestate);
private:
	GameData m_level;
	LevelLoader m_loader;
	static const int M_MAX_STORED_SCORES = 10;
	Label m_highscoreLabel[M_MAX_STORED_SCORES];
	Label m_title;
	std::string m_playerName[M_MAX_STORED_SCORES];
	//the time taken to complete the mission
	int m_highscore[M_MAX_STORED_SCORES];
	sf::Font m_font;
};


#endif // !HIGHSCORES

