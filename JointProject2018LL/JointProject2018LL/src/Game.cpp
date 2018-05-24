#include "Game.h"

#define COLOR_NORMAL sf::Color(  97, 106, 107  )
#define COLOR_HIT sf::Color(231, 76, 60)


/// <summary>
/// default constructor to be used
/// </summary>
/// <param name="t_level">the level data loaded before the game starts</param>
Game::Game(GameData & t_level) :
	m_level(t_level),
	m_resourceLoader(t_level),
	m_window{ sf::VideoMode{ ScreenSize::s_screenWidth, ScreenSize::s_screenHeight, 32 }, "SFML Game" , sf::Style::Fullscreen},
	m_mapping(sf::Triangles, 67),
	m_Level2Map(sf::Triangles, 159),
	m_spaceShip(t_level.m_level1.m_startPointPos, m_resourceLoader, m_level.m_ship.m_size, m_level.m_ship.m_weight),
	m_missileBase(t_level, sf::Vector2f(178, 865)),
	m_highscoreScreen(t_level, m_resourceLoader.m_fontHolder["nasalization-rg"]),
	m_missionSetUpScreen(m_resourceLoader.m_fontHolder["nasalization-rg"], m_spaceShip, m_resourceLoader),
	m_pause(m_resourceLoader.m_fontHolder["nasalization-rg"]),
	m_mainMenuScreen(m_resourceLoader.m_fontHolder["nasalization-rg"]),
	m_helpScreen(m_resourceLoader.m_fontHolder["nasalization-rg"]),
	m_settingsScreen(m_resourceLoader.m_fontHolder["nasalization-rg"]),
	m_gameOverScreen(m_resourceLoader.m_fontHolder["nasalization-rg"], m_highscoreScreen),
	m_tinyDebug(m_window),
	m_HUD(m_resourceLoader.m_fontHolder["nasalization-rg"], m_resourceLoader),
	m_introAnimation(m_introRect, 16, m_resourceLoader.m_textureHolder["introAnim"], sf::IntRect(0, 0, 959.62, 538)),
	m_transAnim(m_transRect, 12, m_resourceLoader.m_textureHolder["transAnim"], sf::IntRect(0, 0, 839, 270.5))
{
	m_introAnimation.m_delay = 20;
	m_transAnim.m_delay = 25;

	m_introRect.setSize(sf::Vector2f(ScreenSize::s_screenWidth, ScreenSize::s_screenHeight));
	m_transRect.setSize(sf::Vector2f(ScreenSize::s_screenWidth * 2, ScreenSize::s_screenHeight));
	m_transRect.setTextureRect(sf::IntRect(0, 0, 1678, 541));
	m_transRect.setPosition((m_transRect.getSize().x * .225) * -1, 0);

	//set up the shader Rectangle
	m_shaderBaseRect.setSize(sf::Vector2f(ScreenSize::s_screenWidth / 4, ScreenSize::s_screenHeight / 4));
	m_shaderBaseRect.setScale(4,5);
	m_shaderBaseRect.setPosition(0, -400);
	m_backgroundShader = &m_resourceLoader.m_shaderHolder["BackgroundShader"];
	m_backgroundShader->setUniform("resolution", sf::Vector2f(ScreenSize::s_screenWidth / 3, ScreenSize::s_screenHeight/ 3 ));


	//set up the player camera
	m_playerCam.setSize(sf::Vector2f(800, 600));
	m_playerCam.setCenter(m_spaceShip.m_position);

	//view for the game
	m_defaultCam.setSize(sf::Vector2f(1920, 1080));
	m_defaultCam.setCenter(sf::Vector2f(960, 540));
	m_window.setView(m_window.getDefaultView());

	//set the max number of fps
	m_window.setFramerateLimit(100);
	
	//set up the ground of the level
	setupLevel();

	//set up the bounding boxes of the different objects
	setupCollisions();
	m_pool.create(m_resourceLoader.m_textureHolder["ShipTexture"], m_missileBase.getPosition().x, m_missileBase.getPosition().y);

m_platform[0].m_platform.setSize(sf::Vector2f(150, 40));
m_platform[0].m_platform.setPosition(290, 890);
m_platform[0].m_platform.setRotation(0);
m_platform[1].m_platform.setSize(sf::Vector2f(120, 40));
m_platform[1].m_platform.setPosition(1000, 260);
m_platform[1].m_platform.setRotation(0);
m_platform[2].m_platform.setSize(sf::Vector2f(50, 40));
m_platform[2].m_platform.setPosition(1280, 385);
m_platform[2].m_platform.setRotation(0);
m_platform[3].m_platform.setSize(sf::Vector2f(100, 40));
m_platform[3].m_platform.setPosition(1505, 825);
m_platform[4].m_platform.setSize(sf::Vector2f(120, 40));
m_platform[4].m_platform.setPosition(1800, 790);

for (int i = 0; i < 5; i++)
{
	m_platform[i].updateCollissions();
}
}

/// <summary>
/// default destructor
/// </summary>
Game::~Game()
{
}

