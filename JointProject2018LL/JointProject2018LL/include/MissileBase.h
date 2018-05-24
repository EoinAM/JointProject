#ifndef MISSILEBASE
#define MISSILEBASE

#include <SFML\Graphics.hpp>
#include <iostream>
#include "LevelLoader.h"

class MissileBase
{
public:
	MissileBase(GameData &t_level, sf::Vector2f t_pos);
	~MissileBase();
	void render(sf::RenderWindow &t_window);
	sf::Vector2f getPosition() { return m_base.getPosition(); }
private:
	sf::RectangleShape m_base;

};

#endif // !MISSILEBASE
