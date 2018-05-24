#include "Spaceship.h"

Spaceship::Spaceship(const sf::Vector2f t_position, rh::ResourceHolder & t_resourceHolder, const sf::Vector2f t_size, const float t_weight):
	m_resourceHolder(t_resourceHolder),
	m_shipTexture(m_resourceHolder.m_textureHolder["ShipTexture"])
{
	//m_spaceShip.setFillColor(sf::Color::Green);
	m_body.setPosition(t_position);
	m_body.setSize(t_size);

	m_shipCircle.setPosition(m_body.getPosition());
	m_shipCircle.setRadius(100);
	m_shipCircle.setOrigin(m_shipCircle.getRadius(), m_shipCircle.getRadius());

	m_body.setTexture(&m_shipTexture);
	m_body.setTextureRect(sf::IntRect(0, 0, 98, 84));
	m_body.setOrigin(m_body.getSize().x / 2.0, m_body.getSize().y / 2.0);
	initStructs();

	m_mass = m_fuelTank.weight + m_sideThrusters[0].weight + m_sideThrusters[1].weight + m_Thruster.weight + m_landingGear.weight + t_weight;
	m_fuelTank.capacity = 100;
}


Spaceship::~Spaceship()
{
}

void Spaceship::update(const sf::Time t_deltaTime, const Xbox360Controller &t_controller)
{
	m_shipCircle.setPosition(m_body.getPosition());

	if (t_controller.m_currentState.RB)
	{
		m_fuelTank.capacity -= m_sideThrusters->fuelComsumption;
		m_headingVector -= m_adjustment;
		m_velocity -= m_adjustment;
		thor::setLength(m_headingVector, 70.f);
		checkShipRotate();
	}
	if (t_controller.m_currentState.LB)
	{
		m_fuelTank.capacity -= m_sideThrusters->fuelComsumption;
		m_headingVector += m_adjustment;
		m_velocity += m_adjustment;
		thor::setLength(m_headingVector, 70.f);
		checkShipRotate();
	}

	/*m_spaceShip.setRotation(m_rotation);*/

	if (t_controller.m_currentState.A)
	{
		m_thrust = m_headingVector;
		m_fuelTank.capacity -= m_Thruster.fuelConsumption;
		if (m_fuelTank.capacity <= 0)
		{
			m_thrust = { 0,0 };
		}
	}

	else
	{
		m_thrust = sf::Vector2f(0, 0);
	}

	m_position = (m_body.getPosition() + m_velocity * t_deltaTime.asSeconds() + 0.5f * m_acceleration * (t_deltaTime.asSeconds() * t_deltaTime.asSeconds()));
	applyGravity(m_mass, m_acceleration, m_thrust);
	m_velocity = m_velocity + (m_acceleration * t_deltaTime.asSeconds());
	m_body.setPosition(m_position);


	updateStructs();
	
}

void Spaceship::checkShipRotate()
{
	float angle;
	if (m_headingVector.y < 0)
	{
		angle = 360 + thor::polarAngle(m_headingVector);
	}
	else if (m_headingVector.y > 0)
	{
		angle = thor::polarAngle(m_headingVector);
	}
	else if (m_headingVector.y == 0)
	{
		if (m_headingVector.x < m_originalHeading.x)
		{
			angle = 180;
		}
		else if (m_headingVector.x > m_originalHeading.x)
		{
			angle = 0;
		}
	}
	angle += 90;
	m_body.setRotation(angle);
	m_adjustment = thor::rotatedVector(m_headingVector, 90.0f);
	thor::setLength(m_adjustment, m_adjustmentMax);
}

void Spaceship::reset(sf::Vector2f t_position)
{
	m_body.setPosition(t_position);
	m_headingVector = m_originalHeading;
	checkShipRotate();
	m_thrust = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_fuelTank.capacity = 100;
}