/// <summary>
/// main method for game, contains game loop
/// </summary>
void Game::run()
{
	//the clock object, keeps track of the time passing
	sf::Clock clock;
	//the amount of time since the last loop was completed
	sf::Time lag = sf::Time::Zero;

	//loop while the window is open
	while (m_window.isOpen())
	{
		//holds the time since the last loop, resets the clock
		sf::Time dTime = clock.restart();
		lag += dTime;
		//update input
		processEvents();

		//update as long as the lag is larger then the time per frame
		while (lag > M_MS_PER_UPDATE)
		{
			update(M_MS_PER_UPDATE);
			lag -= M_MS_PER_UPDATE;
		}
		//draw to the screen
		render();
	}
}

/// <summary>
/// Checking the collisions between The spaceship AABB and The Land Poly USing Tinyc2
///  
/// </summary>
void Game::landShipCollision()
{

	sf::Vector2f temp = m_spaceShip.m_body.getTransform().transformPoint(0, 0);
	m_shipPoly.verts[0] = c2V(temp.x, temp.y);
	temp = m_spaceShip.m_body.getTransform().transformPoint(m_spaceShip.m_body.getSize().x, 0);
	m_shipPoly.verts[1] = c2V(temp.x, temp.y);
	temp = m_spaceShip.m_body.getTransform().transformPoint(0, m_spaceShip.m_body.getSize().y + m_spaceShip.m_landingGear.m_landingbody.getSize().y - 5);
	m_shipPoly.verts[3] = c2V(temp.x, temp.y);
	temp = m_spaceShip.m_body.getTransform().transformPoint(m_spaceShip.m_body.getSize().x, m_spaceShip.m_body.getSize().y + m_spaceShip.m_landingGear.m_landingbody.getSize().y - 5);
	m_shipPoly.verts[2] = c2V(temp.x, temp.y);

	/*c2Manifold shipPlatManifold[5];
	for (int i = 0; i < 5; i++)
	{
		c2AABBtoPolyManifold(m_platform[i].m_platformAABB, &m_shipPoly, NULL, &shipPlatManifold[i]);
		if (shipPlatManifold[i].count > 0)
		{
			std::cout << "success" << std::endl;
		}
	}*/

	for (int i = 0; i < 5; i++)
	{
		m_platform[i].updateCollissions();
		if (m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() <= 10 || m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() >= 350)
		{
			if (i >= 0 && i <= 4)
			{
				m_spaceShip.m_fuelTank.capacity += 100;
				m_spaceShip.m_velocity = (sf::Vector2f(0, 0));
			}
			else if (i == 5)
			{
				m_currentLevelState = Level::LEVELTWO;
				m_spaceShip.m_body.setPosition(100, 200);
			}
			
		}
		else if (m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() >= 10 || m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() < 350)
		{
		m_gameOver = true;
		}
	}

	c2Manifold  shipLandManifold[20];
	for (int i = 0; i < 20; i++)
	{
		c2PolytoPolyManifold(&m_shipPoly,NULL , &m_landPolys[i], NULL, &shipLandManifold[i]);
	
		//if the collisions intersect Output that its colliding
		if (shipLandManifold[i].count > 0) 
		{
			m_gameOver = true;
		}
	}
}

void Game::land2ShipCollision()
{
	sf::Vector2f temp = m_spaceShip.m_body.getTransform().transformPoint(0, 0);
	m_shipPoly.verts[0] = c2V(temp.x, temp.y);
	temp = m_spaceShip.m_body.getTransform().transformPoint(m_spaceShip.m_body.getSize().x, 0);
	m_shipPoly.verts[1] = c2V(temp.x, temp.y);
	temp = m_spaceShip.m_body.getTransform().transformPoint(0, m_spaceShip.m_body.getSize().y);
	m_shipPoly.verts[3] = c2V(temp.x, temp.y);
	temp = m_spaceShip.m_body.getTransform().transformPoint(m_spaceShip.m_body.getSize().x, m_spaceShip.m_body.getSize().y);
	m_shipPoly.verts[2] = c2V(temp.x, temp.y);

	for (int i = 0; i < 5; i++)
	{
		m_platform[i].updateCollissions();
		if (m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() <= 10 || m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() >= 350)
		{
			if (i >= 0 && i <= 4)
			{
				m_spaceShip.m_fuelTank.capacity += 100;
				m_spaceShip.m_velocity = (sf::Vector2f(0, 0));
			}
			else if (i == 5)
			{
				m_padHit = true;
				m_gameOver = true;
			}
		}
		else if (m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() >= 10 || m_spaceShip.m_body.getGlobalBounds().intersects(m_platform[i].m_platform.getGlobalBounds()) && m_spaceShip.m_body.getRotation() < 350)
		{
			m_gameOver = true;
		}

		c2Manifold  shipLandManifold[49];
		for (int i = 0; i < 49; i++)
		{
			c2PolytoPolyManifold(&m_shipPoly, NULL, &m_landPolyslvl2[i], NULL, &shipLandManifold[i]);

			//if the collisions intersect Output that its colliding
			if (shipLandManifold[i].count > 0) {

				m_gameOver = true;
			}
		}
	}
}
/// <summary>
/// Process user input
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		//if the window is closed or the escape button is pressed, cloase the window
		if ( sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // window message
		{
			m_window.close();
		}
	}
}

