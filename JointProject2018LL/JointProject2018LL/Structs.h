#pragma once
#include <SFML\Graphics.hpp>

struct fuel
{
	sf::RectangleShape m_tank;
	sf::Texture m_fuelTexture;
	float capacity;
	float weight;
};

struct landingGear
{
	sf::RectangleShape m_landingbody;
	sf::Texture landingGearSprite;
	float breakSpeed;
	float weight;
};

struct mainThruster
{
	sf::RectangleShape m_mainThrusterBody;
	sf::Texture mainThrusterSprite;
	sf::Vector2f size;
	sf::Vector2f thrust;
	float weight;
	float fuelConsumption;
};

struct sideThruster
{
	sf::RectangleShape m_sideThrusterBody;
	sf::Texture sideThrusterTexture;
	sf::Vector2f adjustment;
	sf::Vector2f size;
	float fuelComsumption;
	float weight;
};