#include "GameOverScreen.h"

GameOverScreen::GameOverScreen(sf::Font &t_font, HighscoreScreen t_highscoreScreen):
	m_font(t_font),
	m_highscoreScreen(t_highscoreScreen)
{
	m_gameOverLabel.init("GAMEOVER", sf::Vector2f(960, 40), m_font, 100, sf::Color::Yellow);
	m_winLabel.init("YOU WIN", sf::Vector2f(960, 140), m_font, 100, sf::Color::Yellow);
	m_loseLabel.init("YOU LOSE", sf::Vector2f(960, 140), m_font, 100, sf::Color::Yellow);
	m_mainMenuLabel.init("MAINMENU", sf::Vector2f(960, 895), m_font, 24, sf::Color::Red);
	m_scoreLabel.init("SCORE : ", sf::Vector2f(960, 540), m_font, 24, sf::Color::Red);
	m_playerNameLabel.init("NAME : ", sf::Vector2f(960, 580), m_font, 24, sf::Color::Red);
	m_mainMenuButton.init(sf::Vector2f(960, 900), sf::Vector2f(200, 50), sf::Texture(), m_mainMenuLabel, true, sf::Color::Green);
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::update(Xbox360Controller t_controller, int t_newScore, sf::Time & t_deltaTime)
{
	m_mainMenuButton.update(t_deltaTime, t_controller, 5);
	if (t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		m_switchMainMenu = true;
	}
	m_scoreLabel.string("SCORE : " + std::to_string(t_newScore));
	m_playerNameLabel.string("NAME : " + m_playerName);
	enterName();
	if (!scoreCalled)
	{
		//calls the function to add a new score to the highscore table.
		m_highscoreScreen.newScore(t_newScore, m_playerName);
		scoreCalled = true;
	}
}


//bool determines if the win or lose text gets displayed.
void GameOverScreen::render(sf::RenderWindow & t_window, bool & t_win)
{
	m_gameOverLabel.render(t_window);
	m_scoreLabel.render(t_window); 
	m_playerNameLabel.render(t_window);
	m_mainMenuButton.render(t_window);
	m_mainMenuLabel.render(t_window);
	if (t_win)
	{
		m_winLabel.render(t_window);
	}
	else
	{
		m_loseLabel.render(t_window);
	}
}

//will call eoins keyboard function that takes input and will return the entered string which
//will then be assigned to m_playerName.
void GameOverScreen::enterName()
{
	//m_playerName = keyboard();
}
