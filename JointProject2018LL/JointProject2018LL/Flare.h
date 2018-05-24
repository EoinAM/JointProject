#pragma once
#ifndef FLARE
#define FLARE

#include <SFML\Graphics.hpp>
#include "UiLibrary.h"
#include "Xbox360Controller.h"
#include "Physics.h"

class Flare
{
public:
	Flare();
	~Flare();

	void update(Xbox360Controller &t_controller, sf::Time t_deltaTime);
	void render(sf::RenderWindow &t_window);
	void reset();
	bool m_flareAlive;
	sf::RectangleShape m_flareBody;
	sf::Vector2f m_flarePosition{};

	sf::Vector2f m_velocity{ 0,0 };
	sf::Vector2f m_acceleration{ 0,-120 };
	float rectWeight = 100;
	sf::Vector2f m_thrust{ 0,0 };
};
#endif
