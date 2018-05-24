/// <summary>
/// Description: Sets up all ui elements needed.
/// No keyboard input to be taken in here , input should be in other files
/// and based on input the appropriate function is called to make the change.
/// </summary>

#ifndef UILIBRARY
#define UILIBRARY

#include <SFML\Graphics.hpp>
#include "Xbox360Controller.h"
#include <iostream>


/// <summary>
/// Label class, used as text, to label buttons, and as titles
/// </summary>
class Label
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	/// <param name="t_string">The string the label will display...Defaulted to "".</param>
	/// <param name="t_pos">The centre point of the label...Defaulted to ( 0 , 0 ).</param>
	/// <param name="t_font">The font used for the label...Defaulted to an empty font object.</param>
	/// <param name="t_characterSize">The size of the letters in the label...Defaulted to 20.</param>
	/// <param name="t_color">The color of the text...Defaulted to white.</param>
	Label(const std::string &t_string = std::string(""), const sf::Vector2f &t_pos = sf::Vector2f(0, 0), const sf::Font &t_font = sf::Font(), const int t_characterSize = 20, const sf::Color t_color = sf::Color::White);

	/// <summary>
	/// Set up all the values of a label.
	/// </summary>
	/// <param name="t_string">The string the label will display...Defaulted to "".</param>
	/// <param name="t_pos">The centre point of the label...Defaulted to ( 0 , 0 ).</param>
	/// <param name="t_font">The font used for the label...Defaulted to an empty font object.</param>
	/// <param name="t_characterSize">The size of the letters in the label...Defaulted to 20.</param>
	/// <param name="t_color">The color of the text...Defaulted to white.</param>
	void init(const std::string &t_string = std::string(""), const sf::Vector2f &t_pos = sf::Vector2f(0, 0), const sf::Font &t_font = sf::Font(), const int t_characterSize = 20, const sf::Color t_color = sf::Color::White);

	/// <summary>
	/// Used to draw a label object to the render window passed to the function.
	/// </summary>
	/// <param name="t_window">SFML Render Window.</param>
	void render(sf::RenderWindow &t_window);

	//Getter/Setter functions.

	/// <summary>
	/// Set the string of the label.
	/// </summary>
	/// <param name="t_string">The string the label will display.</param>
	void string(const std::string &t_string);
	/// <summary>
	/// Returns the string the label is displaying.
	/// </summary>
	/// <returns>The labels string.</returns>
	std::string string();
	/// <summary>
	/// Sets the position of the centre point of the label.
	/// </summary>
	/// <param name="t_pos">The centre point of the label.</param>
	void position(const sf::Vector2f &t_pos);
	/// <summary>
	/// Returns the position of the label.
	/// </summary>
	/// <returns>The centre point of the label.</returns>
	sf::Vector2f position();
	/// <summary>
	/// Sets the character size of the text in the label.
	/// </summary>
	/// <param name="t_characterSize">Integer value for the character size.</param>
	void characterSize(const int &t_characterSize);
	/// <summary>
	/// Returns the character size of the text in the label.
	/// </summary>
	/// <returns>Integer value of the character size.</returns>
	int characterSize();
	/// <summary>
	/// Sets the color of the text in the label.
	/// </summary>
	/// <param name="t_color">The color of the text.</param>
	void color(const sf::Color &t_color);
	/// <summary>
	/// Returns the color of the text in the label.
	/// </summary>
	/// <returns>The color of the text in the label.</returns>
	sf::Color color();
	/// <summary>
	/// Returns a vector containing the width and height of the text in the label.
	/// </summary>
	/// <returns>sf::Vector2f containing the width and height of the text in the label.</returns>
	sf::Vector2f size();
	/// <summary>
	/// Sets the font the text will use.
	/// </summary>
	/// <param name="t_font">Reference to the font to be used.</param>
	void font(const sf::Font &t_font);
private:
	//SFML Text Object
	sf::Text m_text;
};



