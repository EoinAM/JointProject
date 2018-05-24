#ifndef LEVELLOADER
#define LEVELLOADER

#include "yaml-cpp\yaml.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <SFML\Graphics.hpp>



struct HighScoreData
{
	std::string m_name;
	float m_score;
};

struct ShipData
{
	sf::Vector2f m_size;
	float m_weight;
};


struct AssetsData
{
	std::string m_fileName;
	std::string m_ID;
};

struct ShaderData
{
	std::string m_fileName;
	std::string m_ID;
	std::string m_type;
};

struct HolderData
{
	std::vector<AssetsData> m_textures;
	std::vector<AssetsData> m_fonts;
	std::vector<ShaderData> m_shaders;
	std::vector<AssetsData> m_sounds;
};


struct GroundData
{
	sf::Vector2f m_position;
};

struct MissileData
{
	sf::Vector2f m_position;
};

struct FuelTankData
{
	std::string m_textureID;
	float m_capacity;
	float m_mass;
};

struct LandingGearData
{
	std::string m_textureID;
	float m_breakSpeed;
	float m_mass;
};

struct SideThrusterData
{
	std::string m_textureID;
	sf::Vector2f m_adjustmentMax;
	sf::Vector2f m_size;
	float m_fuelConsumption;
	float m_mass;
};

struct MainThrusterData
{
	std::string m_textureID;
	sf::Vector2f m_size;
	sf::Vector2f m_thrustMax;
	float m_fuelConsumption;
	float m_mass;
};

struct PartData
{
	std::vector<FuelTankData> m_fuelTankData;
	std::vector<LandingGearData> m_landingData;
	std::vector<SideThrusterData> m_sideThrusterData;
	std::vector<MainThrusterData> m_mainThrusterData;
};

struct LevelData
{
	sf::Color m_color;
	std::vector<GroundData> m_groundPoints;
	sf::Vector2f m_cameraPos;
	sf::Vector2f m_startPointPos;
	sf::Vector2f m_endPointPos;
	std::vector<MissileData> m_missilePlatPos;
};

/// <summary>
/// @bried Struct to load level data
/// </summary>
struct GameData 
{
	std::vector<HighScoreData> m_scores;//done
	ShipData m_ship;//done

	HolderData m_holderData;//done
	PartData m_partData;

	LevelData m_level1;
	LevelData m_level2;
};

class LevelLoader
{
private:
	static YAML::Node m_baseNode;
public:
	LevelLoader() = default;

	//load function to be passed a number for a level along 
	//with the level data
	static bool load(int t_nr, GameData & t_level);

	//load function passed the name of the file to be opened
	static bool load(std::string t_fileName,GameData & t_level);

	static void write(std::string t_playerName[], int t_playerScore[]);

	
};


#endif // !LEVELLOADER

