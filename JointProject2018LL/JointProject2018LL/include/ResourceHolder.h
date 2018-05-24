#ifndef RESOURCE_LOADER
#define RESOURCE_LOADER

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Thor\Resources.hpp"
#include "LevelLoader.h"

//namespace for our resourceHolder class
namespace rh
{
	//resource holder class
	class ResourceHolder
	{
	public:
		/// <summary>
		/// default constructor
		/// </summary>
		/// <param name="t_level">pass the resource holder the gamedata loaded from the yaml</param>
		ResourceHolder(GameData & t_level);

		/// <summary>
		/// a holder for texture objects
		/// </summary>
		thor::ResourceHolder<sf::Texture, std::string> m_textureHolder;
		/// <summary>
		/// a holder for font objects
		/// </summary>
		thor::ResourceHolder<sf::Font, std::string> m_fontHolder;
		/// <summary>
		/// a holder for shader objects
		/// </summary>
		thor::ResourceHolder<sf::Shader, std::string> m_shaderHolder;

		thor::ResourceHolder<sf::SoundBuffer, std::string> m_soundHolder;
	private:
		/// <summary>
		/// loads all of the textures specified in the yaml file data
		/// </summary>
		/// <param name="t_level">data loaded from the yaml</param>
		void load(GameData & t_level);
	};
}

#endif