/// <summary>
/// Button class, contains a label, used in menus
/// </summary>
class Button
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="t_pos">The position the button is to be drawn at...Defaulted to ( 0 , 0 ).</param>
	/// <param name="t_size">The size of the button, width and height...Defaulted to ( 0 , 0 ).</param>
	/// <param name="t_texture">The image of the button...Defaulted to an empty texture object.</param>
	/// <param name="t_label">The label the button will use... Defaulted to an empty Label object.</param>
	/// <param name="t_isHighlighted">Whether the button is currently highlighted...Defaulted to false.</param>
	/// <param name="t_color">The color of the button...Defaulted to white.</param>
	Button(const sf::Vector2f &t_pos = sf::Vector2f(0, 0), const sf::Vector2f &t_size = sf::Vector2f(0, 0), const sf::Texture &t_texture = sf::Texture(), const Label &t_label = Label(), const bool t_isHighlighted = false, const sf::Color &t_color = sf::Color::White);

	/// <summary>
	/// Set up all the values of the button.
	/// </summary>
	/// <param name="t_pos">The position the button is to be drawn at...Defaulted to ( 0 , 0 ).</param>
	/// <param name="t_size">The size of the button, width and height...Defaulted to ( 0 , 0 ).</param>
	/// <param name="t_texture">The image of the button...Defaulted to an empty texture object.</param>
	/// <param name="t_label">The label the button will use... Defaulted to an empty Label object.</param>
	/// <param name="t_isHighlighted">Whether the button is currently highlighted...Defaulted to false.</param>
	/// <param name="t_color">The color of the button...Defaulted to white.</param>
	void init(const sf::Vector2f &t_pos = sf::Vector2f(0, 0), const sf::Vector2f &t_size = sf::Vector2f(0, 0), const sf::Texture &t_texture = sf::Texture(), const Label &t_label = Label(), const bool t_isHighlighted = false, const sf::Color &t_color = sf::Color::White);
	/// <summary>
	/// Update the button object.
	/// </summary>
	/// <param name="t_dTime">Time that has passed since the last time the button was updated.</param>
	/// <param name="t_controller">The controller input handler.</param>
	/// <param name="t_animationScalar">The rate at which animations happen.</param>
	void update(const sf::Time t_dTime, const Xbox360Controller &t_controller, const int t_animationScalar);
	/// <summary>
	/// Draw the button object to the render window passed.
	/// </summary>
	/// <param name="t_window">SFML Render Window.</param>
	void render(sf::RenderWindow &t_window);

	//Getter/Setter functions.

	/// <summary>
	/// Return the position the button is being drawn at.
	/// </summary>
	/// <returns>The position of the button.</returns>
	sf::Vector2f position();
	/// <summary>
	/// Set the position the button is to be drawn at.
	/// </summary>
	/// <param name="t_pos">The position the button is to be drawn at.</param>
	void position(const sf::Vector2f &t_pos);
	/// <summary>
	/// Return the color of the button.
	/// </summary>
	/// <returns>The color of the button.</returns>
	sf::Color color();
	/// <summary>
	/// Set the color of the button.
	/// </summary>
	/// <param name="t_color">The color the button is to be drawn as.</param>
	void color(const sf::Color &t_color);
	/// <summary>
	/// Return the size of the button, width and height.
	/// </summary>
	/// <returns>sf::Vector2f containing the widtha nd height of the button.</returns>
	sf::Vector2f size();
	/// <summary>
	/// Set the size of the button.
	/// </summary>
	/// <param name="t_size">sf::Vector2f containing the width and height.</param>
	void size(const sf::Vector2f &t_size);
	/// <summary>
	/// Set the texture of the button.
	/// </summary>
	/// <param name="t_texture">sf::Texture object</param>
	void texture(const sf::Texture &t_texture);
	/// <summary>
	/// Set the label of the button object.
	/// </summary>
	/// <param name="t_label">Label object.</param>
	void label(const Label &t_label);
	/// <summary>
	/// Return the label object in the button.
	/// </summary>
	/// <returns>Label object.</returns>
	Label label();
	/// <summary>
	/// Set whether the button is highlighted.
	/// </summary>
	/// <param name="t_bool">Boolean.</param>
	void highlighted(const bool &t_bool);
	/// <summary>
	/// Return whether the button is highlighted.
	/// </summary>
	/// <returns>Boolean.</returns>
	bool highlighted();
	/// <summary>
	/// Set wether the button has been pressed or not.
	/// </summary>
	/// <param name="t_bool">Boolean.</param>
	void pressed(const bool &t_bool);
	/// <summary>
	/// Return whether the button has been pressed or not.
	/// </summary>
	/// <returns>Boolean.</returns>
	bool pressed();

	void TextureRect(const sf::IntRect & t_rect);

	/// <summary>
	/// Reset the button to default values.
	/// </summary>
	void reset();

	//Body of the button.
	sf::RectangleShape m_body;