/// <summary>
/// update the game objects
/// </summary>
/// <param name="t_deltaTime">time since last update</param>
void Game::update(sf::Time t_deltaTime)
{
	//if the window was prompted to close, close the window
	if (m_exitGame)
	{
		m_window.close();
	}

	//if the controller is connected update the key presses
	if (m_controller.isConnected())
	{
		m_controller.update();
	}
	//otherwise try find a controller to connect
	else
	{
		m_controller.connect();
	}

	//depending on what state the game is in update diffeently
	switch (m_currentState)
	{
	case GameState::INTRO:
		m_introAnimation.update();
		m_nextState = GameState::MENU;
		if (m_introAnimation.m_currentFrame >= m_introAnimation.m_frames)
		{
			m_currentState = GameState::TRANSITION;
		}
		m_gameOver = false;
		break;


	case GameState::TRANSITION:
		m_transAnim.update();
		m_gameOver = false;
		if (m_transAnim.m_currentFrame >= m_transAnim.m_frames)
		{
			m_transAnim.reset();
			m_currentState = m_nextState;
		}
		break;


	case GameState::PLAYING:

		m_missionSetUpScreen.m_finishedSetUp = false;
		m_window.setView(m_window.getDefaultView());
		
		flareCollisions();
		m_shadertimer += t_deltaTime.asSeconds();
		m_backgroundShader->setUniform("time", m_shadertimer);

		m_HUD.update(m_controller, m_spaceShip.m_fuelTank.capacity, m_spaceShip.m_velocity.x, m_spaceShip.m_velocity.y, 100);
		switch (m_currentLevelState)
		{
		case Level::LEVELONE:
			landShipCollision();
			if (m_controller.m_currentState.Y)
			{
				m_currentLevelState = Level::LEVELTWO;
			}
			for (int i = 0; i < 5; i++)
			{
				m_platform[i].m_platformCircle.setPosition(m_platform[i].m_platform.getPosition());
			}
			break;
		case Level::LEVELTWO:
			setUpCollisionlvl2();
			setuplvl2();

			m_platform[0].m_platform.setSize(sf::Vector2f(130, 20));
			m_platform[0].m_platform.setPosition(70, 595);
			m_platform[0].m_platform.setRotation(0);
			m_platform[1].m_platform.setSize(sf::Vector2f(120, 20));
			m_platform[1].m_platform.setPosition(730, 725);
			m_platform[1].m_platform.setRotation(0);
			m_platform[2].m_platform.setSize(sf::Vector2f(50, 20));
			m_platform[2].m_platform.setPosition(1335, 295);
			m_platform[2].m_platform.setRotation(0);
			m_platform[3].m_platform.setSize(sf::Vector2f(100, 20));
			m_platform[3].m_platform.setPosition(1733, 273);
			m_platform[4].m_platform.setSize(sf::Vector2f(120, 20));
			m_platform[4].m_platform.setPosition(1650, 681);

			for (int i = 0; i < 5; i++)
			{
				m_platform[i].m_platformCircle.setPosition(m_platform[i].m_platform.getPosition());
			}
			break;
		}


		if (m_controller.m_currentState.Start)
		{	
			if (!m_controller.m_previousState.Start)
			{
				m_controller.m_currentState.Start = true;
				m_pauseBool = true;
			}
		}

		for (int i = 0; i <5; i++)
		{
			//set the appropriate view for the screen
			m_window.setView(m_defaultCam);

			//check if the ship collides with the ground
			landShipCollision();

			//update the shader
			m_shadertimer += t_deltaTime.asSeconds();
			m_backgroundShader->setUniform("time", m_shadertimer);


			//loop through all of the platforms
			for (int i = 0; i < 5; i++)
			{ 
				//if the ship is close enough to the platform change the view the game has
				if (cd::circleToCircle(m_spaceShip.m_shipCircle, m_platform[i].m_platformCircle))
				{
					//update the centre of the cam to where the player is
					m_playerCam.setCenter(m_spaceShip.m_position);
					//set the window view to the playercam view
					m_window.setView(m_playerCam);
				}
			}

			//screen wrap
			if (m_spaceShip.m_position.x < 0)
			{
				m_spaceShip.m_position.x = ScreenSize::s_screenWidth;
				m_spaceShip.m_body.setPosition(m_spaceShip.m_position);
			}
			if (m_playerCam.getCenter().x < 400)
			{
				m_playerCam.setCenter(500, m_spaceShip.m_position.y);
				m_window.setView(m_playerCam);
			}
		}

		if (!m_gameOver && !m_pauseBool)
		{
			m_spaceShip.update(t_deltaTime, m_controller);
			m_pause.m_restart = false;
			m_pause.m_resume = false;
			m_pool.update(t_deltaTime, m_spaceShip.m_position);

		}
		else
		{
			if (m_pauseBool)
			{
				m_window.setView(m_window.getDefaultView());
				m_pause.update(m_controller, t_deltaTime, m_currentState);
				if (m_pause.m_resume)
				{
					m_pauseBool = false;
				}

				if (m_pause.m_restart)
				{
					m_spaceShip.reset(m_level.m_level1.m_startPointPos);
					m_pauseBool = false;
				}
			}
		
			if (m_gameOver)
			{
				m_window.setView(m_window.getDefaultView());
				m_gameOverScreen.update(m_controller, 100, t_deltaTime);
				if (m_gameOverScreen.m_switchMainMenu)
				{
					m_currentState = GameState::MENU;
					m_gameOver = false; m_gameOverScreen.m_switchMainMenu = false;	
					m_spaceShip.reset(m_level.m_level1.m_startPointPos);
					m_window.setView(m_window.getDefaultView());
				}
			}
		}

		setUpView();

		if (m_controller.m_currentState.X)
		{
			m_flare.m_flareAlive = true;
		}

		if (m_flare.m_flareAlive == false)
		{
			m_flare.m_flarePosition = m_spaceShip.m_position;
		}

		if (m_flare.m_flareAlive == true)
		{
			m_flare.update(m_controller, t_deltaTime);
		}

		break;
	case GameState::MENU:
		m_window.setView(m_window.getDefaultView());
		m_gameOver = false;
		m_missionSetUpScreen.m_returnToMenu = false;
		m_pauseBool = false;
		m_mainMenuScreen.update(m_controller, t_deltaTime, m_currentState);
			break;
	case GameState::OPTIONS:
		m_window.setView(m_window.getDefaultView());
		m_settingsScreen.update(t_deltaTime, m_controller,m_currentState);
		m_missionSetUpScreen.m_returnToMenu = false;
		break;
	case GameState::HELP:
		m_missionSetUpScreen.m_returnToMenu = false;
		m_window.setView(m_window.getDefaultView());
		m_pauseBool = false;
		m_mainMenuScreen.update(m_controller, t_deltaTime, m_currentState);
		//m_pool.update(t_deltaTime, sf::Vector2f(1930, 900));
			break;
	case GameState::MISSIONSETUP:
		m_window.setView(m_window.getDefaultView());
		m_missionSetUpScreen.update(t_deltaTime, m_controller);
		if (m_missionSetUpScreen.m_finishedSetUp)
		{
			m_missionSetUpScreen.m_finishedSetUp = false;
			m_currentState = GameState::PLAYING;
			m_gameOver = false;
			m_spaceShip.reset(m_level.m_level1.m_startPointPos);
		}
		if (m_missionSetUpScreen.m_returnToMenu)
		{
			m_missionSetUpScreen.m_returnToMenu = false;
			m_currentState = GameState::MENU;
		}
		break;
	case GameState::HIGHSCORESCREEN:
		m_window.setView(m_window.getDefaultView());
		m_highscoreScreen.buttonPress(m_controller, m_currentState);
		break;
	case GameState::EXIT:
		m_window.close();
		m_pauseBool = false;

		break;
	default:
		break;
	}

}

