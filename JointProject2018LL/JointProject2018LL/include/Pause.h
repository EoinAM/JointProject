#ifndef PAUSE
#define PAUSE

#include "SFML\Graphics.hpp"
#include "Highscores.h"
#include "UiLibrary.h"
#include "Xbox360Controller.h"
#include "Global.h"

class Pause
{
public:
	Pause(sf::Font &t_font);
	~Pause();
	void update(Xbox360Controller &t_controller, sf::Time t_d, GameState & t_gamestate);
	void render(sf::RenderWindow &t_window);
	bool m_resume = false;
	bool m_restart = false;

private:
	static const int M_MAX_BUTTONS = 3;
	Button m_pauseButton[M_MAX_BUTTONS];
	const std::string M_LABEL_STRINGS[M_MAX_BUTTONS] = { "Resume", "Restart" , "Exit"};
	int m_currentButton = 0;
	int m_previousButton = 2;
};

#endif
