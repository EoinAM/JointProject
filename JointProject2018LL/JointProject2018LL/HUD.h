#ifndef HUDisplay
#define HUDisplay

#include <SFML\Graphics.hpp>
#include "Xbox360Controller.h"
#include "ResourceHolder.h"

class HUD
{
public:
	HUD(sf::Font &t_font, rh::ResourceHolder & t_resourceHolder);
	~HUD();

	void update(Xbox360Controller t_controller, float t_fuel, float t_horizontalSpeed, float t_verticalSpeed, int t_score);
	void render(sf::RenderWindow &t_window);

private:
	sf::Text m_HUDText[4];
	sf::RectangleShape m_fuelRectangle;
	sf::RectangleShape m_HUDRectangle[2];
	sf::Texture m_HUDTexture;
	rh::ResourceHolder & m_resourceHolder;
};

#endif
