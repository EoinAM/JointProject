#include "Missile.h"

Missile::Missile()
{
	m_missileBody.setFillColor(sf::Color::Magenta);
	m_missileBody.setPosition(m_position);
	m_missileBody.setSize(sf::Vector2f(10, 10));
	m_missileBody.setOrigin(m_missileBody.getSize().x * .5, m_missileBody.getSize().y * .5);

}


Missile::~Missile()
{
}

void Missile::update()
{
	

	m_direction.x = m_target.x - m_position.x;
	m_direction.y = m_target.y - m_position.y;

	m_hypotenuse = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	m_direction.x /= m_hypotenuse;
	m_direction.y /= m_hypotenuse;

	m_position.x += m_direction.x * m_speed;
	m_position.y += m_direction.y * m_speed;

	m_missileBody.setPosition(m_position);
}

void Missile::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_missileBody);
}
