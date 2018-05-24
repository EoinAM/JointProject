#include "MissileBase.h"

MissileBase::MissileBase(GameData &t_level, sf::Vector2f t_pos)
{
	m_base.setSize(sf::Vector2f(20, 20));
	m_base.setFillColor(sf::Color::Red);
	m_base.setOrigin(10, 10);
	//m_base.setTexture();
	m_base.setPosition(t_pos);
}

MissileBase::~MissileBase()
{
}

void MissileBase::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_base);
}
