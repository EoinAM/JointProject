#include "UiLibrary.h"


/// <summary>
/// Default constructor.
/// </summary>
/// <param name="t_string">The string the label will display...Defaulted to "".</param>
/// <param name="t_pos">The centre point of the label...Defaulted to ( 0 , 0 ).</param>
/// <param name="t_font">The font used for the label...Defaulted to an empty font object.</param>
/// <param name="t_characterSize">The size of the letters in the label...Defaulted to 20.</param>
/// <param name="t_color">The color of the text...Defaulted to white.</param>
Label::Label(const std::string & t_string, const sf::Vector2f & t_pos, const sf::Font & t_font, const int t_characterSize, const sf::Color t_color)
{
	//Call the initialiser.
	init(t_string, t_pos, t_font, t_characterSize, t_color);
}

/// <summary>
/// Set up all the values of a label.
/// </summary>
/// <param name="t_string">The string the label will display...Defaulted to "".</param>
/// <param name="t_pos">The centre point of the label...Defaulted to ( 0 , 0 ).</param>
/// <param name="t_font">The font used for the label...Defaulted to an empty font object.</param>
/// <param name="t_characterSize">The size of the letters in the label...Defaulted to 20.</param>
/// <param name="t_color">The color of the text...Defaulted to white.</param>
void Label::init(const std::string & t_string, const sf::Vector2f & t_pos, const sf::Font & t_font, const int t_characterSize, const sf::Color t_color)
{

	m_text.setString(t_string);
	m_text.setPosition(t_pos);
	m_text.setFont(t_font);
	m_text.setCharacterSize(t_characterSize);
	m_text.setFillColor(t_color);
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);

}

/// <summary>
/// Used to draw a label object to the render window passed to the function.
/// </summary>
/// <param name="t_window">SFML Render Window.</param>
void Label::render(sf::RenderWindow & t_window)
{
	// No need to render the text if there isn't any.
	if (m_text.getString() != "")
	{
		t_window.draw(m_text);
	}
}