/// <summary>
/// draw the game objects to the screen
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	switch (m_currentState)
	{
	case GameState::INTRO:
		m_window.draw(m_introRect);
		break;		  
	case GameState::TRANSITION:
		m_window.clear(sf::Color::Black);
		m_window.draw(m_transRect);
		break;
	case GameState::PLAYING:
		m_window.draw(m_shaderBaseRect, m_backgroundShader);
		m_spaceShip.render(m_window);
		m_missileBase.render(m_window);
		m_pool.render(m_window);
		m_window.draw(m_collisionMap);
		m_HUD.render(m_window);
		for (int i = 0; i < 47; i++)
		{
			m_window.draw(m_collisionPoints[i]);
		}

		m_missileBase.render(m_window);

		/// <summary>
		/// Drawing the debugs
		/// </summary>
		m_tinyDebug.draw(m_pool.m_collisisionPoly, COLOR_NORMAL);
		m_tinyDebug.draw(m_shipPoly, COLOR_NORMAL);
		for (int i = 0; i < 5; i++)
		{
			m_tinyDebug.draw(m_platform[i].m_platformAABB, COLOR_NORMAL);
		}
		
		switch (m_currentLevelState)
		{
		case Level::LEVELONE:
			m_window.draw(m_mapping);
			for (int i = 0; i < 20; i++)
			{
				m_tinyDebug.draw(m_landPolys[i], COLOR_NORMAL);
			}
			break;
		case Level::LEVELTWO:
			m_window.draw(m_Level2Map);
			for (int i = 0; i < 49; i++)
			{
				m_tinyDebug.draw(m_landPolyslvl2[i], COLOR_NORMAL);
			}
			break;
		}
		for (int i = 0; i < 5; i++)
		{
			m_platform[i].render(m_window);
		}
		if (m_gameOver)
		{
			m_gameOverScreen.render(m_window, m_padHit);
		}

		if (m_flare.m_flareAlive == true)
		{
			m_flare.render(m_window);
		}
		if (m_pauseBool)
		{
			m_pause.render(m_window);
		}

		break;
	case GameState::MENU:
		m_mainMenuScreen.render(m_window);
		break;
	case GameState::OPTIONS:
		m_settingsScreen.render(m_window);
		break;
	case GameState::HELP:
		m_helpScreen.render(m_window);
		break;
	case GameState::MISSIONSETUP:
		m_missionSetUpScreen.render(m_window);
		break;
	case GameState::HIGHSCORESCREEN:
		m_highscoreScreen.render(m_window);
		break;
	case GameState::EXIT:
		break;
	default:
		break;
	}
	m_window.display();
}

