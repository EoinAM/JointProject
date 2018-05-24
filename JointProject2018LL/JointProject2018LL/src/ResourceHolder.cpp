#include "..\include\ResourceHolder.h"

/// <summary>
/// default constructor
/// </summary>
/// <param name="t_level">pass the resource holder the gamedata loaded from the yaml</param>
rh::ResourceHolder::ResourceHolder(GameData & t_level)
{
	load(t_level);
}

/// <summary>
/// loads all of the textures specified in the yaml file data
/// </summary>
/// <param name="t_level">data loaded from the yaml</param>
void rh::ResourceHolder::load(GameData & t_level)
{
	try
	{
		//loop through all of the data and load the files given the names and id's
		for (int i = 0; i < t_level.m_holderData.m_textures.size(); i++)
		{
			m_textureHolder.acquire(t_level.m_holderData.m_textures.at(i).m_ID, thor::Resources::fromFile<sf::Texture>(t_level.m_holderData.m_textures.at(i).m_fileName));
		}
		for (int i = 0; i < t_level.m_holderData.m_fonts.size(); i++)
		{
			m_fontHolder.acquire(t_level.m_holderData.m_fonts.at(i).m_ID, thor::Resources::fromFile<sf::Font>(t_level.m_holderData.m_fonts.at(i).m_fileName));
		}
		for (int i = 0; i < t_level.m_holderData.m_shaders.size(); i++)
		{
			if (t_level.m_holderData.m_shaders.at(i).m_type == "Fragment")
			{
				m_shaderHolder.acquire(t_level.m_holderData.m_shaders.at(i).m_ID, thor::Resources::fromFile<sf::Shader>(t_level.m_holderData.m_shaders.at(i).m_fileName, sf::Shader::Fragment));
			}
			if (t_level.m_holderData.m_shaders.at(i).m_type == "Geometry")
			{
				m_shaderHolder.acquire(t_level.m_holderData.m_shaders.at(i).m_ID, thor::Resources::fromFile<sf::Shader>(t_level.m_holderData.m_shaders.at(i).m_fileName, sf::Shader::Geometry));
			}
			if (t_level.m_holderData.m_shaders.at(i).m_type == "Vertex")
			{
				m_shaderHolder.acquire(t_level.m_holderData.m_shaders.at(i).m_ID, thor::Resources::fromFile<sf::Shader>(t_level.m_holderData.m_shaders.at(i).m_fileName, sf::Shader::Vertex));
			}
		}
		for (int i = 0; i < t_level.m_holderData.m_sounds.size(); i++)
		{
			m_soundHolder.acquire(t_level.m_holderData.m_sounds.at(i).m_ID, thor::Resources::fromFile<sf::SoundBuffer>(t_level.m_holderData.m_sounds.at(i).m_fileName));
		}
	}
	catch(thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
