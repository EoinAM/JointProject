#ifndef SETTINGS
#define SETTINGS

#include <SFML\Graphics.hpp>
#include "UiLibrary.h"
#include "Xbox360Controller.h"
#include"Global.h"

/// <summary>
/// SettingsScreen class
/// </summary>
class SettingsScreen
{
public:
	/// <summary>
	/// default constructor, needs to be passed a font
	/// </summary>
	/// <param name="t_font">font used in buttons and labels</param>
	SettingsScreen(sf::Font &t_font);
	/// <summary>
	/// default destructor
	/// </summary>
	~SettingsScreen();
	/// <summary>
	/// update the settings screen data
	/// </summary> 
	/// <param name="t_dTime">the time that has passed since the last update</param>
	/// <param name="t_controller">controller input handler</param>
	void update(sf::Time t_dTime, Xbox360Controller t_controller, GameState & t_gamestate);
	/// <summary>
	/// render all of the elements of the settings screen object
	/// </summary>
	/// <param name="t_window">render window</param>
	void render(sf::RenderWindow &t_window);

private:
	//private memeber variables
	//ui elements
	Slider m_sliderMusic;
	Slider m_sliderSFX;
	CheckBox m_checkBox;
	Label m_label[3];//the labels of the settings screen
	sf::String m_labelText[3] = { "Music", "SFX", "Mute" };//the text to be used in the labels
	int m_currentButton = 0;//the 0 button is the default first button to be highlighted
};
#endif
