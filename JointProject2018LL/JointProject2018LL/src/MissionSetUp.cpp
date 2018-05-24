#include "MissionSetUp.h"



MissionSetUpScreen::MissionSetUpScreen(sf::Font &t_font, Spaceship & t_spaceship, rh::ResourceHolder & t_resources) :
	m_resources(t_resources),
	m_font(t_font),
	m_spaceship(t_spaceship)
{
	m_ship.setPosition(150, 175);
	m_ship.setSize(sf::Vector2f(400, 400));

	for (int i = 0; i < M_MAXUPGRADES; i++)
	{
		if (i == 0)
		{
			m_upgrades[i].init(sf::Vector2f(350, 400), sf::Vector2f(90, 90), sf::Texture() , Label(), false, sf::Color::White);
		}
		if( i == 4 )
		{
			m_upgrades[i].init(sf::Vector2f(230, 440), sf::Vector2f(90, 90), sf::Texture(), Label(), false, sf::Color::White);
		}
		if(i == 8 )
		{
			m_upgrades[i].init(sf::Vector2f(350, 575), sf::Vector2f(90, 90), sf::Texture(), Label(), false, sf::Color::White);
		}
		if( i == 12)
		{
			m_upgrades[i].init(sf::Vector2f(350, 680), sf::Vector2f(90, 90), sf::Texture(), Label(), false, sf::Color::White);
		}

		if (i == 1 || i == 5 || i == 9 || i == 13)
		{
			m_upgrades[i].init(sf::Vector2f(1000, 250 + (40 * (i-1))), sf::Vector2f(90, 90), sf::Texture(), Label(), false, sf::Color::White);
		}

		if (i == 2 || i == 6 || i == 10 || i == 14)
		{
			m_upgrades[i].init(sf::Vector2f(1200, 250 + (40 * (i - 2))), sf::Vector2f(90, 90), sf::Texture(), Label(), false, sf::Color::White);
		}

		if (i == 3 || i == 7 || i == 11 || i == 15)
		{
			m_upgrades[i].init(sf::Vector2f(1400, 250 + (40 * (i - 3))), sf::Vector2f(90, 90), sf::Texture(), Label(), false, sf::Color::White);
		}

		if (i > 15 && i < M_MAXUPGRADES)
		{
			m_upgrades[i].init(sf::Vector2f(225 + (250 * (i-16)), 900), sf::Vector2f(200, 50), m_resources.m_textureHolder["ButtonTexture"], Label("",sf::Vector2f(0,0), m_font, 20, sf::Color::Black), false);
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 800, 200));
		}

	}
	
	for (int i = 0; i < 4; i++)
	{
		m_names[i].init(m_nameString[i], sf::Vector2f(1600, 250 + (160 * i)), t_font, 20, sf::Color::Black);	
	}
	m_names[4].init(m_nameString[4], sf::Vector2f(225, 890), t_font, 30, sf::Color::Black);
	m_names[5].init(m_nameString[5], sf::Vector2f(475, 890), t_font, 30, sf::Color::Black);

	for (int i = 0; i < M_MAXTIERS; i++)
	{
		m_tiers[i].init(m_tierString[i], sf::Vector2f(1000 + (200 * i), 150), t_font, 20, sf::Color::Black);
	}

	setupTextures();
}

MissionSetUpScreen::~MissionSetUpScreen()
{
}

void MissionSetUpScreen::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_ship);

	for (int i = 0; i < M_MAXUPGRADES; i++)
	{
		m_upgrades[i].render(t_window);
	}

	for (int i = 0; i < M_MAXNAMES; i++)
	{
		m_names[i].render(t_window); 
	}

	for (int i = 0; i < M_MAXTIERS; i++)
	{
		m_tiers[i].render(t_window);
	}
}