void Spaceship::render(sf::RenderWindow &t_window)
{
	t_window.draw(m_Thruster.m_mainThrusterBody);
	t_window.draw(m_body);
	t_window.draw(m_landingGear.m_landingbody);
	t_window.draw(m_fuelTank.m_tank);
	for (int i = 0; i < 2; i++)
	{
		t_window.draw(m_sideThrusters[0].m_sideThrusterBody);
		t_window.draw(m_sideThrusters[1].m_sideThrusterBody);
	}
}

void Spaceship::initStructs()
{
	m_landingGear.landingGearSprite = m_resourceHolder.m_textureHolder["T1LandingGear"];
	m_fuelTank.m_fuelTexture = m_resourceHolder.m_textureHolder["T1FuelTank"];
	m_Thruster.mainThrusterSprite = m_resourceHolder.m_textureHolder["T1MainEngine"];
	for (int i = 0; i < 2; i++)
	{
		m_sideThrusters[i].sideThrusterTexture = m_resourceHolder.m_textureHolder["T1SideEngine"];
	}

	m_fuelTank.m_tank.setSize(sf::Vector2f(15, 20));
	m_fuelTank.m_tank.setTexture(&m_fuelTank.m_fuelTexture);
	m_fuelTank.m_tank.setOrigin(m_fuelTank.m_tank.getGlobalBounds().width * .5, 0);
	m_fuelTank.m_tank.setPosition(m_position);
	m_fuelTank.m_tank.setRotation(m_rotation);

	m_landingGear.m_landingbody.setSize(sf::Vector2f(20, 25));
	m_landingGear.m_landingbody.setTexture(&m_landingGear.landingGearSprite);
	m_landingGear.m_landingbody.setPosition(m_position.x, m_position.y);
	m_landingGear.m_landingbody.setOrigin(m_landingGear.m_landingbody.getSize().x * .5, (m_body.getSize().y * .4) * -1);
	m_landingGear.m_landingbody.setRotation(m_rotation);

	m_Thruster.m_mainThrusterBody.setSize(sf::Vector2f(10, 10));
	m_Thruster.m_mainThrusterBody.setTexture(&m_Thruster.mainThrusterSprite);
	m_Thruster.m_mainThrusterBody.setOrigin(m_fuelTank.m_tank.getGlobalBounds().width * .4 - 1, (m_body.getSize().y * .4) * -1);
	m_Thruster.m_mainThrusterBody.setPosition(m_position);
	m_Thruster.m_mainThrusterBody.setRotation(m_rotation);

	for (int i = 0; i < 2; i++)
	{
		m_sideThrusters[i].m_sideThrusterBody.setSize(sf::Vector2f(10, 20));
		m_sideThrusters[i].m_sideThrusterBody.setTexture(&m_sideThrusters[i].sideThrusterTexture);
		m_sideThrusters[i].m_sideThrusterBody.setRotation(m_rotation);
	}
	m_sideThrusters[0].m_sideThrusterBody.setOrigin(m_body.getSize().x * .3, (m_body.getSize().y * .1) * -1);
	m_sideThrusters[1].m_sideThrusterBody.setOrigin((m_body.getSize().x * .2 -2 )* -1, (m_body.getSize().y * .1) * -1);
	
	m_sideThrusters[0].m_sideThrusterBody.setPosition(m_position);
	m_sideThrusters[1].m_sideThrusterBody.setPosition(m_position);

}

void Spaceship::updateStructs()
{
	m_fuelTank.m_tank.setPosition(m_position);
	m_landingGear.m_landingbody.setPosition(m_position);
	m_Thruster.m_mainThrusterBody.setPosition(m_position);

	m_fuelTank.m_tank.setRotation(m_body.getRotation());
	m_landingGear.m_landingbody.setRotation(m_body.getRotation());
	m_Thruster.m_mainThrusterBody.setRotation(m_body.getRotation());

	for (int i = 0; i < 2; i++)
	{
		m_sideThrusters[0].m_sideThrusterBody.setPosition(m_position);
		m_sideThrusters[1].m_sideThrusterBody.setPosition(m_position);

		m_sideThrusters[0].m_sideThrusterBody.setRotation(m_body.getRotation());
		m_sideThrusters[1].m_sideThrusterBody.setRotation(m_body.getRotation());
	}
}
