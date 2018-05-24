#ifndef COLLISION_DETECTOR
#define COLLISION_DETECTOR

#include <SFML/Graphics.hpp>
#include <iostream>


namespace cd
{
	/// <summary>
	/// returns a bool of wether the two rects passed have collided(entered each other)
	/// </summary>
	/// <param name="t_rect1">rectangle shape 1</param>
	/// <param name="t_rect2">rectangle shape 2</param>
	/// <returns>wether the rectangles have collided</returns>
	static bool rectToRect(sf::RectangleShape t_rect1, sf::RectangleShape t_rect2)
	{
		//if the rectangles are drawing from the top left
		if (t_rect1.getOrigin() == sf::Vector2f(0,0) && t_rect2.getOrigin() == sf::Vector2f(0,0))
		{
			//if they collide
			return(t_rect1.getPosition().x < t_rect2.getPosition().x + t_rect2.getLocalBounds().width &&
				t_rect1.getPosition().x + t_rect1.getLocalBounds().width > t_rect2.getPosition().x &&
				t_rect1.getPosition().y < t_rect2.getPosition().y + t_rect2.getLocalBounds().height &&
				t_rect1.getPosition().y + t_rect1.getLocalBounds().height > t_rect2.getPosition().y);
		}
		//if an origin has been set for the rectangles
		else
		{
			//remember the old values for the origin
			float rec1X, rec1Y, rec2X, rec2Y;


			rec1X = t_rect1.getOrigin().x;
			rec1Y = t_rect1.getOrigin().y;
			rec2X = t_rect2.getOrigin().x;
			rec2Y = t_rect2.getOrigin().y;

			//reset te origins to draw from the top left
			t_rect1.setOrigin(0, 0);
			t_rect2.setOrigin(0, 0);

			//recursive call to this function to get wether they collide
			bool answer = rectToRect(t_rect1, t_rect2);

			//reset the origins to the values passed
			t_rect1.setOrigin(rec1X, rec1Y);
			t_rect2.setOrigin(rec2X, rec2Y);

			//return the recursive answer
			return answer;
		}
	}

	/// <summary>
	/// returns a bool of whether the two sprites have collided(entered each other)
	/// </summary>
	/// <param name="t_sprite1">first sprite</param>
	/// <param name="t_sprite2">second sprite</param>
	/// <returns>whether the two sprites passed have collided with each other</returns>
	static bool spriteToSprite(sf::Sprite t_sprite1, sf::Sprite t_sprite2)
	{
		//if the sprites are drawing from the top left
		if (t_sprite1.getOrigin() == sf::Vector2f(0, 0) && t_sprite2.getOrigin() == sf::Vector2f(0, 0))
		{
			//if they collide
			return(t_sprite1.getPosition().x < t_sprite2.getPosition().x + t_sprite2.getLocalBounds().width &&
				t_sprite1.getPosition().x + t_sprite1.getLocalBounds().width > t_sprite2.getPosition().x &&
				t_sprite1.getPosition().y < t_sprite2.getPosition().y + t_sprite2.getLocalBounds().height &&
				t_sprite1.getPosition().y + t_sprite1.getLocalBounds().height > t_sprite2.getPosition().y);
		}
		//if an origin has been set for the sprites
		else
		{
			//remember the old values passed to the function
			int sprite1X, sprite1Y, sprite2X, sprite2Y;

			sprite1X = t_sprite1.getOrigin().x;
			sprite1Y = t_sprite1.getOrigin().y;
			sprite2X = t_sprite2.getOrigin().x;
			sprite2Y = t_sprite2.getOrigin().y;

			//reset the origin to the top left
			t_sprite1.setOrigin(0, 0);
			t_sprite2.setOrigin(0, 0);

			//recursive call to the function to get wether they collide
			bool answer = spriteToSprite(t_sprite1, t_sprite2);

			//reset the origin to the old values
			t_sprite1.setOrigin(sprite1X, sprite1Y);
			t_sprite2.setOrigin(sprite2X, sprite2Y);

			//return the recursive answer
			return answer;
		}
	}

