#include "Platform.h"

Platform::Platform()
{
	m_platform.setFillColor(sf::Color::Green);
	m_platformCircle.setPosition(m_platform.getPosition());
	m_platformCircle.setRadius(150);
	m_platformCircle.setOrigin(m_platformCircle.getRadius(), m_platformCircle.getRadius());
}


Platform::~Platform()
{
}

void Platform::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_platform);	
}

void Platform::updateCollissions()
{
	m_platformAABB.max = c2V(m_platform.getPosition().x, m_platform.getPosition().y);
	m_platformAABB.min = c2V(m_platform.getPosition().x + (m_platform.getGlobalBounds().width), m_platform.getPosition().y + (m_platform.getGlobalBounds().height));
}