void Game::flareCollisions()
{
	m_flarePoly.verts[0] = c2V(m_flare.m_flarePosition.x - m_flare.m_flareBody.getGlobalBounds().width * .5, m_flare.m_flarePosition.y - m_flare.m_flareBody.getGlobalBounds().height * .5);
	m_flarePoly.verts[1] = c2V(m_flare.m_flarePosition.x + m_flare.m_flareBody.getGlobalBounds().width * .5, m_flare.m_flarePosition.y - m_flare.m_flareBody.getGlobalBounds().height * .5);
	m_flarePoly.verts[2] = c2V(m_flare.m_flarePosition.x + m_flare.m_flareBody.getGlobalBounds().width * .5, m_flare.m_flarePosition.y + m_flare.m_flareBody.getGlobalBounds().height * .5);
	m_flarePoly.verts[3] = c2V(m_flare.m_flarePosition.x - m_flare.m_flareBody.getGlobalBounds().width * .5, m_flare.m_flarePosition.y + m_flare.m_flareBody.getGlobalBounds().height * .5);
	c2MakePoly(&m_flarePoly);

	c2Manifold  m_flareManifold[20];
	c2Manifold  m_flareManifoldlvl2[49];
	switch (m_currentLevelState)
	{
	case Level::LEVELONE:
		
		for (int i = 0; i < 20; i++)
		{
			c2PolytoPolyManifold(&m_flarePoly, NULL, &m_landPolys[i], NULL, &m_flareManifold[i]);

			//if the collisions intersect Output that its colliding
			if (m_flareManifold[i].count > 0) {

				m_flare.m_flareAlive = false;
			}
		}
		break;
	case Level::LEVELTWO:
		
		for (int i = 0; i < 49; i++)
		{
			c2PolytoPolyManifold(&m_flarePoly, NULL, &m_landPolyslvl2[i], NULL, &m_flareManifoldlvl2[i]);

			//if the collisions intersect Output that its colliding
			if (m_flareManifoldlvl2[i].count > 0) {

				m_flare.m_flareAlive = false;
			}
		}
		break;
	default:
		break;
	}

}

/// <summary>
/// Set up the level
/// </summary>
void Game::setupLevel()
{
	for (int i = 0; i < 66; i++)
	{
		m_mapping[i].position = m_level.m_level1.m_groundPoints.at(i).m_position;
		m_mapping[i].color = sf::Color(128, 128, 128, 255);
	}
}

void Game::setuplvl2()
{
	for (int i = 0; i < 159; i++)
	{
		m_Level2Map[i].position = m_level.m_level2.m_groundPoints.at(i).m_position;
		m_Level2Map[i].color = sf::Color(128, 128, 128, 255);
	}
}

