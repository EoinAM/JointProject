#include "HeatSeaker.h"


void HeatSeaker::init(sf::Texture const & t_texture, float t_x, float t_y) 
{
	m_position = { t_x, t_y };
	//should be m_bullet.whatever
	m_body.setOrigin(m_body.getLocalBounds().width * .5, m_body.getLocalBounds().height * .5);
	m_body.setPosition(m_position);
	m_body.setTexture(&t_texture);
	//m_body.setTextureRect(sf::IntRect(0, 0, 18, 6));
	m_body.setFillColor(sf::Color::Magenta);
	m_speed = M_MAX_SPEED;
}



bool HeatSeaker::update(sf::Time const & t_dTime, sf::Vector2f t_target)
{
	if (!inUse())
	{
		return false;
	}

	/*sf::Vector2f newPos(position.x + std::cos(m_body.getRotation() * 3.141592653 / 180.0) * m_speed * (t_dTime.asMilliseconds() / 1000.0),
		position.y + std::sin(m_body.getRotation() * 3.141592653 / 180.0) * m_speed * (t_dTime.asMilliseconds() / 1000.0));*/

	//sets speed to 0 if the missile is not on screen
	if (onScreenCheck())
	{
		m_speed = 0;
	}

	m_direction.x = t_target.x - m_position.x;
	m_direction.y = t_target.y - m_position.y;

	m_hypotenuse = sqrt(m_direction.x * m_direction.x + m_direction.y * m_direction.y);
	m_direction.x /= m_hypotenuse;
	m_direction.y /= m_hypotenuse;

	m_position.x += m_direction.x * m_speed;
	m_position.y += m_direction.y * m_speed;


	m_body.setPosition(m_position);

	return m_speed == M_MAX_SPEED;
}

bool HeatSeaker::inUse() const
{
	return m_speed == M_MAX_SPEED;
}

void HeatSeaker::setRotation(double t_angle)
{
	m_body.setRotation(t_angle);
}

bool HeatSeaker::onScreenCheck()
{
	if (m_body.getPosition().x > 1910 || m_body.getPosition().x < 0
		|| m_body.getPosition().y > 1070 || m_body.getPosition().y < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