/// <summary>
/// Set the string of the label.
/// </summary>
/// <param name="t_string">The string the label will display.</param>
void Label::string(const std::string & t_string)
{
	m_text.setString(t_string);
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Returns the string the label is displaying.
/// </summary>
/// <returns>The labels string.</returns>
std::string Label::string()
{
	return m_text.getString();
}

/// <summary>
/// Sets the position of the centre point of the label.
/// </summary>
/// <param name="t_pos">The centre point of the label.</param>
void Label::position(const sf::Vector2f & t_pos)
{
	m_text.setPosition(t_pos);
}

/// <summary>
/// Returns the position of the label.
/// </summary>
/// <returns>The centre point of the label.</returns>
sf::Vector2f Label::position()
{
	return m_text.getPosition();
}

/// <summary>
/// Sets the character size of the text in the label.
/// </summary>
/// <param name="t_characterSize">Integer value for the character size.</param>
void Label::characterSize(const int & t_characterSize)
{
	m_text.setCharacterSize(t_characterSize);
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Returns the character size of the text in the label.
/// </summary>
/// <returns>Integer value of the character size.</returns>
int Label::characterSize()
{
	return m_text.getCharacterSize();
}

/// <summary>
/// Sets the color of the text in the label.
/// </summary>
/// <param name="t_color">The color of the text.</param>
void Label::color(const sf::Color & t_color)
{
	m_text.setFillColor(t_color);
}

/// <summary>
/// Returns the color of the text in the label.
/// </summary>
/// <returns>The color of the text in the label.</returns>
sf::Color Label::color()
{
	return m_text.getFillColor();
}

/// <summary>
/// Returns a vector containing the width and height of the text in the label.
/// </summary>
/// <returns>sf::Vector2f containing the width and height of the text in the label.</returns>
sf::Vector2f Label::size()
{
	return sf::Vector2f(m_text.getLocalBounds().width, m_text.getLocalBounds().height);
}

/// <summary>
/// Sets the font the text will use.
/// </summary>
/// <param name="t_font">Reference to the font to be used.</param>
void Label::font(const sf::Font & t_font)
{
	m_text.setFont(t_font);
	//update the origin as the font may have larger/smaller characters.
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Default constructor.
/// </summary>
/// <param name="t_pos">The position the button is to be drawn at...Defaulted to ( 0 , 0 ).</param>
/// <param name="t_size">The size of the button, width and height...Defaulted to ( 0 , 0 ).</param>
/// <param name="t_texture">The image of the button...Defaulted to an empty texture object.</param>
/// <param name="t_label">The label the button will use... Defaulted to an empty Label object.</param>
/// <param name="t_isHighlighted">Whether the button is currently highlighted...Defaulted to false.</param>
/// <param name="t_color">The color of the button...Defaulted to white.</param>
Button::Button(const sf::Vector2f & t_pos, const sf::Vector2f & t_size, const sf::Texture & t_texture, const Label & t_label, const bool t_isHighlighted, const sf::Color & t_color)
{
	//call the initialiser.
	init(t_pos, t_size, t_texture, t_label, t_isHighlighted, t_color);
}

/// <summary>
/// Set up all the values of the button.
/// </summary>
/// <param name="t_pos">The position the button is to be drawn at...Defaulted to ( 0 , 0 ).</param>
/// <param name="t_size">The size of the button, width and height...Defaulted to ( 0 , 0 ).</param>
/// <param name="t_texture">The image of the button...Defaulted to an empty texture object.</param>
/// <param name="t_label">The label the button will use... Defaulted to an empty Label object.</param>
/// <param name="t_isHighlighted">Whether the button is currently highlighted...Defaulted to false.</param>
/// <param name="t_color">The color of the button...Defaulted to white.</param>
void Button::init(const sf::Vector2f & t_pos, const sf::Vector2f & t_size, const sf::Texture & t_texture, const Label & t_label, const bool t_isHighlighted, const sf::Color & t_color)
{
	//set up the body of the button.
	m_body.setPosition(t_pos);
	m_body.setSize(t_size);
	m_body.setTexture(&t_texture);
	m_body.setFillColor(t_color);
	m_body.setOrigin(t_size.x / 2.0f, t_size.y / 2.0f);
	m_body.setOutlineColor(sf::Color::Black);
	//set the label up.
	m_label = t_label;
	//reset the booleans
	reset();
	//set wether the button is highlighted or not.
	m_isHighlighted = t_isHighlighted;
}

/// <summary>
/// Update the button object.
/// </summary>
/// <param name="t_dTime">Time that has passed since the last time the button was updated.</param>
/// <param name="t_controller">The controller input handler.</param>
/// <param name="t_animationScalar">The rate at which animations happen.</param>
void Button::update(const sf::Time t_dTime, const Xbox360Controller & t_controller, const int t_animationScalar)
{
	//if the button is currently highlighted.
	if (m_isHighlighted)
	{
		//check if the user has pressed the a button.
		if (!m_isPressed && (t_controller.m_currentState.A && !t_controller.m_previousState.A))
		{
			m_isPressed = true;
		}
		//if the button is now highlighted, but wasnt before.
		if (!m_previouslyHighlighted)
		{
			m_highlightOn = true;
		}
		//if the animation cycle needs to happen.
		if (m_highlightOn)
		{
			//if the animation hasnt completed.
			if (m_body.getOutlineThickness() < 5)
			{
				m_body.setOutlineThickness(m_body.getOutlineThickness() + (0.3f * t_animationScalar));
			}
			//if it has completed.
			else
			{
				m_highlightOn = false;
			}
		}
	}
	//if the button isnt highlighted
	else
	{
		//if the animation needs cycle to happen.
		if (m_body.getOutlineThickness() > 0)
		{
			m_body.setOutlineThickness(m_body.getOutlineThickness() - (0.4f * t_animationScalar));
		}
		//if it has completed.
		else
		{
			m_body.setOutlineThickness(0);
		}
	}
	//update the booleans.
	m_previouslyHighlighted = m_isHighlighted;
}

/// <summary>
/// Draw the button object to the render window passed.
/// </summary>
/// <param name="t_window">SFML Render Window.</param>
void Button::render(sf::RenderWindow &t_window)
{
	//draw the objects to the screen.
	t_window.draw(m_body);
	m_label.render(t_window);
}

/// <summary>
/// Return the position the button is being drawn at.
/// </summary>
/// <returns>The position of the button.</returns>
sf::Vector2f Button::position()
{
	return m_body.getPosition();
}

/// <summary>
/// Set the position the button is to be drawn at.
/// </summary>
/// <param name="t_pos">The position the button is to be drawn at.</param>
void Button::position(const sf::Vector2f & t_pos)
{
	m_body.setPosition(t_pos);
}

/// <summary>
/// Return the color of the button.
/// </summary>
/// <returns>The color of the button.</returns>
sf::Color Button::color()
{
	return m_body.getFillColor();
}

/// <summary>
/// Set the color of the button.
/// </summary>
/// <param name="t_color">The color the button is to be drawn as.</param>
void Button::color(const sf::Color & t_color)
{
	m_body.setFillColor(t_color);
}

/// <summary>
/// Return the size of the button, width and height.
/// </summary>
/// <returns>sf::Vector2f containing the widtha nd height of the button.</returns>
sf::Vector2f Button::size()
{
	return m_body.getSize();
}

/// <summary>
/// Set the size of the button.
/// </summary>
/// <param name="t_size">sf::Vector2f containing the width and height.</param>
void Button::size(const sf::Vector2f & t_size)
{
	m_body.setSize(t_size);
	//update the origin.
	m_body.setOrigin(t_size.x / 2.0f, t_size.y / 2.0f);
}

/// <summary>
/// Set the texture of the button.
/// </summary>
/// <param name="t_texture">sf::Texture object</param>
void Button::texture(const sf::Texture & t_texture)
{
	m_body.setTexture(&t_texture);
}

/// <summary>
/// Set the label of the button object.
/// </summary>
/// <param name="t_label">Label object.</param>
void Button::label(const Label & t_label)
{
	m_label = t_label;
}

/// <summary>
/// Return the label object in the button.
/// </summary>
/// <returns>Label object.</returns>
Label Button::label()
{
	return m_label;
}

/// <summary>
/// Set whether the button is highlighted.
/// </summary>
/// <param name="t_bool">Boolean.</param>
void Button::highlighted(const bool & t_bool)
{
	m_isHighlighted = t_bool;
}

/// <summary>
/// Return whether the button is highlighted.
/// </summary>
/// <returns>Boolean.</returns>
bool Button::highlighted()
{
	return m_isHighlighted;
}

/// <summary>
/// Set wether the button has been pressed or not.
/// </summary>
/// <param name="t_bool">Boolean.</param>
void Button::pressed(const bool & t_bool)
{
	m_isPressed = t_bool;
}

/// <summary>
/// Return whether the button has been pressed or not.
/// </summary>
/// <returns>Boolean.</returns>
bool Button::pressed()
{
	return m_isPressed;
}

void Button::TextureRect(const sf::IntRect & t_rect)
{
	m_body.setTextureRect(t_rect);
}

/// <summary>
/// Reset the button to default values.
/// </summary>
void Button::reset()
{
	m_isPressed = false;
	m_isHighlighted = false;
	m_previouslyHighlighted = false;
	m_highlightOn = false;
	m_body.setOutlineThickness(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Default constructor.
/// </summary>
/// <param name="t_position">Position of the left most/bottom circle.</param>
/// <param name="t_barLength">The max length of the centre bar.</param>
/// <param name="t_initialValue">The value the slider is set at originally.</param>
/// <param name="t_orientation">The orientation of the slider, e.g. Horizontally/Vertically.</param>
/// <param name="t_highlighted">Whether the is highlighted or not.</param>
/// <param name="t_color">The color of the slider.</param>
Slider::Slider(const sf::Vector2f & t_position, const int t_barLength, float t_initialValue, BarOrientation t_orientation, const bool t_highlighted, const sf::Color &t_color)
{
	//call the initialiser.
	init(t_position, t_barLength, t_initialValue, t_orientation, t_highlighted, t_color);
}

/// <summary>
/// Initialise the variables in the slider.
/// </summary>
/// <param name="t_position">Position of the left most/bottom circle.</param>
/// <param name="t_barLength">The max length of the centre bar.</param>
/// <param name="t_initialValue">The value the slider is set at originally.</param>
/// <param name="t_orientation">The orientation of the slider, e.g. Horizontally/Vertically.</param>
/// <param name="t_highlighted">Whether the is highlighted or not.</param>
/// <param name="t_color">The color of the slider.</param>
void Slider::init(const sf::Vector2f & t_position, const int t_barLength, float t_initialValue, BarOrientation t_orientation, const bool t_highlighted, const sf::Color &t_color)
{
	//initialise the values passed.
	m_orientation = t_orientation;
	m_length = t_barLength;
	m_value = t_initialValue;
	m_isHighlighted = t_highlighted;
	m_highlightOn = false;
	m_isPressed = false;

	//depending on the orientation passed set up the shape of the slider
	switch (m_orientation)
	{
	case BarOrientation::Horizontal:
		m_startPoint.setFillColor(t_color);
		m_startPoint.setPosition(t_position);
		m_startPoint.setRadius(20);
		m_startPoint.setOrigin(20, 20);

		m_endPoint.setFillColor(t_color);
		m_endPoint.setPosition(t_position + sf::Vector2f(t_barLength, 0));
		m_endPoint.setRadius(20);
		m_endPoint.setOrigin(20, 20);

		m_centreBar.setFillColor(t_color);
		m_centreBar.setSize(sf::Vector2f(t_barLength, 20));
		m_centreBar.setOrigin(t_barLength / 2.0f, 10);
		m_centreBar.setPosition(t_position + sf::Vector2f(t_barLength / 2.0f, 0));

		m_barIndicator.setFillColor(t_color);
		m_barIndicator.setSize(sf::Vector2f(20, 50));
		m_barIndicator.setOrigin(10, 25);
		m_barIndicator.setPosition(t_position + sf::Vector2f(t_barLength * (t_initialValue / 100.f), 0));
		break;
	case BarOrientation::Vertical:
		m_startPoint.setFillColor(t_color);
		m_startPoint.setPosition(t_position);
		m_startPoint.setRadius(20);
		m_startPoint.setOrigin(20, 20);

		m_endPoint.setFillColor(t_color);
		m_endPoint.setPosition(t_position + sf::Vector2f(0, t_barLength));
		m_endPoint.setRadius(20);
		m_endPoint.setOrigin(20, 20);

		m_centreBar.setFillColor(t_color);
		m_centreBar.setSize(sf::Vector2f(20, t_barLength));
		m_centreBar.setOrigin(10, t_barLength / 2.0f);
		m_centreBar.setPosition(t_position + sf::Vector2f(0, t_barLength / 2.0f));

		m_barIndicator.setFillColor(t_color);
		m_barIndicator.setSize(sf::Vector2f(50, 20));
		m_barIndicator.setOrigin(25, 10);
		m_barIndicator.setPosition(t_position + sf::Vector2f(0, t_barLength * (t_initialValue / 100.f)));
		break;
	default:
		break;
	}
}

/// <summary>
/// Update the slider, handle any input from the user.
/// </summary>
/// <param name="t_dTime">Time since th last time the slider was updated.</param>
/// <param name="t_controller">Controller input class.</param>
/// <param name="t_animationScalar">Scalar for the animations.</param>
void Slider::update(const sf::Time t_dTime, const Xbox360Controller & t_controller, const int t_animationScalar)
{
	//if the slider is highlighted
	if (m_isHighlighted)
	{
		//check if the slider is pressed and update accordingly
		m_isPressed = true;
		m_startPoint.setOutlineColor(sf::Color::Red);
		m_endPoint.setOutlineColor(sf::Color::Red);
		m_centreBar.setOutlineColor(sf::Color::Red);
		m_barIndicator.setOutlineColor(sf::Color::Red);

		//if it wasnt highligted last frame the animation cycle needs to run.
		if (!m_prevHighlighted)
		{
			m_highlightOn = true;
		}
		if (m_highlightOn)
		{
			if (m_startPoint.getOutlineThickness() < 5)
			{
				m_startPoint.setOutlineThickness(m_startPoint.getOutlineThickness() + (0.3f * t_animationScalar));
				m_endPoint.setOutlineThickness(m_endPoint.getOutlineThickness() + (0.3f * t_animationScalar));
				m_centreBar.setOutlineThickness(m_centreBar.getOutlineThickness() + (0.3f * t_animationScalar));
				m_barIndicator.setOutlineThickness(m_barIndicator.getOutlineThickness() + (0.3f * t_animationScalar));
			}
			else
			{
				m_highlightOn = false;
			}
		}
		//if the label is pressed allow the values to be changed
		if (m_isPressed)
		{
			switch (m_orientation)
			{
			case BarOrientation::Horizontal:
				if (t_controller.m_currentState.LeftThumbStick.x > 0)
				{
					m_value++;
				}
				else if (t_controller.m_currentState.LeftThumbStick.x < 0)
				{
					m_value--;
				}
				if (m_barIndicator.getPosition().x > m_endPoint.getPosition().x - 30)
				{
					m_value = m_value - 1;
				}

				if (m_barIndicator.getPosition().x < m_startPoint.getPosition().x + 30)
				{
					m_value = m_value + 1;
				}

				m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length * (m_value / 100.f), 0));

				break;
			case BarOrientation::Vertical:
				if (t_controller.m_currentState.LeftThumbStick.y > 0)
				{
					m_value++;
				}
				else if (t_controller.m_currentState.LeftThumbStick.y < 0)
				{
					m_value--;
				}
				m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length * (m_value / 100.f)));
				break;
			default:
				break;
			}
		}
	}
	//if the slider isnt highlighted animation cycle needs to run until completion.
	else
	{
		if (m_startPoint.getOutlineThickness() > 0)
		{
			m_startPoint.setOutlineThickness(m_startPoint.getOutlineThickness() - (0.3f * t_animationScalar));
			m_endPoint.setOutlineThickness(m_endPoint.getOutlineThickness() - (0.3f * t_animationScalar));
			m_centreBar.setOutlineThickness(m_centreBar.getOutlineThickness() - (0.3f * t_animationScalar));
			m_barIndicator.setOutlineThickness(m_barIndicator.getOutlineThickness() - (0.3f * t_animationScalar));
		}
		else
		{
			m_startPoint.setOutlineThickness(0);
			m_endPoint.setOutlineThickness(0);
			m_centreBar.setOutlineThickness(0);
			m_barIndicator.setOutlineThickness(0);
		}
	}
	//update the previously highligted bool.
	m_prevHighlighted = m_isHighlighted;
}

/// <summary>
/// Draw the slider and objects to the render window.
/// </summary>
/// <param name="t_window">SFML Render Window.</param>
void Slider::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_centreBar);
	t_window.draw(m_startPoint);
	t_window.draw(m_endPoint);
	t_window.draw(m_barIndicator);
}

