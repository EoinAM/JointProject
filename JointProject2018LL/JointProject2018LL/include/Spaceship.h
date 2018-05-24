#ifndef SPACESHIP
#define SPACESHIP

#include "SFML\Graphics.hpp"
#include "Xbox360Controller.h"
#include "Physics.h"
#include "ResourceHolder.h"
#include "CollisionDetector.h"
#include "Thor\Vectors.hpp"
#include "Structs.h"

#define PI 3.141592653

class Spaceship
{
public:
	Spaceship(const sf::Vector2f t_position, rh::ResourceHolder & t_resourceHolder, const sf::Vector2f t_size, const float t_weight);
	~Spaceship();

	void update(const sf::Time t_deltaTime, const Xbox360Controller &t_controller);
	void render(sf::RenderWindow &t_window);

	void reset(sf::Vector2f t_position);

	sf::RectangleShape m_body;
	sf::CircleShape m_shipCircle;
	sf::Vector2f m_position{ 350, 450 };
	sf::Vector2f m_velocity{ 0,0 };

	void initStructs();
	void updateStructs();
	/// <summary>
	/// Struct objects setups
	/// </summary>
	fuel m_fuelTank;
	landingGear m_landingGear;
	mainThruster m_Thruster;
	sideThruster m_sideThrusters[2];

	rh::ResourceHolder & m_resourceHolder;

	float m_rotation{ 0 };

private:
	void checkShipRotate();

	sf::Texture & m_shipTexture;
	
	float m_mass = 0;

	sf::Vector2f m_acceleration{ 0,0 };
	
	sf::Vector2f m_thrust{ 0,0 };

	sf::Vector2f m_originalHeading{ 0,-50 };
	sf::Vector2f m_headingVector{ m_originalHeading };

	float m_adjustmentMax{ 1.f };
	sf::Vector2f m_adjustment{ m_adjustmentMax,0 };
	
};
#endif
