#ifndef PLATFORM
#define PLATFORM

#include <SFML\Graphics.hpp>
#include "Xbox360Controller.h"
#include "Global.h"

class Platform
{
public:
	Platform();
	~Platform();

	void render(sf::RenderWindow &t_window);
	sf::RectangleShape m_platform;
	sf::CircleShape m_platformCircle;

	c2AABB m_platformAABB;
	c2Poly m_platformPoly;

	void updateCollissions();
};
#endif
