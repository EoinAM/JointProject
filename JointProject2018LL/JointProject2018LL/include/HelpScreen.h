#ifndef HELPSCREEN
#define HELPSCREEN

#include <SFML\Graphics.hpp>
#include "UiLibrary.h"
#include "Global.h"
class HelpScreen
{
public:
	HelpScreen(sf::Font &t_font);
	~HelpScreen();
	void buttonPress(Xbox360Controller t_controller, GameState & t_gamestate);
	void render(sf::RenderWindow &t_window);

private:
	Label m_helpText;
};
#endif