/// <summary>
/// Returns the position of the left-most/bottom circle.
/// </summary>
/// <returns>sf::Vector2f with the position.</returns>
sf::Vector2f Slider::position()
{
	return m_startPoint.getPosition();
}

/// <summary>
/// Set the position of the slider.
/// </summary>
/// <param name="t_pos">sf::vector2f containing the intended location.</param>
void Slider::position(const sf::Vector2f & t_pos)
{
	//depending on the orientation set the positions correctly.
	switch (m_orientation)
	{
	case BarOrientation::Horizontal:
		m_startPoint.setPosition(t_pos);
		m_endPoint.setPosition(t_pos + sf::Vector2f(m_length, 0));
		m_centreBar.setPosition(t_pos + sf::Vector2f(m_length / 2.0f, 0));
		m_barIndicator.setPosition(t_pos + sf::Vector2f(m_length * (m_value / 100.f), 0));
		break;
	case BarOrientation::Vertical:
		m_startPoint.setPosition(t_pos);
		m_endPoint.setPosition(t_pos + sf::Vector2f(0, m_length));
		m_centreBar.setPosition(t_pos + sf::Vector2f(0, m_length / 2.0f));
		m_barIndicator.setPosition(t_pos + sf::Vector2f(0, m_length * (m_value / 100.f)));
		break;
	default:
		break;
	}
}

