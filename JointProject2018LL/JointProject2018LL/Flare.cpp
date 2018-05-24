#include "Flare.h"



Flare::Flare()
{
	m_flareBody.setFillColor(sf::Color::Red);
	m_flareBody.setSize(sf::Vector2f(20, 30));
	m_flareBody.setOrigin(0, m_flareBody.getGlobalBounds().height);
}


Flare::~Flare()
{
}

void Flare::update(Xbox360Controller & t_controller, sf::Time t_deltaTime)
{
	m_flarePosition = (m_flarePosition + m_velocity * t_deltaTime.asSeconds() + 0.5f * m_acceleration * (t_deltaTime.asSeconds() * t_deltaTime.asSeconds()));
	applyGravity(rectWeight, m_acceleration, m_thrust);
	m_velocity = m_velocity + (m_acceleration * t_deltaTime.asSeconds());
	m_flareBody.setPosition(m_flarePosition);
}

void Flare::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_flareBody);
}

void Flare::reset()
{
	m_flareAlive = false;
	m_velocity = { 0,0 };
}
