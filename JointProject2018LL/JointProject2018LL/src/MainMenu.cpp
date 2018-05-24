#include "MainMenu.h"

MainMenuScreen::MainMenuScreen(sf::Font &t_font)
{
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_button[i].init(sf::Vector2f(950, 400 + (100 * i)), sf::Vector2f(200, 50), sf::Texture(), Label(M_LABEL_STRINGS[i], sf::Vector2f(920, 390 + (100 * i)), t_font, 20, sf::Color::Black), false, sf::Color::Green);
	}

}

MainMenuScreen::~MainMenuScreen()
{
}

void MainMenuScreen::update(Xbox360Controller &t_controller, sf::Time t_deltaTime, GameState & t_gamestate)
{
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_button[i].update(t_deltaTime, t_controller, 10);
	}

	m_button[m_currentButton].highlighted(true);
	m_button[m_previosButton].highlighted(false);

	

	if (t_controller.m_currentState.DpadDown && !t_controller.m_previousState.DpadDown)
	{
		m_currentButton++;
		m_previosButton = m_currentButton - 1;
	}

	if (t_controller.m_currentState.DpadUp && !t_controller.m_previousState.DpadUp)
	{
		m_currentButton--;
		m_previosButton = m_currentButton + 1;
	}

	if (m_currentButton > M_MAX_BUTTONS - 1)
	{
		m_currentButton = 0;
	}

	if (m_currentButton < 0)
	{
		m_currentButton = M_MAX_BUTTONS - 1;
	}

	if (m_button[0].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		t_gamestate = GameState::MISSIONSETUP;
	}

	if (m_button[1].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		t_gamestate = GameState::OPTIONS;
	}

	if (m_button[2].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		t_gamestate = GameState::HELP;
	}

	if (m_button[3].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		t_gamestate = GameState::HIGHSCORESCREEN;
	}

	if (m_button[4].highlighted() && t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		t_gamestate = GameState::EXIT;
	}
}

void MainMenuScreen::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < M_MAX_BUTTONS; i++)
	{
		m_button[i].render(t_window);
	}
}