	/// <summary>
	/// returns a bool wether the rectangle shape and the sprite passed collide(enter each other)
	/// </summary>
	/// <param name="t_rect">rectangle shape passed</param>
	/// <param name="t_sprite">sprite object passsed</param>
	/// <returns>wether the two objects passed collide</returns>
	static bool rectToSprite(sf::RectangleShape t_rect, sf::Sprite t_sprite)
	{
		//if the objects are drawing from the top left
		if (t_rect.getOrigin() == sf::Vector2f(0, 0) && t_sprite.getOrigin() == sf::Vector2f(0, 0))
		{
			//if they collide
			return(t_rect.getPosition().x < t_sprite.getPosition().x + t_sprite.getLocalBounds().width &&
				t_rect.getPosition().x + t_rect.getLocalBounds().width > t_sprite.getPosition().x &&
				t_rect.getPosition().y < t_sprite.getPosition().y + t_sprite.getLocalBounds().height &&
				t_rect.getPosition().y + t_rect.getLocalBounds().height > t_sprite.getPosition().y);
		}
		//if an origin has been set for either object
		else
		{
			//remember the old values passed to the function
			int rectX, rectY, spriteX, spriteY;

			rectX = t_rect.getOrigin().x;
			rectY = t_rect.getOrigin().y;
			spriteX = t_sprite.getOrigin().x;
			spriteY = t_sprite.getOrigin().y;

			//reset the origin to the top left
			t_rect.setOrigin(0, 0);
			t_sprite.setOrigin(0, 0);

			//recursive call to get wether the two objects collide
			bool answer = rectToSprite(t_rect, t_sprite);

			//reset the origin to the values passed
			t_rect.setOrigin(rectX, rectY);
			t_sprite.setOrigin(spriteX, spriteY);

			//return the recursive answer
			return answer;
		}
	}

	/// <summary>
	/// overloaded function to check wether a rectangle shape or a sprite object collide
	/// </summary>
	/// <param name="t_sprite">sprite object</param>
	/// <param name="t_rect">rectangle shape passed</param>
	/// <returns>wether the rectangle shape and the sprite object collide</returns>
	static bool rectToSprite(sf::Sprite t_sprite, sf::RectangleShape t_rect)
	{
		//call the other function, return that answer
		return rectToSprite(t_rect, t_sprite);
	}

	/// <summary>
	/// circle to circle collision
	/// </summary>
	/// <param name="t_circ1">first circle passed</param>
	/// <param name="t_circ2">second circle passed</param>
	/// <returns>wether the circle collide</returns>
	static bool circleToCircle(sf::CircleShape t_circ1, sf::CircleShape t_circ2)
	{
		//if the circles are drawn from their centres
		if (t_circ1.getOrigin() == sf::Vector2f(t_circ1.getRadius(), t_circ1.getRadius()) && t_circ2.getOrigin() == sf::Vector2f(t_circ2.getRadius(), t_circ2.getRadius()))
		{
			//vector between the centres
			sf::Vector2f vectorBetween = t_circ1.getPosition() - t_circ2.getPosition();
			//length of the vector between their centres
			double length = sqrt(abs(vectorBetween.x * vectorBetween.x + vectorBetween.y * vectorBetween.y));
			//if the length is smaller than the sum of their squares they have collided
			if (length < t_circ1.getRadius() + t_circ2.getRadius())
			{
				return true;
			}
			//otherwise they havent collided
			else
			{
				return false;
			}
		}
		//if they arent drawn from their centres
		else
		{
			//remember the old origin values passed to the function
			int circ1X, circ1Y, circ2X, circ2Y;

			circ1X = t_circ1.getOrigin().x;
			circ1Y = t_circ1.getOrigin().y;
			circ2X = t_circ2.getOrigin().x;
			circ2Y = t_circ2.getOrigin().y;

			//reset the origins to the centres of the respective circle
			t_circ1.setOrigin(t_circ1.getRadius(), t_circ1.getRadius());
			t_circ2.setOrigin(t_circ2.getRadius(), t_circ2.getRadius());

			//recursive call to this function to get the answer
			bool answer = circleToCircle(t_circ1, t_circ2);

			//reset the origins to the values passed
			t_circ1.setOrigin(circ1X, circ1Y);
			t_circ2.setOrigin(circ2X, circ2Y);

			//return eh recursive answer
			return answer;
		}
	}

	/// <summary>
	/// circle to sprite collision
	/// </summary>
	/// <param name="t_circ">circle shape</param>
	/// <param name="t_sprite">sprite object</param>
	/// <returns>wether the circle and the sprite collide</returns>
	static bool circleToSprite(sf::CircleShape t_circ, sf::Sprite t_sprite)
	{
		//if both objects are being drawn from their centres
		if (t_sprite.getOrigin() == sf::Vector2f(t_sprite.getLocalBounds().width / 2.f, t_sprite.getLocalBounds().height / 2.f) && t_circ.getOrigin() == sf::Vector2f(t_circ.getRadius(), t_circ.getRadius()))
		{
			//get the distance between the centres
			sf::Vector2f circleDistance{};
			circleDistance.x = abs(t_circ.getPosition().x - t_sprite.getPosition().x);
			circleDistance.y = abs(t_circ.getPosition().y - t_sprite.getPosition().y);

			//if the circle is too far away return false
			if (circleDistance.x > (t_sprite.getLocalBounds().width / 2 + t_circ.getRadius()))
			{
				return false;
			}
			if (circleDistance.y > (t_sprite.getLocalBounds().height / 2 + t_circ.getRadius()))
			{
				return false;
			}

			//if the centre of the circle centre is less than the width of the sprite away it has collided
			if (circleDistance.x <= (t_sprite.getLocalBounds().width / 2))
			{
				return true;
			}
			if (circleDistance.y <= (t_sprite.getLocalBounds().height / 2))
			{
				return true;
			}


			//check if the circle collides with the corners of the square
			double cornerDistance = (circleDistance.x - t_sprite.getLocalBounds().width / 2) * (circleDistance.x - t_sprite.getLocalBounds().width / 2) +
				(circleDistance.y - t_sprite.getLocalBounds().height / 2) * (circleDistance.y - t_sprite.getLocalBounds().height / 2);

			return (cornerDistance <= (t_circ.getRadius() * t_circ.getRadius()));
		}
		//if either objct isnt drawn from their centre
		else
		{
			//remember the origin values passed to the function
			int circY, circX, rectX, rectY;

			circX = t_circ.getOrigin().x;
			circY = t_circ.getOrigin().y;
			rectX = t_sprite.getOrigin().x;
			rectY = t_sprite.getOrigin().y;

			//set the origins to the centres of the objects
			t_circ.setOrigin(t_circ.getRadius(), t_circ.getRadius());
			t_sprite.setOrigin(t_sprite.getLocalBounds().width / 2.f, t_sprite.getLocalBounds().height / 2.f);

			//recursive call to return the answer
			bool answer = circleToSprite(t_circ, t_sprite);

			//reset the origins to the values passed to the function
			t_circ.setOrigin(circY, circX);
			t_sprite.setOrigin(rectX, rectY);

			//return the answer
			return answer;
		}
	}