private:
	//Label of the button.
	Label m_label;
	//Contains whether the button is highlighted.
	bool m_isHighlighted;
	//Contains whether the button was highlighted last time it was updated.
	bool m_previouslyHighlighted;
	//Used to determine if the highlight animation should be happening.
	bool m_highlightOn;

	//Contains whether the button has been pressed.
	bool m_isPressed;
};


/// <summary>
/// Enum used for the Slider, determines whether the slider is oriented horixontally or vertically.
/// </summary>
enum class BarOrientation
{
	Horizontal,
	Vertical
};

/// <summary>
/// Slider class
/// </summary>
class Slider
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="t_position">Position of the left most/bottom circle.</param>
	/// <param name="t_barLength">The max length of the centre bar.</param>
	/// <param name="t_initialValue">The value the slider is set at originally.</param>
	/// <param name="t_orientation">The orientation of the slider, e.g. Horizontally/Vertically.</param>
	/// <param name="t_highlighted">Whether the is highlighted or not.</param>
	/// <param name="t_color">The color of the slider.</param>
	Slider(const sf::Vector2f &t_position = sf::Vector2f(), const int t_barLength = 100, float t_initialValue = 0.0f, BarOrientation t_orientation = BarOrientation::Horizontal, const bool t_highlighted = false, const sf::Color &t_color = sf::Color::White);

	/// <summary>
	/// Initialise the variables in the slider.
	/// </summary>
	/// <param name="t_position">Position of the left most/bottom circle.</param>
	/// <param name="t_barLength">The max length of the centre bar.</param>
	/// <param name="t_initialValue">The value the slider is set at originally.</param>
	/// <param name="t_orientation">The orientation of the slider, e.g. Horizontally/Vertically.</param>
	/// <param name="t_highlighted">Whether the is highlighted or not.</param>
	/// <param name="t_color">The color of the slider.</param>
	void init(const sf::Vector2f &t_position = sf::Vector2f(), const int t_barLength = 100, float t_initialValue = 0.0f, BarOrientation t_orientation = BarOrientation::Horizontal, const bool t_highlighted = false, const sf::Color &t_color = sf::Color::White);
	/// <summary>
	/// Update the slider, handle any input from the user.
	/// </summary>
	/// <param name="t_dTime">Time since th last time the slider was updated.</param>
	/// <param name="t_controller">Controller input class.</param>
	/// <param name="t_animationScalar">Scalar for the animations.</param>
	void update(const sf::Time t_dTime, const Xbox360Controller & t_controller, const int t_animationScalar);
	/// <summary>
	/// Draw the slider and objects to the render window.
	/// </summary>
	/// <param name="t_window">SFML Render Window.</param>
	void render(sf::RenderWindow &t_window);

	//Getter/Setter functions

	/// <summary>
	/// Returns the position of the left-most/bottom circle.
	/// </summary>
	/// <returns>sf::Vector2f with the position.</returns>
	sf::Vector2f position();
	/// <summary>
	/// Set the position of the slider.
	/// </summary>
	/// <param name="t_pos">sf::vector2f containing the intended location.</param>
	void position(const sf::Vector2f &t_pos);
	/// <summary>
	/// Return the color of thr slider.
	/// </summary>
	/// <returns>sf::color</returns>
	sf::Color color();
	/// <summary>
	/// Set the color of the slider.
	/// </summary>
	/// <param name="t_color">sf::color</param>
	void color(const sf::Color &t_color);
	/// <summary>
	/// Return the max lenght of the centre bar.
	/// </summary>
	/// <returns>float</returns>
	float length();
	/// <summary>
	/// Set the max length of the slider.
	/// </summary>
	/// <param name="t_size">float</param>
	void length(const float &t_size);
	/// /// <summary>
	/// Set whether the slider is highlighted or not.
	/// </summary>
	/// <returns>boolean</returns>
	void highlighted(const bool &t_bool);
	/// <summary>
	/// Return whether the slider is highlighted or not.
	/// </summary>
	/// <param name="t_bool">boolean</param>
	bool highlighted();
	/// <summary>
	/// Set whether the slider has been pressed(If its pressed the value can be changed).
	/// </summary>
	/// <param name="t_bool">boolean</param>
	void pressed(const bool &t_bool);
	/// <summary>
	/// Return whether the slider has been pressed or not.
	/// </summary>
	/// <returns>boolean</returns>
	bool pressed();
	/// <summary>
	/// Returns the value the slider is currently at(float value between 0 and 100).
	/// </summary>
	/// <returns>float</returns>
	float value();
	/// <summary>
	/// Set the value the slider is at(Value can be a float value between 0 and 100)
	/// </summary>
	/// <param name="t_value">float</param>
	void value(const float &t_value);
	/// <summary>
	/// Returns what way the bar is orientated(Horizontal or vertical).
	/// </summary>
	/// <returns>BarOrientation enum.</returns>
	BarOrientation orientation();
	/// <summary>
	/// Set the orientation of the bar.
	/// </summary>
	/// <param name="t_orientation">BarOrientation enum.</param>
	void orientation(const BarOrientation &t_orientation);
	
