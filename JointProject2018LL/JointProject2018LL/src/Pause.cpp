#include "Pause.h"



Pause::Pause(sf::Font &t_font)
{
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_pauseButton[i].init(sf::Vector2f(950, 400 + (100 * i)), sf::Vector2f(200,50), sf::Texture(), Label(M_LABEL_STRINGS[i], sf::Vector2f(950, 400 + (100 * i)), t_font, 20, sf::Color::Black), false, sf::Color::Green);
	}
}

Pause::~Pause()
{
}

void Pause::update(Xbox360Controller & t_controller, sf::Time t_d, GameState & t_gamestate)
{
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_pauseButton[i].update(t_d, t_controller, 10);
	}

	m_pauseButton[m_currentButton].highlighted(true);
	m_pauseButton[m_previousButton].highlighted(false);

	if (t_controller.m_currentState.DpadDown && !t_controller.m_previousState.DpadDown)
	{
		m_currentButton++;
		m_previousButton = m_currentButton - 1;
	}

	if (t_controller.m_currentState.DpadUp && !t_controller.m_previousState.DpadUp)
	{
		m_currentButton--;
		m_previousButton = m_currentButton + 1;
	}

	if (m_currentButton > M_MAX_BUTTONS - 1)
	{
		m_currentButton = 0;
	}

	if (m_currentButton < 0)
	{
		m_currentButton = M_MAX_BUTTONS - 1;
	}

	if (m_pauseButton[0].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		m_resume = true;
		m_currentButton = 0;
	}

	if (m_pauseButton[1].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		m_restart = true;
	}

	if (m_pauseButton[2].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		t_gamestate = GameState::MENU;
	}
}

void Pause::render(sf::RenderWindow &t_window)
{
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_pauseButton[i].render(t_window);
	}
}
