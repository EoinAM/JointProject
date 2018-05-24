#include "HeatSeakerPool.h"

void HeatSeakerPool::create(sf::Texture const & t_texture, double t_x, double t_y)
{
	//if no projectiles available, simply re-use the next in sequence.
	if (m_poolFull)
	{
		m_nextAvailable = (m_nextAvailable + 1) % M_POOL_SIZE;
	}
	m_heatSeakers.at(m_nextAvailable).init(t_texture, t_x, t_y);
	m_body[m_nextAvailable] = m_heatSeakers.at(m_nextAvailable).getBody();
	m_missilePos[m_nextAvailable] = m_heatSeakers.at(m_nextAvailable).getPosition();

	m_collisisionPoly.count = 4;
	m_collisisionPoly.verts[0] = c2V(m_missilePos[0].x - m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y - m_body[0].getGlobalBounds().height * .5);
	m_collisisionPoly.verts[1] = c2V(m_missilePos[0].x + m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y- m_body[0].getGlobalBounds().height * .5);
	m_collisisionPoly.verts[2] = c2V(m_missilePos[0].x - m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y+ m_body[0].getGlobalBounds().height * .5);
	m_collisisionPoly.verts[3] = c2V(m_missilePos[0].x + m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y+ m_body[0].getGlobalBounds().height * .5);
	c2MakePoly(&m_collisisionPoly);

	update(sf::Time::Zero, sf::Vector2f(1930, 600));
}

void HeatSeakerPool::update(sf::Time const & t_dTime, sf::Vector2f t_target)
{																												 
	m_collisisionPoly.verts[0] = c2V(m_missilePos[0].x - m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y - m_body[0].getGlobalBounds().height * .5);
	m_collisisionPoly.verts[1] = c2V(m_missilePos[0].x + m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y - m_body[0].getGlobalBounds().height * .5);
	m_collisisionPoly.verts[2] = c2V(m_missilePos[0].x - m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y + m_body[0].getGlobalBounds().height * .5);
	m_collisisionPoly.verts[3] = c2V(m_missilePos[0].x + m_body[0].getGlobalBounds().width * .5, m_missilePos[0].y + m_body[0].getGlobalBounds().height * .5);
	c2MakePoly(&m_collisisionPoly);

	int activeCount = 0;
	m_poolFull = false;
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		//loop through all of the barriers to see if there is a collision
		if (!m_heatSeakers.at(i).update(t_dTime,t_target))
		{
			m_nextAvailable = i;
		}
		else
		{
			activeCount++;
		}
		m_body[i] = m_heatSeakers.at(i).getBody();
		m_missilePos[i] = m_heatSeakers.at(i).getPosition();
	}
	if (M_POOL_SIZE == activeCount)
	{
		m_poolFull = true;
	}


	
}

void HeatSeakerPool::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		// If projectile is active...
		if (m_heatSeakers.at(i).inUse())
		{
			t_window.draw(m_heatSeakers.at(i).m_body);
		}
	}
}

void HeatSeakerPool::setRotation(double t_angle)
{
	for (int i = 0; i < M_POOL_SIZE; i++)
	{
		if (!m_heatSeakers.at(i).inUse())
		{
			m_heatSeakers.at(i).setRotation(t_angle);
		}

	}
	int test = 0;
}