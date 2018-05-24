#include "HUD.h"






HUD::HUD(sf::Font & t_font, rh::ResourceHolder & t_resourceHolder):
	m_resourceHolder(t_resourceHolder)
{
	for (int i = 0; i < 4; i++)
	{
		m_HUDText[i].setCharacterSize(20);
		m_HUDText[i].setFillColor(sf::Color::White);
		m_HUDText[i].setFont(t_font);
	}

	m_HUDText[0].setPosition(50, 40);
	m_HUDText[0].setString("Fuel");
	m_HUDText[1].setPosition(50, 80);
	m_HUDText[1].setString("Score: ");
	m_HUDText[2].setPosition(1380, 40);
	m_HUDText[2].setString("Horizontal Speed: ");
	m_HUDText[3].setPosition(1380, 80);
	m_HUDText[3].setString("Vertical Speed: ");

	m_fuelRectangle.setFillColor(sf::Color::Green);
	m_fuelRectangle.setPosition(115,40);

	m_HUDTexture = m_resourceHolder.m_textureHolder["HUDTexture"];
	
	for (int i = 0; i < 2; i++)
	{
		m_HUDRectangle[i].setTexture(&m_HUDTexture);
		m_HUDRectangle[i].setSize(sf::Vector2f(650, 300));
		m_HUDRectangle[i].setFillColor(sf::Color(255, 255, 255, 120));
	}

	m_HUDRectangle[0].setPosition(-30, -10);
	m_HUDRectangle[1].setPosition(1930, -10);
	m_HUDRectangle[1].setScale(-1, 1);
}

HUD::~HUD()
{
}

void HUD::update(Xbox360Controller t_controller, float t_fuel, float t_horizontalSpeed, float t_verticalSpeed, int t_score)
{
	if (t_fuel > 400)
	{
		t_fuel = 400;
	}
	if (t_fuel < 0)
	{
		t_fuel = 0;
	}
	if (t_controller.m_currentState.A)
	{
		t_fuel -= 1;
	}
	m_fuelRectangle.setSize(sf::Vector2f(t_fuel, 20));

	m_HUDText[1].setString("Score: " + std::to_string(t_score));
	m_HUDText[2].setString("Horizontal Speed: " + std::to_string(t_horizontalSpeed));
	m_HUDText[3].setString("Vertical Speed: " + std::to_string(t_verticalSpeed));
}

void HUD::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_HUDRectangle[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		t_window.draw(m_HUDText[i]);
	}
	t_window.draw(m_fuelRectangle);
}
