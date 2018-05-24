#ifndef MISSIONSETUPSCREEN
#define MISSIONSETUPSCREEN

#include <SFML\Graphics.hpp>
#include "UiLibrary.h"
#include "Xbox360Controller.h"
#include "Spaceship.h"
#include "ResourceHolder.h"

class MissionSetUpScreen
{
public:
	MissionSetUpScreen(sf::Font &t_font, Spaceship & t_spaceship, rh::ResourceHolder & t_resources);
	~MissionSetUpScreen();
	void render(sf::RenderWindow &t_window);
	void update(sf::Time t_d, Xbox360Controller t_controller);
	bool m_finishedSetUp{ false };
	bool m_returnToMenu{ false };

	void setupTextures();
	void compareTextures();

private:
	int m_sideEngineInUse{ 1 };
	int m_fuelInUse{ 1 };
	int m_landerInUse{ 1 };
	int m_thrusterInUse{ 1 };

	rh::ResourceHolder & m_resources;

	sf::Font & m_font;

	static const int M_MAXUPGRADES = 18;
	static const int M_MAXBUTTONS = 2;
	static const int M_MAXNAMES = 6;
	static const int M_MAXTIERS = 3;
	static const int M_MAXSHIPBUTTONS = 4;
	
	sf::RectangleShape m_ship;
	
	Spaceship & m_spaceship;

	Button m_upgrades[M_MAXUPGRADES];
	Label m_label[M_MAXBUTTONS];
	Label m_names[M_MAXNAMES];
	Label m_tiers[M_MAXTIERS];
	
	const std::string m_string[M_MAXBUTTONS] = { "Start", "Exit" };
	const std::string m_nameString[M_MAXNAMES] = { "Fuel Tank", "Side Thrusters", "Main Thruster", "Landing Gear", "Confirm", "Main Menu" };
	const std::string m_tierString[M_MAXTIERS] = { "Common", "Rare", "Legendary" };
	
	int m_currentButton = 12;
	int m_previousButton = 15;
	
	int j = 0;
	int k = 0;
};
#endif