/// <summary>
/// Return the color of thr slider.
/// </summary>
/// <returns>sf::color</returns>
sf::Color Slider::color()
{
	return m_startPoint.getFillColor();
}

/// <summary>
/// Set the color of the slider.
/// </summary>
/// <param name="t_color">sf::color</param>
void Slider::color(const sf::Color & t_color)
{
	m_startPoint.setFillColor(t_color);
	m_endPoint.setOutlineColor(t_color);
	m_centreBar.setOutlineColor(t_color);
	m_barIndicator.setOutlineColor(t_color);
}

/// <summary>
/// Return the max lenght of the centre bar.
/// </summary>
/// <returns>float</returns>
float Slider::length()
{
	return m_length;
}

/// <summary>
/// Set the max length of the slider.
/// </summary>
/// <param name="t_size">float</param>
void Slider::length(const float & t_size)
{
	m_length = t_size;
	switch (m_orientation)
	{
	case BarOrientation::Horizontal:
		m_endPoint.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length, 0));
		m_centreBar.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length / 2.0f, 0));
		m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length * (m_value / 100.f), 0));
		break;
	case BarOrientation::Vertical:
		m_endPoint.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length));
		m_centreBar.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length / 2.0f));
		m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length * (m_value / 100.f)));
		break;
	default:
		break;
	}
}

