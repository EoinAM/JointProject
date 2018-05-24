#ifndef GAMEOVER
#define GAMEOVER

#include "SFML\Graphics.hpp"
#include "Highscores.h"
#include "UiLibrary.h"
#include "Xbox360Controller.h"

class GameOverScreen
{
public:
	GameOverScreen(sf::Font &t_font, HighscoreScreen t_highscoreScreen);
	~GameOverScreen();

	void update(Xbox360Controller t_controller, int t_newScore, sf::Time & t_deltaTime);
	void render(sf::RenderWindow &t_window, bool & t_win);
	bool m_switchMainMenu = false;
private:
	void enterName();
	sf::Font m_font;
	HighscoreScreen m_highscoreScreen;
	Label m_gameOverLabel;
	Label m_loseLabel;
	Label m_winLabel;
	Label m_mainMenuLabel;
	Label m_scoreLabel;
	Label m_playerNameLabel;
	std::string m_playerName = "Jimmy";
	Button m_mainMenuButton;
	bool scoreCalled = false;
};

#endif // !GAMEOVER
