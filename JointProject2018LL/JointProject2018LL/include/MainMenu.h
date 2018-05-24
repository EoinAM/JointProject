#ifndef MAINMENU
#define MAINMENU

#include <SFML\Graphics.hpp>
#include "UiLibrary.h"
#include "Xbox360Controller.h"
#include "Global.h"

class MainMenuScreen
{
public:
	MainMenuScreen(sf::Font &t_font);
	~MainMenuScreen();

	void update(Xbox360Controller &t_controller, sf::Time t_deltaTime,GameState & t_gamestate);
	void render(sf::RenderWindow &t_window);
private:
	sf::Font m_font;
	static const int M_MAX_BUTTONS = 5;
	Button m_button[M_MAX_BUTTONS];
	const std::string M_LABEL_STRINGS[M_MAX_BUTTONS] = { "Start", "Settings", "Help","Highscores", "Exit" };
	int m_currentButton = 0;
	int m_previosButton = 5;
};

#endif // !MAINMENU

