#ifndef MISSILE
#define MISSILE

#include "SFML\Graphics.hpp"
#include "Xbox360Controller.h"


class Missile
{
public:
	Missile();
	~Missile();
	void update();
	void render(sf::RenderWindow &t_window);
	sf::Vector2f m_target{};
	

private:
	sf::RectangleShape m_missileBody;
	sf::Vector2f m_direction;
	sf::Vector2f m_position{10,10};
	float m_speed{ 0.5f };
	float m_hypotenuse{ 0 };
};
#endif