/// <summary>
/// Set whether the slider is highlighted or not.
/// </summary>
/// <returns>boolean</returns>
void Slider::highlighted(const bool & t_bool)
{
	m_isHighlighted = t_bool;
}

/// <summary>
/// Return whether the slider is highlighted or not.
/// </summary>
/// <param name="t_bool">boolean</param>
bool Slider::highlighted()
{
	return m_isHighlighted;
}

/// <summary>
/// Set whether the slider has been pressed(If its pressed the value can be changed).
/// </summary>
/// <param name="t_bool">boolean</param>
void Slider::pressed(const bool & t_bool)
{
	m_isPressed = t_bool;
}

/// <summary>
/// Return whether the slider has been pressed or not.
/// </summary>
/// <returns>boolean</returns>
bool Slider::pressed()
{
	return m_isPressed;
}

/// <summary>
/// Returns the value the slider is currently at(float value between 0 and 100).
/// </summary>
/// <returns>float</returns>
float Slider::value()
{
	return m_value;
}

/// <summary>
/// Set the value the slider is at(Value can be a float value between 0 and 100)
/// </summary>
/// <param name="t_value">float</param>
void Slider::value(const float & t_value)
{
	//error checking, the value cant be less than 0 or greater than 100
	if (t_value < 0)
	{
		m_value = 0;
	}
	else if (t_value > 100)
	{
		m_value = 100;
	}
	else
	{
		m_value = t_value;
	}
	m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length * (m_value / 100.f)));
}

