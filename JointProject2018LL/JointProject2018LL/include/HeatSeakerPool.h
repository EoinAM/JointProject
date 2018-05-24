#ifndef HEATSEAKERPOOL
#define HEATSEAKERPOOL

#include "SFML\Graphics.hpp"
#include <array>
#include "HeatSeaker.h"

class HeatSeakerPool
{
public:
	HeatSeakerPool() = default;

	//makes a new projectile, sets the position of the projectile
	void create(sf::Texture const & t_texture, double t_x, double t_y);

	void update(sf::Time const &t_dTime, sf::Vector2f t_target);

	void render(sf::RenderWindow &t_window);

	void setRotation(double t_angle);

	c2Poly m_collisisionPoly;
private:
	static const int M_POOL_SIZE =  4;
	std::array < HeatSeaker , M_POOL_SIZE > m_heatSeakers;

	sf::Vector2f m_missilePos[M_POOL_SIZE];
	sf::RectangleShape m_body[M_POOL_SIZE];
	int m_nextAvailable{ 0 };

	bool m_poolFull{ false };

};

#endif // !HEATSEAKERPOOL
