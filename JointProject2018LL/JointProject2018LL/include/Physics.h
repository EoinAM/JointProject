#ifndef PHYSICS
#define PHYSICS

#include <SFML/Graphics.hpp>

//gravity for the land mass we are trying to land on
const sf::Vector2f gravity{0,0.5};

/// <summary>
/// sets the acceleration to be gravity
/// </summary>
/// <param name="t_mass">how massive the object is</param>
/// <param name="t_currentAcceleration">current acceleration</param>
/// <param name="t_externalForce">thrust force/ other force acting up on the object/ could be a sum of all other forces</param>
static void applyGravity(const float t_mass, sf::Vector2f &t_currentAcceleration, sf::Vector2f t_externalForce)
{
	t_currentAcceleration = sf::Vector2f(gravity.x * t_mass, gravity.y * t_mass) + t_externalForce;
}
#endif