/// <summary>
/// Returns what way the bar is orientated(Horizontal or vertical).
/// </summary>
/// <returns>BarOrientation enum.</returns>
BarOrientation Slider::orientation()
{
	return m_orientation;
}

/// <summary>
/// Set the orientation of the bar.
/// </summary>
/// <param name="t_orientation">BarOrientation enum.</param>
void Slider::orientation(const BarOrientation & t_orientation)
{
	//update the orientation, move the shapes to the correct positions
	m_orientation = t_orientation;
	switch (m_orientation)
	{
	case BarOrientation::Horizontal:
		m_endPoint.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length, 0));
		m_centreBar.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length / 2.0f, 0));
		m_centreBar.setSize(sf::Vector2f(m_length, 20));
		m_centreBar.setOrigin(m_length / 2.0f, 10);
		m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(m_length * (m_value / 100.f), 0));
		m_barIndicator.setSize(sf::Vector2f(20, 50));
		m_barIndicator.setOrigin(10, 25);
		break;
	case BarOrientation::Vertical:
		m_endPoint.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length));
		m_centreBar.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length / 2.0f));
		m_centreBar.setSize(sf::Vector2f(20, m_length));
		m_centreBar.setOrigin(10, m_length / 2.0f);
		m_barIndicator.setPosition(m_startPoint.getPosition() + sf::Vector2f(0, m_length * (m_value / 100.f)));
		m_barIndicator.setSize(sf::Vector2f(50, 20));
		m_barIndicator.setOrigin(25, 10);
		break;
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// <summary>
/// Default constructor.
/// </summary>
/// <param name="t_pos">The position of the checkbox.</param>
/// <param name="t_size">The size of the checkbox.</param>
/// <param name="t_isHighlighted">whether the checkbox is highlighted or not.</param>
/// <param name="t_color">the color of the checkbox.</param>
CheckBox::CheckBox(const sf::Vector2f & t_pos, const sf::Vector2f & t_size, const bool t_isHighlighted, const sf::Color & t_color)
{
	init(t_pos, t_size, t_isHighlighted, t_color);
}

