#ifndef HEATSEAKER
#define HEATSEAKER

#include "Global.h"
#include "SFML\Graphics.hpp"

class HeatSeaker
{
	friend class HeatSeakerPool;
public:
	HeatSeaker(){ m_body.setSize(sf::Vector2f(10, 10)); m_body.setFillColor(sf::Color::Magenta); }

	void init(sf::Texture const & t_texture, float t_x, float t_y);
	bool update(sf::Time const &t_dTime, sf::Vector2f t_target);

	bool inUse() const;

	void setRotation(double t_angle);

	sf::RectangleShape getBody() { return m_body; }
	sf::Vector2f getPosition() { return m_position; }
	sf::Vector2f m_target{};

private:
	sf::Texture m_texture;

	bool onScreenCheck();

	static constexpr double M_MAX_SPEED{ 0.5f };

	double m_speed{ 0.0 };

	sf::Sprite m_missile;

	sf::IntRect m_bulletRect{};

	sf::Vector2f m_position;

	sf::RectangleShape m_body;
	sf::Vector2f m_direction;
	float m_hypotenuse{ 0 };
};


#endif // !HEATSEAKER