/// <summary>
/// set up the bounding boxes
/// </summary>
void Game::setupCollisions()
{
	m_landerPoly.count = 4;

	m_shipPoly.count = 4;
	m_shipPoly.verts[0] = c2V(m_spaceShip.m_position.x - (m_spaceShip.m_body.getGlobalBounds().width * .5), m_spaceShip.m_position.y - (m_spaceShip.m_body.getGlobalBounds().height* .5));
	m_shipPoly.verts[1] = c2V(m_spaceShip.m_position.x + (m_spaceShip.m_body.getGlobalBounds().width * .5), m_spaceShip.m_position.y - (m_spaceShip.m_body.getGlobalBounds().height* .5));
	m_shipPoly.verts[2] = c2V(m_spaceShip.m_position.x - (m_spaceShip.m_body.getGlobalBounds().width * .5), m_spaceShip.m_position.y + (m_spaceShip.m_body.getGlobalBounds().height* .5));
	m_shipPoly.verts[3] = c2V(m_spaceShip.m_position.x + (m_spaceShip.m_body.getGlobalBounds().width * .5), m_spaceShip.m_position.y + (m_spaceShip.m_body.getGlobalBounds().height* .5));

	c2MakePoly(&m_shipPoly);

	for (int i = 0; i < 20; i++)
	{
		m_landPolys[i].count = 3;
	}

	m_landPolys[0].verts[0] = c2V(0, 955);
	m_landPolys[0].verts[1] = c2V(175,870);
	m_landPolys[0].verts[2] = c2V(1180, 1930);

	m_landPolys[1].verts[0] = c2V(175, 870);
	m_landPolys[1].verts[1] = c2V(280, 915);
	m_landPolys[1].verts[2] = c2V(1180, 1930);

	m_landPolys[2].verts[0] = c2V(280, 915);
	m_landPolys[2].verts[1] = c2V(445, 900);
	m_landPolys[2].verts[2] = c2V(1180, 1930);

	m_landPolys[3].verts[0] = c2V(445, 900);
	m_landPolys[3].verts[1] = c2V(560, 835);
	m_landPolys[3].verts[2] = c2V(1180, 1930);

	m_landPolys[4].verts[0] = c2V(560, 835);
	m_landPolys[4].verts[1] = c2V(650, 865);
	m_landPolys[4].verts[2] = c2V(1180, 1930);

	m_landPolys[5].verts[0] = c2V(650, 865);
	m_landPolys[5].verts[1] = c2V(840, 590);
	m_landPolys[5].verts[2] = c2V(1180, 1930);

	m_landPolys[6].verts[0] = c2V(840, 590);
	m_landPolys[6].verts[1] = c2V(915, 565);
	m_landPolys[6].verts[2] = c2V(1180, 1930);

	m_landPolys[7].verts[0] = c2V(915, 565);
	m_landPolys[7].verts[1] = c2V(1015, 315);
	m_landPolys[7].verts[2] = c2V(1180, 1930);

	m_landPolys[8].verts[0] = c2V(1015, 315);
	m_landPolys[8].verts[1] = c2V(1110, 275);
	m_landPolys[8].verts[2] = c2V(1180, 1930);

	m_landPolys[9].verts[0] = c2V(1110, 275);
	m_landPolys[9].verts[1] = c2V(1180, 195);
	m_landPolys[9].verts[2] = c2V(1180, 1930);

	m_landPolys[10].verts[0] = c2V(1180, 195);
	m_landPolys[10].verts[1] = c2V(1275, 400);
	m_landPolys[10].verts[2] = c2V(1180, 1930);

	m_landPolys[11].verts[0] = c2V(1275, 400);
	m_landPolys[11].verts[1] = c2V(1325, 430);
	m_landPolys[11].verts[2] = c2V(1180, 1930);

	m_landPolys[12].verts[0] = c2V(1325, 430);
	m_landPolys[12].verts[1] = c2V(1360, 690);
	m_landPolys[12].verts[2] = c2V(1180, 1930);

	m_landPolys[13].verts[0] = c2V(1360, 690);
	m_landPolys[13].verts[1] = c2V(1475, 750);
	m_landPolys[13].verts[2] = c2V(1180, 1930);

	m_landPolys[14].verts[0] = c2V(1475, 750);
	m_landPolys[14].verts[1] = c2V(1510, 850);
	m_landPolys[14].verts[2] = c2V(1180, 1930);

	m_landPolys[15].verts[0] = c2V(1510, 850);
	m_landPolys[15].verts[1] = c2V(1640, 835);
	m_landPolys[15].verts[2] = c2V(1180, 1930);

	m_landPolys[16].verts[0] = c2V(1640, 835);
	m_landPolys[16].verts[1] = c2V(1660, 765);
	m_landPolys[16].verts[2] = c2V(1180, 1930);

	m_landPolys[17].verts[0] = c2V(1660, 765);
	m_landPolys[17].verts[1] = c2V(1750, 755);
	m_landPolys[17].verts[2] = c2V(1180, 1930);

	m_landPolys[18].verts[0] = c2V(1750, 755);
	m_landPolys[18].verts[1] = c2V(1800, 805);
	m_landPolys[18].verts[2] = c2V(1180, 1930);

	m_landPolys[19].verts[0] = c2V(1800, 805);
	m_landPolys[19].verts[1] = c2V(1950, 805);
	m_landPolys[19].verts[2] = c2V(1180, 1930);

	for (int i = 0; i < 20; i++)
	{
		c2MakePoly(&m_landPolys[i]);
	}
	
	/*for (int i = 0; i <NoOfPoints; i++)
	{
		m_mapping[i].color = sf::Color(128, 128, 128, 255);
		m_collisionmap[i].position = sf::Vector2f(m_landPoly.verts[i].x, m_landPoly.verts[i].y);
		m_collisionmap[i].color = sf::Color::Red;

		m_collisionpoints[i].setRadius(5);
		m_collisionpoints[i].setFillColor(sf::Color::Red);
		m_collisionpoints[i].setPosition(sf::Vector2f(m_landPoly.verts[i].x, m_landPoly.verts[i].y));
		m_collisionpoints[i].setOrigin(m_collisionpoints[i].getRadius(), m_collisionpoints[i].getRadius());
	}

	m_collisionpoints[45].setPosition(sf::Vector2f(m_shipCollisionBox.max.x, m_shipCollisionBox.max.y));
	m_collisionpoints[46].setPosition(sf::Vector2f(m_shipCollisionBox.min.x, m_shipCollisionBox.min.y));
	m_collisionpoints[45].setRadius(5);
	m_collisionpoints[45].setFillColor(sf::Color::Green);
	m_collisionpoints[45].setOrigin(m_collisionpoints[45].getRadius(), m_collisionpoints[45].getRadius());

	m_collisionpoints[46].setRadius(5);
	m_collisionpoints[46].setFillColor(sf::Color::Green);
	m_collisionpoints[46].setOrigin(m_collisionpoints[46].getRadius(), m_collisionpoints[46].getRadius());*/

	/*for (int i = 0; i < m_level.m_level1.m_groundPoints.capacity(); i++)
	{
		
	}*/

}