/// <summary>
/// Initialise the checkbox.
/// </summary>
/// <param name="t_pos">The position of the checkbox.</param>
/// <param name="t_size">The size of the checkbox.</param>
/// <param name="t_isHighlighted">whether the checkbox is highlighted or not.</param>
/// <param name="t_color">the color of the checkbox.</param>
void CheckBox::init(const sf::Vector2f & t_pos, const sf::Vector2f & t_size, const bool t_isHighlighted, const sf::Color & t_color)
{
	m_body.setPosition(t_pos);
	m_body.setSize(t_size);
	m_body.setFillColor(t_color);
	m_body.setOrigin(t_size.x / 2.0f, t_size.y / 2.0f);
	m_body.setOutlineColor(t_color);
	reset();
	m_isHighlighted = t_isHighlighted;
	m_highlightOn = false;
	m_isPressed = false;
}

/// <summary>
/// Update the check box variables.
/// </summary>
/// <param name="t_dTime">Time since the last time the check box was updated.</param>
/// <param name="t_controller">Controller input class</param>
/// <param name="t_animationScalar">Scalar for the animations.</param>
void CheckBox::update(const sf::Time t_dTime, const Xbox360Controller & t_controller, const int t_animationScalar)
{
	if (m_isHighlighted)
	{
		if (!m_isPressed && (t_controller.m_currentState.A && !t_controller.m_previousState.A))
		{
			m_isPressed = true;
			m_body.setFillColor(sf::Color::Black);
		}
		else if (m_isPressed && (t_controller.m_currentState.A && !t_controller.m_previousState.A))
		{
			m_isPressed = false;
			m_body.setFillColor(sf::Color::White);
		}
		if (!m_previouslyHighlighted)
		{
			m_highlightOn = true;
		}
		if (m_highlightOn)
		{
			if (m_body.getOutlineThickness() < 5)
			{
				m_body.setOutlineThickness(m_body.getOutlineThickness() + (0.3f * t_animationScalar));
			}
			else
			{
				m_highlightOn = false;
			}
		}
	}
	else
	{
		if (m_body.getOutlineThickness() > 0)
		{
			m_body.setOutlineThickness(m_body.getOutlineThickness() - (0.4f * t_animationScalar));
		}
		else
		{
			m_body.setOutlineThickness(0);
		}
	}
	m_previouslyHighlighted = m_isHighlighted;
}

/// <summary>
/// Draw the check box to the screen.
/// </summary>
/// <param name="t_window">SFML Render Window</param>
void CheckBox::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_body);
}