private:
	//The startpoint/lowest point of the slider.
	sf::CircleShape m_startPoint;
	//The endpoint/highest point of the slider.
	sf::CircleShape m_endPoint;
	//The bar the bar indicator appears to slide along.
	sf::RectangleShape m_centreBar;
	//The bar in the slider that indicates what value it is currently at.
	sf::RectangleShape m_barIndicator; 

	//The length of the slider.
	float m_length;
	//The value of the slider(is between 0 and 100 e.g. is a percentage).
	float m_value;
	//Booleans containing whether the slider is highlighted or not this frame and the previous frame.
	bool m_isHighlighted, m_prevHighlighted;
	//Whether the slider is pressed, if it is, the value can be changed.
	bool m_isPressed;
	//Used to determine if the highlight animation should be happening.
	bool m_highlightOn;

	//The orientation of the slider.
	BarOrientation m_orientation;
};


//Check Box class.
class CheckBox
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	/// <param name="t_pos">The position of the checkbox.</param>
	/// <param name="t_size">The size of the checkbox.</param>
	/// <param name="t_isHighlighted">whether the checkbox is highlighted or not.</param>
	/// <param name="t_color">the color of the checkbox.</param>
	CheckBox(const sf::Vector2f &t_pos = sf::Vector2f(0, 0), const sf::Vector2f &t_size = sf::Vector2f(0, 0), const bool t_isHighlighted = false, const sf::Color &t_color = sf::Color::White);

	/// <summary>
	/// Initialise the checkbox.
	/// </summary>
	/// <param name="t_pos">The position of the checkbox.</param>
	/// <param name="t_size">The size of the checkbox.</param>
	/// <param name="t_isHighlighted">whether the checkbox is highlighted or not.</param>
	/// <param name="t_color">the color of the checkbox.</param>
	void init(const sf::Vector2f &t_pos = sf::Vector2f(0, 0), const sf::Vector2f &t_size = sf::Vector2f(0, 0), const bool t_isHighlighted = false, const sf::Color &t_color = sf::Color::White);
	/// <summary>
	/// Update the check box variables.
	/// </summary>
	/// <param name="t_dTime">Time since the last time the check box was updated.</param>
	/// <param name="t_controller">Controller input class</param>
	/// <param name="t_animationScalar">Scalar for the animations.</param>
	void update(const sf::Time t_dTime, const Xbox360Controller &t_controller, const int t_animationScalar);
	/// <summary>
	/// Draw the check box to the screen.
	/// </summary>
	/// <param name="t_window">SFML Render Window</param>
	void render(sf::RenderWindow &t_window);

	//Getter/Setter methods.

	/// <summary>
	/// Retun the position of the check box
	/// </summary>
	/// <returns>sf::vector2f</returns>
	sf::Vector2f position();
	/// <summary>
	/// set the position of the checkbox
	/// </summary>
	/// <param name="t_pos">sf::vector2f</param>
	void position(const sf::Vector2f &t_pos);
	/// <summary>
	/// Return the color of the check box.
	/// </summary>
	/// <returns>sf::color</returns>
	sf::Color color();
	/// <summary>
	/// Set the color of the check box.
	/// </summary>
	/// <param name="t_color">sf::color</param>
	void color(const sf::Color &t_color);
	/// <summary>
	/// Return the size of the check box.
	/// </summary>
	/// <returns>sf::vector2f</returns>
	sf::Vector2f size();
	/// <summary>
	/// Set the size of the check box.
	/// </summary>
	/// <param name="t_size">sf::vector2f</param>
	void size(const sf::Vector2f &t_size);
	/// <summary>
	/// Set whether the check box is highlighted or not.
	/// </summary>
	/// <param name="t_bool">boolean.</param>
	void highlighted(const bool &t_bool);
	/// <summary>
	/// Return whether th check box is highlighted or not
	/// </summary>
	/// <returns>boolean</returns>
	bool highlighted();
	/// <summary>
	/// Set whether the check box is pressed or not.
	/// </summary>
	/// <param name="t_bool">boolean</param>
	void pressed(const bool &t_bool);
	/// <summary>
	/// Return whether the check box has been oressed or not.
	/// </summary>
	/// <returns>boolean</returns>
	bool pressed();

	/// <summary>
	/// Reset the booleans like a fresh button, un highlighted and unpressed, no animation occurred.
	/// </summary>
	void reset();
private:
	//The body of the Check Box.
	sf::RectangleShape m_body;
	//Used to determine if the highlight animation should be happening.
	bool m_isHighlighted;
	//Booleans containing whether the slider is highlighted or not this frame and the previous frame.
	bool m_previouslyHighlighted, m_highlightOn;

	//Whether the slider is pressed or not.
	bool m_isPressed;
};



//class RadioButton
//{
//public:
//	RadioButton();
//
//	void setPosition(sf::Vector2f t_pos);
//	void pressed();
//	void unPressed();
//	void update();
//	void render(sf::RenderWindow &t_window);
//private:
//	void setUp();
//	bool m_pressed = { false };
//	sf::Texture m_radioButtonTexture;
//	sf::RectangleShape m_radioButton;
//	sf::Texture m_radioButtonFillTexture;
//	sf::RectangleShape m_radioButtonFill;
//};



class Keyboard
{
public:
	Keyboard();

	void setPosition(sf::Vector2f t_pos);
	void update();
	void render(sf::RenderWindow &t_window);
private:
	void setUp();
};

#endif // !UILIBRARY