	/// <summary>
	/// overloaded function for circle to sprite collision
	/// </summary>
	/// <param name="t_sprite">sprite object</param>
	/// <param name="t_circ">circle shape</param>
	/// <returns>wether they have collided</returns>
	static bool circleToSprite(sf::Sprite t_sprite, sf::CircleShape t_circ)
	{
		//call the other function
		return circleToSprite(t_circ, t_sprite);
	}

	/// <summary>
	/// circle to rectangle collision
	/// </summary>
	/// <param name="t_circ">circle shape</param>
	/// <param name="t_rect">rectangle shape</param>
	/// <returns>wether they have collided</returns>
	static bool circleToRect(sf::CircleShape t_circ, sf::RectangleShape t_rect)
	{
		//if the objects are drawn from their centres
		if (t_rect.getOrigin() == sf::Vector2f(t_rect.getLocalBounds().width / 2.f, t_rect.getLocalBounds().height / 2.f) && t_circ.getOrigin() == sf::Vector2f(t_circ.getRadius(), t_circ.getRadius()))
		{
			//calculate the distance between the centres
			sf::Vector2f circleDistance{};
			circleDistance.x = abs(t_circ.getPosition().x - t_rect.getPosition().x);
			circleDistance.y = abs(t_circ.getPosition().y - t_rect.getPosition().y);

			//if the circle is too far away it doesnt collide
			if (circleDistance.x > (t_rect.getSize().x / 2 + t_circ.getRadius())) 
			{ 
				return false; 
			}
			if (circleDistance.y > (t_rect.getSize().y / 2 + t_circ.getRadius())) 
			{ 
				return false; 
			}

			//if the distance between the centres is less than the width of the rectangle it has collided
			if (circleDistance.x <= (t_rect.getSize().x / 2)) 
			{ 
				return true; 
			}
			if (circleDistance.y <= (t_rect.getSize().y / 2)) 
			{ 
				return true; 
			}


			//check if the circle collides with the corners of the square
			double cornerDistance = (circleDistance.x - t_rect.getSize().x / 2) * (circleDistance.x - t_rect.getSize().x / 2) +
				(circleDistance.y - t_rect.getSize().y / 2) * (circleDistance.y - t_rect.getSize().y / 2);

			return (cornerDistance <= (t_circ.getRadius() * t_circ.getRadius()));
		}
		//if either object isnt drawn from thier centre
		else
		{
			//remember the oigin values passed to the function
			int circY, circX, rectX, rectY;

			circX = t_circ.getOrigin().x;
			circY = t_circ.getOrigin().y;
			rectX = t_rect.getOrigin().x;
			rectY = t_rect.getOrigin().y;

			//set the origin to the centre
			t_circ.setOrigin(t_circ.getRadius(), t_circ.getRadius());
			t_rect.setOrigin(t_rect.getLocalBounds().width / 2.f, t_rect.getLocalBounds().height / 2.f);

			//recursive call to find the answer
			bool answer = circleToRect(t_circ, t_rect);

			//reset the origin to the origin values passed to the functions
			t_circ.setOrigin(circY, circX);
			t_rect.setOrigin(rectX, rectY);

			//return the recursive answer
			return answer;
		}
	}

	/// <summary>
	/// overloaded circle rectangle collision
	/// </summary>
	/// <param name="t_rect">rectangle shape</param>
	/// <param name="t_circ">circle shape</param>
	/// <returns>wether they collide</returns>
	static bool circleToRect(sf::RectangleShape t_rect, sf::CircleShape t_circ)
	{
		//call the other function
		return circleToRect(t_circ, t_rect);
	}
}
#endif