/// <summary>
/// Retun the position of the check box
/// </summary>
/// <returns>sf::vector2f</returns>
sf::Vector2f CheckBox::position()
{
	return m_body.getPosition();
}

/// <summary>
/// set the position of the checkbox
/// </summary>
/// <param name="t_pos">sf::vector2f</param>
void CheckBox::position(const sf::Vector2f & t_pos)
{
	m_body.setPosition(t_pos);
}

/// <summary>
/// Return the color of the check box.
/// </summary>
/// <returns>sf::color</returns>
sf::Color CheckBox::color()
{
	return m_body.getFillColor();
}

/// <summary>
/// Set the color of the check box.
/// </summary>
/// <param name="t_color">sf::color</param>
void CheckBox::color(const sf::Color & t_color)
{
	m_body.setFillColor(t_color);
}

/// <summary>
/// Return the size of the check box.
/// </summary>
/// <returns>sf::vector2f</returns>
sf::Vector2f CheckBox::size()
{
	return m_body.getSize();
}

/// <summary>
/// Set the size of the check box.
/// </summary>
/// <param name="t_size">sf::vector2f</param>
void CheckBox::size(const sf::Vector2f & t_size)
{
	m_body.setSize(t_size);
}

/// <summary>
/// Set whether the check box is highlighted or not.
/// </summary>
/// <param name="t_bool">boolean.</param>
void CheckBox::highlighted(const bool & t_bool)
{
	m_isHighlighted = t_bool;
}

/// <summary>
/// Return whether th check box is highlighted or not
/// </summary>
/// <returns>boolean</returns>
bool CheckBox::highlighted()
{
	return m_isHighlighted;
}

/// <summary>
/// Set whether the check box is pressed or not.
/// </summary>
/// <param name="t_bool">boolean</param>
void CheckBox::pressed(const bool & t_bool)
{
	m_isPressed = t_bool;
}

/// <summary>
/// Return whether the check box has been oressed or not.
/// </summary>
/// <returns>boolean</returns>
bool CheckBox::pressed()
{
	return m_isPressed;
}

/// <summary>
/// Reset the booleans like a fresh button, un highlighted and unpressed, no animation occurred.
/// </summary>
void CheckBox::reset()
{
	m_isPressed = false;
	m_isHighlighted = false;
	m_previouslyHighlighted = false;
	m_highlightOn = false;
	m_body.setOutlineThickness(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
//RadioButton::RadioButton()
//{
//	setUp();
//}
//
//void RadioButton::setPosition(sf::Vector2f t_pos)
//{
//	m_radioButton.setPosition(t_pos);
//}
//
//void RadioButton::pressed()
//{
//	m_pressed = true;
//}
//
//void RadioButton::unPressed()
//{
//	m_pressed = false;
//}
//
//void RadioButton::update()
//{
//}
//
//void RadioButton::render(sf::RenderWindow & t_window)
//{
//	t_window.draw(m_radioButton);
//	if (m_pressed)
//	{
//		t_window.draw(m_radioButtonFill);
//	}
//}
//
//void RadioButton::setUp()
//{
//	m_radioButton.setTexture(&m_radioButtonTexture);
//	m_radioButton.setSize(sf::Vector2f(20, 20));
//	m_radioButton.setOrigin(sf::Vector2f(m_radioButton.getGlobalBounds().width / 2, m_radioButton.getGlobalBounds().height / 2));
//	m_radioButtonFill.setTexture(&m_radioButtonFillTexture);
//	m_radioButtonFill.setSize(sf::Vector2f(10, 10));
//	m_radioButtonFill.setPosition(m_radioButton.getOrigin());
//	m_radioButtonFill.setOrigin(sf::Vector2f(m_radioButtonFill.getGlobalBounds().width / 2, m_radioButtonFill.getGlobalBounds().height / 2));
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Keyboard::Keyboard()
{
	setUp();
}

void Keyboard::setPosition(sf::Vector2f t_pos)
{
}

void Keyboard::update()
{
}

void Keyboard::render(sf::RenderWindow & t_window)
{
}

void Keyboard::setUp()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////