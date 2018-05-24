#include "Settings.h"



/// <summary>
/// default constructor, needs to be passed a font
/// </summary>
/// <param name="t_font">font used in buttons and labels</param>
SettingsScreen::SettingsScreen(sf::Font &t_font)
{
	m_sliderMusic.init(sf::Vector2f(600, 300), 500, 100.0f, BarOrientation::Horizontal, false, sf::Color::Blue);
	m_sliderSFX.init(sf::Vector2f(600, 500), 500, 100.0f, BarOrientation::Horizontal, false, sf::Color::Blue);
	m_checkBox.init(sf::Vector2f(600, 700), sf::Vector2f(10, 10), false, sf::Color::Blue);

	for (int i = 0; i < 3; i++)
	{
		m_label[i].init(m_labelText[i], sf::Vector2f(500, 300 + (200 * i)), t_font, 20, sf::Color::Red);
	}
}

/// <summary>
/// default destructor
/// </summary>
SettingsScreen::~SettingsScreen()
{
}

/// <summary>
/// update the settings screen data
/// </summary> 
/// <param name="t_dTime">the time that has passed since the last update</param>
/// <param name="t_controller">controller input handler</param>
void SettingsScreen::update(sf::Time d_t, Xbox360Controller t_controller, GameState & t_gamestate)
{
	//update all ui elements
	m_checkBox.update(d_t, t_controller, 10);
	m_sliderMusic.update(d_t, t_controller, 10);
	m_sliderSFX.update(d_t, t_controller, 10);

	//update which ui element is highlighted
	if (m_currentButton == 0)
	{
		m_sliderMusic.highlighted(true);
		m_sliderSFX.highlighted(false);
		m_checkBox.highlighted(false);
	}

	else if (m_currentButton == 1)
	{
		m_sliderMusic.highlighted(false);
		m_sliderSFX.highlighted(true);
		m_checkBox.highlighted(false);
	}
	
	else if (m_currentButton == 2)
	{
		m_sliderMusic.highlighted(false);
		m_sliderSFX.highlighted(false);
		m_checkBox.highlighted(true);
	}
	
	//depending on the controller input change which button is active
	if (t_controller.m_currentState.DpadDown && !t_controller.m_previousState.DpadDown)
	{
		m_currentButton ++;
	}

	if (t_controller.m_currentState.DpadUp && !t_controller.m_previousState.DpadUp)
	{
		m_currentButton--;
	}

	if (m_currentButton < 0)
	{
		m_currentButton = 2;
	}

	if (m_currentButton > 2)
	{
		m_currentButton = 0;
	}
	if (t_controller.m_currentState.Back)
	{
		t_gamestate = GameState::MENU;
	}
}

/// <summary>
/// render all of the elements of the settings screen object
/// </summary>
/// <param name="t_window">render window</param>
void SettingsScreen::render(sf::RenderWindow &t_window)
{
	m_sliderMusic.render(t_window);
	m_sliderSFX.render(t_window);
	m_checkBox.render(t_window);
	for (int i = 0; i < 3; i++)
	{
		m_label[i].render(t_window);
	}
}
