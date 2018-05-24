#include "HelpScreen.h"



HelpScreen::HelpScreen(sf::Font &t_font)
{
	m_helpText.init("Help", sf::Vector2f(100, 100), t_font, 50, sf::Color::Green);
}


HelpScreen::~HelpScreen()
{
}

void HelpScreen::buttonPress(Xbox360Controller t_controller, GameState & t_gamestate)
{
	if (t_controller.m_currentState.Back)
	{
		t_gamestate = GameState::MENU;
	}
}

void HelpScreen::render(sf::RenderWindow &t_window)
{
	m_helpText.render(t_window);
}

