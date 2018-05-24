#ifndef GAME
#define GAME

#define COLOR_NORMAL sf::Color(41, 128, 185)
#define COLOR_HIT sf::Color(231, 76, 60)
#define NO_OF_POINTS 45

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML\Graphics\Shader.hpp>
#include "Xbox360Controller.h"

#include "Global.h"
#include "MainMenu.h"

#include "LevelLoader.h"
#include "ResourceHolder.h"

#include "CollisionDetector.h"
#include "Physics.h"

#include "Spaceship.h"
#include "Missile.h"
#include "Platform.h"
#include "Flare.h"
#include "HeatSeakerPool.h"
#include "MissileBase.h"

#include "MainMenu.h"
#include "HelpScreen.h"
#include "Settings.h"
#include "Highscores.h"
#include "MissionSetUp.h"
#include "GameOverScreen.h"
#include "Pause.h"
#include "HUD.h"

#include "Animation.h"

//#include <tinyc2.h>
#include <Tinyc2Debug.hpp>

enum class Level
{
	LEVELONE,
	LEVELTWO
};

class Game
{
public:
	/// <summary>
	/// default constructor to be used
	/// </summary>
	/// <param name="t_level">the level data loaded before the game starts</param>
	Game(GameData & t_level);
	/// <summary>
	/// default destructor
	/// </summary>
	~Game();

	/// <summary>
	/// main method for game, contains game loop
	/// </summary>
	void run();

	rh::ResourceHolder m_resourceLoader;

	LevelLoader m_loader;

	c2Poly m_landPolys[20];
	c2Poly m_landPolyslvl2[49];
	c2Poly m_shipPoly;
	c2Poly m_landerPoly;
	c2Manifold m_shipLandManifold;

	GameData m_level;

private:
	/// <summary>
	/// Process user input
	/// </summary>
	void processEvents();
	/// <summary>
	/// update the game objects
	/// </summary>
	/// <param name="t_deltaTime">time since last update</param>
	void update(sf::Time t_deltaTime);
	/// <summary>
	/// draw the game objects to the screen
	/// </summary>
	void render();

	/// <summary>
	/// Set up the level
	/// </summary>
	void setupLevel();	
	void setuplvl2();

	void setUpCollisionlvl2();
	/// <summary>
	/// set up the bounding boxes
	/// </summary>
	void setupCollisions();

	void setUpView();
	
	/// <summary>
	/// Check the collisions between the ship poly bounding box and the ground poly bounding box
	/// </summary>
	void landShipCollision();
	void land2ShipCollision();
	void shipPlatformCollision();

	void flareCollisions();

	// main SFML window
	sf::RenderWindow m_window; 
	//Amount of time per frame update
	const sf::Time M_MS_PER_UPDATE{ sf::milliseconds(10) };
	//User controller input handler
	Xbox360Controller m_controller;

	//The state the game is currently in
	GameState m_currentState = { GameState::INTRO };
	GameState m_nextState;

	sf::VertexArray m_Level2Map;
	sf::VertexArray m_mapping;
	//the tiny c2 collision bounding boxes
	c2Poly m_flarePoly;
	c2Manifold m_flareManifold;

	//Debugging collisions
	Tinyc2Debug m_tinyDebug;
	sf::VertexArray m_collisionMap;
	sf::CircleShape m_collisionPoints[47];
	
	//Screen objects
	MainMenuScreen m_mainMenuScreen;
	HighscoreScreen m_highscoreScreen;
	GameOverScreen m_gameOverScreen;
	HelpScreen m_helpScreen;
	SettingsScreen m_settingsScreen;
	MissionSetUpScreen m_missionSetUpScreen;
	Pause m_pause;
	HUD m_HUD;

	// control exiting game
	bool m_exitGame{ false };

	//controls if the game is over, if player lands or dies set to true.
	bool m_gameOver = true; 

	//whether the game is paused or not
	bool m_pauseBool = false;

	//if the ship collides with a pad
	bool m_padHit = false;
	//game objects
	Spaceship m_spaceShip;
	//Missile m_missile;
	Platform m_platform[5];
	Flare m_flare;
	
	//shader data
	float m_shadertimer{ 0 };
	sf::RectangleShape m_shaderBaseRect;
	sf::Shader *m_backgroundShader;

	//camera views for panning and gameplay
	sf::View m_playerCam;
	sf::View m_defaultCam;	

	sf::Vector2f m_toCorners;

	Animation m_introAnimation;
	Animation m_transAnim;
	sf::RectangleShape m_introRect;
	sf::RectangleShape m_transRect;

	int m_currentLevel = 1;
	Level m_currentLevelState = Level::LEVELONE;
	

	HeatSeakerPool m_pool;
	MissileBase m_missileBase;
};

#endif // !GAME