void MissionSetUpScreen::update(sf::Time t_d, Xbox360Controller t_controller)
{
	for (int i = 0; i < M_MAXUPGRADES; i++)
	{
		m_upgrades[i].update(t_d, t_controller, 5);
	}

	m_upgrades[m_currentButton].highlighted(true);

	if (t_controller.m_currentState.DpadDown && !t_controller.m_previousState.DpadDown)
	{
		if (m_currentButton == 0 || m_currentButton == 4 || m_currentButton == 8 || m_currentButton == 12)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton += 4;
		}

		else if (m_currentButton == 16|| m_currentButton == 17)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = 0;
		}
	}

	if (t_controller.m_currentState.DpadUp && !t_controller.m_previousState.DpadUp)
	{
		if (m_currentButton == 4 || m_currentButton == 8 || m_currentButton == 12 || m_currentButton == 16)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton -= 4;
		}
		else if (m_currentButton == 17)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton -= 5;
		}
		else if (m_currentButton == 0)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = 16;
		}
	}

	if (t_controller.m_currentState.DpadRight && !t_controller.m_previousState.DpadRight)
	{
		if (m_currentButton >0 && m_currentButton <=2|| m_currentButton > 4 && m_currentButton <= 6 || m_currentButton >8 && m_currentButton <= 10 || m_currentButton >12 && m_currentButton <= 14)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton++;
		}
		else if (m_currentButton == 16)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton++;
		}
		else if (m_currentButton == 17)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = 16;
		}
	}

	if (t_controller.m_currentState.DpadLeft && !t_controller.m_previousState.DpadLeft)
	{
		if (m_currentButton >1 && m_currentButton <= 3 || m_currentButton > 5 && m_currentButton <= 7 || m_currentButton >9 && m_currentButton <= 11 || m_currentButton >13 && m_currentButton <= 15)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton--;
		}
		else if (m_currentButton == 16)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = 17;
		}
		else if (m_currentButton == 17)
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton--;
		}
	}

	if (t_controller.m_currentState.A && !t_controller.m_previousState.A)
	{
		if (m_currentButton == 0 || m_currentButton == 4 || m_currentButton == 8 || m_currentButton == 12 )
		{
			m_upgrades[m_currentButton].highlighted(false);
			m_previousButton = m_currentButton;
			m_currentButton++;
		}
		else if (m_currentButton >= 0 && m_currentButton < 4)
		{
			switch (m_fuelInUse)
			{
			case 1:
				m_upgrades[1].texture(m_resources.m_textureHolder["T1FuelTank"]);
				m_upgrades[1].TextureRect(sf::IntRect(0, 0, 17, 35));
				break;
			case 2:
				m_upgrades[2].texture(m_resources.m_textureHolder["T2FuelTank"]);
				m_upgrades[2].TextureRect(sf::IntRect(0, 0, 17, 35));
				break;
			case 3:
				m_upgrades[3].texture(m_resources.m_textureHolder["T3FuelTank"]);
				m_upgrades[3].TextureRect(sf::IntRect(0, 0, 17, 35));
				break;
			default:
				break;
			}
				m_fuelInUse = m_currentButton;

				switch (m_fuelInUse)
				{
				case 1:
					m_spaceship.m_fuelTank.capacity = 100;
					m_spaceship.m_fuelTank.weight = 5;
					break;
				case 2:
					m_spaceship.m_fuelTank.capacity = 200;
					m_spaceship.m_fuelTank.weight = 7;
					break;
				case 3:
					m_spaceship.m_fuelTank.capacity = 300;
					m_spaceship.m_fuelTank.weight = 10;
					break;
				default:
					break;
				}

				m_upgrades[m_currentButton].TextureRect(sf::IntRect(0, 0, 90, 90));
				m_upgrades[0].m_body.setTexture(m_upgrades[m_currentButton].m_body.getTexture());
				m_spaceship.m_fuelTank.m_fuelTexture = * m_upgrades[0].m_body.getTexture();
				m_upgrades[m_currentButton].texture(m_resources.m_textureHolder["FuelTankInUse"]);
				m_upgrades[m_currentButton].highlighted(false);
				m_currentButton = m_previousButton;
		}

		else if (m_currentButton >= 5 && m_currentButton < 8)
		{
			switch (m_sideEngineInUse)
			{
			case 1:
				m_upgrades[5].texture(m_resources.m_textureHolder["T1SideEngine"]);
				m_upgrades[5].TextureRect(sf::IntRect(0, 0, 11, 22));
				break;
			case 2:
				m_upgrades[6].texture(m_resources.m_textureHolder["T2SideEngine"]);
				m_upgrades[6].TextureRect(sf::IntRect(0, 0, 11, 22));
				break;
			case 3:
				m_upgrades[7].texture(m_resources.m_textureHolder["T3SideEngine"]);
				m_upgrades[7].TextureRect(sf::IntRect(0, 0, 11, 22));
				break;
			default:
				break;
			}
			m_sideEngineInUse = m_currentButton - 4;

			switch (m_sideEngineInUse)
			{
			case 1:
				m_spaceship.m_sideThrusters->fuelComsumption = .06;
				m_spaceship.m_sideThrusters->weight = 5;
				break;
			case 2:
				m_spaceship.m_sideThrusters->fuelComsumption = .8;
				m_spaceship.m_sideThrusters->weight = 7;
				break;
			case 3:
				m_spaceship.m_sideThrusters->fuelComsumption = 0.1;
				m_spaceship.m_sideThrusters->weight = 10;
				break;
			default:
				break;
			}
			m_upgrades[4].m_body.setTexture(m_upgrades[m_currentButton].m_body.getTexture());

			for (int i = 0; i < 2; i++)
			{
				m_spaceship.m_sideThrusters[i].sideThrusterTexture = *m_upgrades[4].m_body.getTexture();
			}
			
			m_upgrades[m_currentButton].TextureRect(sf::IntRect(0, 0, 90, 90));
			m_upgrades[m_currentButton].texture(m_resources.m_textureHolder["sideEngineInUse"]);
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = m_previousButton;
		}

		else if (m_currentButton >= 9 && m_currentButton < 12)
		{
			switch (m_thrusterInUse)
			{
			case 1:
				m_upgrades[9].texture(m_resources.m_textureHolder["T1MainEngine"]);
				m_upgrades[9].TextureRect(sf::IntRect(0, 0, 13, 5));
				break;
			case 2:
				m_upgrades[10].texture(m_resources.m_textureHolder["T2MainEngine"]);
				m_upgrades[10].TextureRect(sf::IntRect(0, 0, 13, 5));
				break;
			case 3:
				m_upgrades[11].texture(m_resources.m_textureHolder["T3MainEngine"]);
				m_upgrades[11].TextureRect(sf::IntRect(0, 0, 13, 5));
				break;
			default:
				break;
			}
			m_thrusterInUse = m_currentButton - 8;

			switch (m_thrusterInUse)
			{
			case 1:
				m_spaceship.m_Thruster.fuelConsumption = .06;
				m_spaceship.m_Thruster.weight = 5;
				break;
			case 2:
				m_spaceship.m_Thruster.fuelConsumption = .08;
				m_spaceship.m_Thruster.weight = 7;
				break;
			case 3:
				m_spaceship.m_Thruster.fuelConsumption = 0.1;
				m_spaceship.m_Thruster.weight = 10;
				break;
			default:
				break;
			}
			m_upgrades[8].m_body.setTexture(m_upgrades[m_currentButton].m_body.getTexture());
			m_spaceship.m_Thruster.mainThrusterSprite = *m_upgrades[8].m_body.getTexture();
			m_upgrades[m_currentButton].TextureRect(sf::IntRect(0, 0, 90, 90));
			m_upgrades[m_currentButton].texture(m_resources.m_textureHolder["engineInUse"]);
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = m_previousButton;
		}
		else if (m_currentButton >= 13 && m_currentButton < 16)
		{
			switch (m_landerInUse)
			{
			case 1:
				m_upgrades[13].texture(m_resources.m_textureHolder["T1LandingGear"]);
				m_upgrades[13].TextureRect(sf::IntRect(0, 0, 59, 31));
				break;
			case 2:
				m_upgrades[14].texture(m_resources.m_textureHolder["T2LandingGear"]);
				m_upgrades[14].TextureRect(sf::IntRect(0, 0, 59, 31));
				break;
			case 3:
				m_upgrades[15].texture(m_resources.m_textureHolder["T3LandingGear"]);
				m_upgrades[15].TextureRect(sf::IntRect(0, 0, 59, 31));
				break;
			default:
				break;
			}
			m_landerInUse = m_currentButton - 12;

			switch (m_landerInUse)
			{
			case 1:
				//m_spaceship.m_landingGear.breakSpeed =
				m_spaceship.m_landingGear.weight = 5;
				break;
			case 2:
				//m_spaceship.m_landingGear.breakSpeed =
				m_spaceship.m_landingGear.weight = 7;
				break;
			case 3:
				//m_spaceship.m_landingGear.breakSpeed =
				m_spaceship.m_landingGear.weight = 10;
				break;
			default:
				break;
			}
			m_upgrades[12].m_body.setTexture(m_upgrades[m_currentButton].m_body.getTexture());
			m_spaceship.m_landingGear.landingGearSprite = *m_upgrades[12].m_body.getTexture();
			m_upgrades[m_currentButton].TextureRect(sf::IntRect(0, 0, 90, 90));
			m_upgrades[m_currentButton].texture(m_resources.m_textureHolder["LandingGearInUse"]);
			m_upgrades[m_currentButton].highlighted(false);
			m_currentButton = m_previousButton;
		}
		else if (m_currentButton == 16)
		{
			m_finishedSetUp = true;
		}
		else if (m_currentButton == 17)
		{
			m_returnToMenu	= true;
		}
	}

	if (t_controller.m_currentState.Start)
	{
		m_finishedSetUp = true;
	}
}

