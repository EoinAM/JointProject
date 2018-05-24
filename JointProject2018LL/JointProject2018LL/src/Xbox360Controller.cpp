#include "XBOX360CONTROLLER.h"
/// <summary>
/// default constructor used to initialise the elements of the current state array
/// </summary>
Xbox360Controller::Xbox360Controller()
{
	m_currentState.A = false;
	m_currentState.B = false;
	m_currentState.X = false;
	m_currentState.Y = false;
	m_currentState.LB = false;
	m_currentState.RB = false;
	m_currentState.LeftThumbStickClick = false;
	m_currentState.RightThumbStickClick = false;
	m_currentState.DpadUp = false;
	m_currentState.DpadDown = false;
	m_currentState.DpadLeft = false;
	m_currentState.DpadRight = false;
	m_currentState.Start = false;
	m_currentState.Back = false;
	m_currentState.Xbox = false;
}

/// <summary>
/// default destructor
/// </summary>
Xbox360Controller::~Xbox360Controller()
{
}

/// <summary>
/// used to update all current state variables
/// </summary>
void Xbox360Controller::update()
{
	m_previousState = m_currentState;
	//only update if the controller is connected
	if (isConnected())
	{
		//check each button if its pressed
		//A
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 0))
		{
			m_currentState.A = true;
		}
		else
		{
			m_currentState.A = false;
		}


		//B
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 1))
		{
			m_currentState.B = true;
		}
		else
		{
			m_currentState.B = false;
		}


		//X
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 2))
		{
			m_currentState.X = true;
		}
		else
		{
			m_currentState.X = false;
		}


		//Y
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 3))
		{
			m_currentState.Y = true;
		}
		else
		{
			m_currentState.Y = false;
		}


		//LB
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 4))
		{
			m_currentState.LB = true;
		}
		else
		{
			m_currentState.LB = false;
		}


		//RB
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 5))
		{
			m_currentState.RB = true;
		}
		else
		{
			m_currentState.RB = false;
		}


		//Back
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 6))
		{
			m_currentState.Back = true;
		}
		else
		{
			m_currentState.Back = false;
		}


		//Start
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 7))
		{
			m_currentState.Start = true;
		}
		else
		{
			m_currentState.Start = false;
		}


		//LeftThumbStick
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 8))
		{
			m_currentState.LeftThumbStickClick = true;
		}
		else
		{
			m_currentState.LeftThumbStickClick = false;
		}


		//RightThumbStick
		if (sf::Joystick::isButtonPressed(sf_Joystick_index, 9))
		{
			m_currentState.RightThumbStickClick = true;
		}
		else
		{
			m_currentState.RightThumbStickClick = false;
		}


		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::X) > 20 || sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::X) < -20)
		{
			m_currentState.LeftThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::X);
		}
		else
		{
			m_currentState.LeftThumbStick.x = 0;
		}
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Y) > 20 || sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Y) < -20)
		{
			m_currentState.LeftThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Y);
		}
		else
		{
			m_currentState.LeftThumbStick.y = 0;
		}
		

		//Get the axis position of the RightThumbStick (U,R)
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::U) > joyStickDeadzone || sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::U) < -joyStickDeadzone)
		{
			m_currentState.RightThumbStick.x = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::U);
		}
		else
		{
			m_currentState.RightThumbStick.x = 0;
		}
		
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::R) > joyStickDeadzone || sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::R) < -joyStickDeadzone)
		{
			m_currentState.RightThumbStick.y = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::R);
		}
		else
		{
			m_currentState.RightThumbStick.y = 0;
		}
		

		//Check Dpad Directions
		//Up
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) > dPadThreshold)
		{
			m_currentState.DpadUp = true;
		}
		else
		{
			m_currentState.DpadUp = false;
		}


		//Down
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovY) < -dPadThreshold)
		{
			m_currentState.DpadDown = true;
		}
		else
		{
			m_currentState.DpadDown = false;
		}


		//Left
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) < -dPadThreshold)
		{
			m_currentState.DpadLeft = true;
		}
		else
		{
			m_currentState.DpadLeft = false;
		}


		//Right
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::PovX) > dPadThreshold)
		{
			m_currentState.DpadRight = true;
		}
		else
		{
			m_currentState.DpadRight = false;
		}


		//check the controller trigger axis
		//right
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) < -0.001526)
		{
			m_currentState.Rtrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) * -1.0f;
			m_currentState.Ltrigger = 0;
		}


		//left
		else if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) > 0)
		{
			m_currentState.Ltrigger = sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z);
			m_currentState.Rtrigger = 0;
		}


		//make sure that when the value of the trigger is between -0.001526 and 0 that the trigger variables are set to 0 so that it is accurate(sort of a deadzone)
		if (sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) >= -0.001526 && sf::Joystick::getAxisPosition(sf_Joystick_index, sf::Joystick::Axis::Z) < 0)
		{
			m_currentState.Rtrigger = 0;
			m_currentState.Ltrigger = 0;
		}


	}

}

/// <summary>
/// check if the controller is still connected
/// </summary>
/// <returns>wether the controller is connected or not</returns>
bool Xbox360Controller::isConnected()
{
	if (sf::Joystick::isConnected(sf_Joystick_index))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// connect the controller and set its joystick index(0 by default in this project)
/// </summary>
/// <returns>whether it was connected or not</returns>
bool Xbox360Controller::connect()
{
	if (sf::Joystick::isConnected(0))
	{
		sf_Joystick_index = 0;
		return true;
	}
	else
	{
		return false;
	}
}