void Game::setUpCollisionlvl2()
{

	for (int i = 0; i < 49; i++)
	{
		m_landPolyslvl2[i].count = 3;
	}

	m_landPolyslvl2[0].verts[0] = c2V(0, 830);
	m_landPolyslvl2[0].verts[1] = c2V(80, 670);
	m_landPolyslvl2[0].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[1].verts[0] = c2V(80, 670);
	m_landPolyslvl2[1].verts[1] = c2V(190, 615);
	m_landPolyslvl2[1].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[2].verts[0] = c2V(190, 615);
	m_landPolyslvl2[2].verts[1] = c2V(360, 820);
	m_landPolyslvl2[2].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[3].verts[0] = c2V(360, 820);
	m_landPolyslvl2[3].verts[1] = c2V(390, 820);
	m_landPolyslvl2[3].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[4].verts[0] = c2V(390, 820);
	m_landPolyslvl2[4].verts[1] = c2V(475, 515);
	m_landPolyslvl2[4].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[5].verts[0] = c2V(475, 515);
	m_landPolyslvl2[5].verts[1] = c2V(515, 470);
	m_landPolyslvl2[5].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[6].verts[0] = c2V(515, 470);
	m_landPolyslvl2[6].verts[1] = c2V(560, 345);
	m_landPolyslvl2[6].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[7].verts[0] = c2V(560, 345);
	m_landPolyslvl2[7].verts[1] = c2V(665, 255);
	m_landPolyslvl2[7].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[8].verts[0] = c2V(665, 255);
	m_landPolyslvl2[8].verts[1] = c2V(745, 405);
	m_landPolyslvl2[8].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[9].verts[0] = c2V(745, 405);
	m_landPolyslvl2[9].verts[1] = c2V(730, 725);
	m_landPolyslvl2[9].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[10].verts[0] = c2V(730, 725);
	m_landPolyslvl2[10].verts[1] = c2V(820, 795);
	m_landPolyslvl2[10].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[11].verts[0] = c2V(820, 795);
	m_landPolyslvl2[11].verts[1] = c2V(915, 735);
	m_landPolyslvl2[11].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[12].verts[0] = c2V(915, 735);
	m_landPolyslvl2[12].verts[1] = c2V(1125, 840);
	m_landPolyslvl2[12].verts[2] = c2V(590, 1070);

	m_landPolyslvl2[13].verts[0] = c2V(1125, 840);
	m_landPolyslvl2[13].verts[1] = c2V(1185, 760);
	m_landPolyslvl2[13].verts[2] = c2V(1530, 1070);

	m_landPolyslvl2[14].verts[0] = c2V(1158, 760);
	m_landPolyslvl2[14].verts[1] = c2V(1325, 750);
	m_landPolyslvl2[14].verts[2] = c2V(1530, 1070);

	m_landPolyslvl2[15].verts[0] = c2V(1325, 750);
	m_landPolyslvl2[15].verts[1] = c2V(1375, 830);
	m_landPolyslvl2[15].verts[2] = c2V(1530, 1070);

	m_landPolyslvl2[16].verts[0] = c2V(1375, 830);
	m_landPolyslvl2[16].verts[1] = c2V(1615, 690);
	m_landPolyslvl2[16].verts[2] = c2V(1530, 1070);

	m_landPolyslvl2[17].verts[0] = c2V(1615, 690);
	m_landPolyslvl2[17].verts[1] = c2V(1775, 685);
	m_landPolyslvl2[17].verts[2] = c2V(1530, 1070);

	m_landPolyslvl2[18].verts[0] = c2V(1775, 685);
	m_landPolyslvl2[18].verts[1] = c2V(1785, 665);
	m_landPolyslvl2[18].verts[2] = c2V(1530, 1070);

	m_landPolyslvl2[19].verts[0] = c2V(1785, 665);
	m_landPolyslvl2[19].verts[1] = c2V(1725, 540);
	m_landPolyslvl2[19].verts[2] = c2V(1905, 525);

	m_landPolyslvl2[20].verts[0] = c2V(1725, 540);
	m_landPolyslvl2[20].verts[1] = c2V(1880, 245);
	m_landPolyslvl2[20].verts[2] = c2V(1905, 525);

	m_landPolyslvl2[21].verts[0] = c2V(1920, 805);
	m_landPolyslvl2[21].verts[1] = c2V(1920, 1930);
	m_landPolyslvl2[21].verts[2] = c2V(1180, 1930);

	m_landPolyslvl2[22].verts[0] = c2V(1853, 280);
	m_landPolyslvl2[22].verts[1] = c2V(1723, 530);
	m_landPolyslvl2[22].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[23].verts[0] = c2V(1725, 530);
	m_landPolyslvl2[23].verts[1] = c2V(1560, 550);
	m_landPolyslvl2[23].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[24].verts[0] = c2V(1560, 550);
	m_landPolyslvl2[24].verts[1] = c2V(1470, 607);
	m_landPolyslvl2[24].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[25].verts[0] = c2V(1470, 607);
	m_landPolyslvl2[25].verts[1] = c2V(1410, 590);
	m_landPolyslvl2[25].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[26].verts[0] = c2V(1410, 590);
	m_landPolyslvl2[26].verts[1] = c2V(1245, 610);
	m_landPolyslvl2[26].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[27].verts[0] = c2V(1245, 610);
	m_landPolyslvl2[27].verts[1] = c2V(1220, 555);
	m_landPolyslvl2[27].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[28].verts[0] = c2V(1220, 555);
	m_landPolyslvl2[28].verts[1] = c2V(1045, 545);
	m_landPolyslvl2[28].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[29].verts[0] = c2V(1045, 545);
	m_landPolyslvl2[29].verts[1] = c2V(1015, 590);
	m_landPolyslvl2[29].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[30].verts[0] = c2V(1015, 590);
	m_landPolyslvl2[30].verts[1] = c2V(945, 560);
	m_landPolyslvl2[30].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[31].verts[0] = c2V(945, 560);
	m_landPolyslvl2[31].verts[1] = c2V(960, 490);
	m_landPolyslvl2[31].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[32].verts[0] = c2V(960, 490);
	m_landPolyslvl2[32].verts[1] = c2V(920, 440);
	m_landPolyslvl2[32].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[33].verts[0] = c2V(920, 440);
	m_landPolyslvl2[33].verts[1] = c2V(945, 370);
	m_landPolyslvl2[33].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[34].verts[0] = c2V(945, 370);
	m_landPolyslvl2[34].verts[1] = c2V(930, 365);
	m_landPolyslvl2[34].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[35].verts[0] = c2V(930, 365);
	m_landPolyslvl2[35].verts[1] = c2V(960, 320);
	m_landPolyslvl2[35].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[36].verts[0] = c2V(960, 320);
	m_landPolyslvl2[36].verts[1] = c2V(1025, 300);
	m_landPolyslvl2[36].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[37].verts[0] = c2V(1025, 300);
	m_landPolyslvl2[37].verts[1] = c2V(1030, 215);
	m_landPolyslvl2[37].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[38].verts[0] = c2V(1030, 215);
	m_landPolyslvl2[38].verts[1] = c2V(1135, 170);
	m_landPolyslvl2[38].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[39].verts[0] = c2V(1135, 170);
	m_landPolyslvl2[39].verts[1] = c2V(1250, 230);
	m_landPolyslvl2[39].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[40].verts[0] = c2V(1250, 230);
	m_landPolyslvl2[40].verts[1] = c2V(1300, 260);
	m_landPolyslvl2[40].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[41].verts[0] = c2V(1300, 260);
	m_landPolyslvl2[41].verts[1] = c2V(1335, 300);
	m_landPolyslvl2[41].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[42].verts[0] = c2V(1335, 300);
	m_landPolyslvl2[42].verts[1] = c2V(1385, 300);
	m_landPolyslvl2[42].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[43].verts[0] = c2V(1385, 300);
	m_landPolyslvl2[43].verts[1] = c2V(1460, 250);
	m_landPolyslvl2[43].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[44].verts[0] = c2V(1460, 250);
	m_landPolyslvl2[44].verts[1] = c2V(1520, 165);
	m_landPolyslvl2[44].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[45].verts[0] = c2V(1520, 165);
	m_landPolyslvl2[45].verts[1] = c2V(1590, 130);
	m_landPolyslvl2[45].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[46].verts[0] = c2V(1590, 130);
	m_landPolyslvl2[46].verts[1] = c2V(1625, 230);
	m_landPolyslvl2[46].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[47].verts[0] = c2V(1625, 230);
	m_landPolyslvl2[47].verts[1] = c2V(1730, 275);
	m_landPolyslvl2[47].verts[2] = c2V(1390, 440);

	m_landPolyslvl2[48].verts[0] = c2V(1730, 275);
	m_landPolyslvl2[48].verts[1] = c2V(1849, 287);
	m_landPolyslvl2[48].verts[2] = c2V(1390, 440);

	for (int i = 0; i < 49; i++)
	{
		c2MakePoly(&m_landPolyslvl2[i]);
	}

}

void Game::setUpView()
{
	if (m_spaceShip.m_position.x < 0)
	{
		m_spaceShip.m_position.x = 1920;
		m_spaceShip.m_body.setPosition(m_spaceShip.m_position);
	}
	if (m_playerCam.getCenter().x < 400)
	{
		m_playerCam.setCenter(500, m_spaceShip.m_position.y);
		m_window.setView(m_playerCam);
	}

	if (m_spaceShip.m_position.x > 1920)
	{
		m_spaceShip.m_position.x = 0;
		m_spaceShip.m_body.setPosition(m_spaceShip.m_position);
		m_playerCam.setCenter(0, m_spaceShip.m_position.y);
	}
	if (m_playerCam.getCenter().x > 1400)
	{
		m_playerCam.setCenter(1500, m_spaceShip.m_position.y);
		m_window.setView(m_playerCam);
	}

	if (m_spaceShip.m_position.y >= 0)
	{
		m_spaceShip.m_body.setPosition(m_spaceShip.m_position.x, m_spaceShip.m_position.y - 1);
	}

}