void MissionSetUpScreen::setupTextures()
{
	m_ship.setTexture(&m_resources.m_textureHolder["ShipTexture"]);
	m_ship.setTextureRect(sf::IntRect(0,0,98,84));

	m_upgrades[0].texture(m_resources.m_textureHolder["T1FuelTank"]);
	m_upgrades[1].texture(m_resources.m_textureHolder["FuelTankInUse"]);
	m_upgrades[2].texture(m_resources.m_textureHolder["T2FuelTank"]);
	m_upgrades[3].texture(m_resources.m_textureHolder["T3FuelTank"]);

	m_upgrades[4].texture(m_resources.m_textureHolder["T1SideEngine"]);
	m_upgrades[5].texture(m_resources.m_textureHolder["sideEngineInUse"]);
	m_upgrades[6].texture(m_resources.m_textureHolder["T2SideEngine"]);
	m_upgrades[7].texture(m_resources.m_textureHolder["T3SideEngine"]);

	m_upgrades[8].texture(m_resources.m_textureHolder["T1MainEngine"]);
	m_upgrades[9].texture(m_resources.m_textureHolder["engineInUse"]);
	m_upgrades[10].texture(m_resources.m_textureHolder["T2MainEngine"]);
	m_upgrades[11].texture(m_resources.m_textureHolder["T3MainEngine"]);
	
	m_upgrades[12].texture(m_resources.m_textureHolder["T1LandingGear"]);
	m_upgrades[13].texture(m_resources.m_textureHolder["LandingGearInUse"]);
	m_upgrades[14].texture(m_resources.m_textureHolder["T2LandingGear"]);
	m_upgrades[15].texture(m_resources.m_textureHolder["T3LandingGear"]);

	for (int i = 0; i < M_MAXUPGRADES; i++)
	{
		if (i >= 0 && i < 4)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 17, 35));
		}
		if (i >= 4 && i < 8)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 11, 22));
		}
		if (i >= 8 && i < 12)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 13, 5));
		}
		if (i >= 12 && i < 16)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 59, 31));
		}
		
		if (i == 1 || i == 5 || i == 9 || i == 13)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 90, 90));
		}
	}
}

void MissionSetUpScreen::compareTextures()
{
	for (int i = 0; i < M_MAXUPGRADES; i++)
	{
		if (i >= 0 && i < 4)
		{
			if (m_upgrades[i].m_body.getTexture() == m_spaceship.m_fuelTank.m_tank.getTexture())
			{
				m_upgrades[0].m_body.setTexture(m_upgrades[i].m_body.getTexture());
				m_upgrades[i].texture(m_resources.m_textureHolder["FuelTankInUse"]);
			}
		}
		if (i >= 4 && i < 8)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 11, 22));
		}
		if (i >= 8 && i < 12)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 13, 5));
		}
		if (i >= 12 && i < 16)
		{
			m_upgrades[i].TextureRect(sf::IntRect(0, 0, 59, 31));
		}
	
	}
}
