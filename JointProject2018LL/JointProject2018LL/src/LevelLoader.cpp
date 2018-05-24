#include "LevelLoader.h"

YAML::Node LevelLoader::m_baseNode; // Defines the static variable

/// <summary>
/// Operator to Load High Scores
/// </summary>
/// <param name="t_scoreDataNode">NOde containgin high score data</param>
/// <param name="t_score"> high score object</param>
void operator >> (const YAML::Node & t_scoreDataNode, HighScoreData & t_score)
{
	t_score.m_name = t_scoreDataNode["name"].as<std::string>();
	t_score.m_score = t_scoreDataNode["score"].as<int>();
}

/// <summary>
/// Operator to load Ship Data
/// </summary>
/// <param name="t_shipDataNode">Node within the Yaml File</param>
/// <param name="t_ship">Ship Object</param>
void operator >> (const YAML::Node & t_shipDataNode, ShipData & t_ship)
{
	t_ship.m_size = sf::Vector2f(t_shipDataNode["size"]["x"].as<float>(), t_shipDataNode["size"]["y"].as<float>());
	t_ship.m_weight = t_shipDataNode["weight"].as<float>();
}


void operator >> (const YAML::Node & t_assetDataNode, AssetsData & t_asset)
{
	t_asset.m_fileName = t_assetDataNode["file"].as<std::string>();
	t_asset.m_ID = t_assetDataNode["name"].as<std::string>();
}

void operator >> (const YAML::Node & t_shaderDataNode, ShaderData & t_shader)
{
	t_shader.m_fileName = t_shaderDataNode["file"].as<std::string>();
	t_shader.m_ID = t_shaderDataNode["name"].as<std::string>();
	t_shader.m_type = t_shaderDataNode["type"].as<std::string>();
}


void operator >> (const YAML::Node & t_holderDataNode, HolderData & t_holder)
{
	const YAML::Node& texturesNode = t_holderDataNode["Textures"].as<YAML::Node>();
	for (unsigned i = 0; i < texturesNode.size(); i++)
	{
		AssetsData textures;
		texturesNode[i] >> textures;
		t_holder.m_textures.push_back(textures);
	}
	const YAML::Node& fontsNode = t_holderDataNode["Fonts"].as<YAML::Node>();
	for (unsigned i = 0; i < fontsNode.size(); i++)
	{
		AssetsData fonts;
		fontsNode[i] >> fonts;
		t_holder.m_fonts.push_back(fonts);
	}
	const YAML::Node& shadersNode = t_holderDataNode["Shaders"].as<YAML::Node>();
	for (unsigned i = 0; i < shadersNode.size(); i++)
	{
		ShaderData shaders;
		shadersNode[i] >> shaders;
		t_holder.m_shaders.push_back(shaders);
	}
	const YAML::Node& soundsNode = t_holderDataNode["Sounds"].as<YAML::Node>();
	for (unsigned i = 0; i < soundsNode.size(); i++)
	{
		AssetsData sounds;
		soundsNode[i] >> sounds;
		t_holder.m_sounds.push_back(sounds);
	}
}

void operator >> (const YAML::Node & t_fuelTankNode, FuelTankData & t_fuelData)
{
	t_fuelData.m_textureID = t_fuelTankNode["textureID"].as<std::string>();
	t_fuelData.m_capacity = t_fuelTankNode["capacity"].as<float>();
	t_fuelData.m_mass = t_fuelTankNode["mass"].as<float>();
}

void operator >> (const YAML::Node & t_landerNode, LandingGearData & t_landerData)
{
	t_landerData.m_textureID = t_landerNode["textureID"].as<std::string>();
	t_landerData.m_breakSpeed = t_landerNode["breakSpeed"].as<float>();
	t_landerData.m_mass = t_landerNode["mass"].as<float>();
}

void operator >> (const YAML::Node & t_mainThrusterNode, MainThrusterData & t_mainThrusterData)
{
	t_mainThrusterData.m_textureID = t_mainThrusterNode["textureID"].as<std::string>();
	t_mainThrusterData.m_size = sf::Vector2f(t_mainThrusterNode["size"]["x"].as<float>(), t_mainThrusterNode["size"]["y"].as<float>());
	t_mainThrusterData.m_mass = t_mainThrusterNode["mass"].as<float>();
	t_mainThrusterData.m_fuelConsumption = t_mainThrusterNode["fuelConsumption"].as<float>();
	t_mainThrusterData.m_thrustMax = sf::Vector2f(t_mainThrusterNode["thrust"]["x"].as<float>(), t_mainThrusterNode["thrust"]["y"].as<float>());
}

void operator >> (const YAML::Node & t_sideThrusterNode, SideThrusterData & t_sideThrusterData)
{
	t_sideThrusterData.m_textureID = t_sideThrusterNode["textureID"].as<std::string>();
	t_sideThrusterData.m_size = sf::Vector2f(t_sideThrusterNode["size"]["x"].as<float>(), t_sideThrusterNode["size"]["y"].as<float>());
	t_sideThrusterData.m_mass = t_sideThrusterNode["mass"].as<float>();
	t_sideThrusterData.m_fuelConsumption = t_sideThrusterNode["fuelConsumption"].as<float>();
	t_sideThrusterData.m_adjustmentMax = sf::Vector2f(t_sideThrusterNode["adjustment"]["x"].as<float>(), t_sideThrusterNode["adjustment"]["y"].as<float>());
}

void operator >> (const YAML::Node & t_partDataNode, PartData & t_part)
{
	const YAML::Node& fuelTankNode = t_partDataNode["FuelTank"].as<YAML::Node>();
	for (unsigned i = 0; i < fuelTankNode.size(); i++)
	{
		FuelTankData fuelData;
		fuelTankNode[i] >> fuelData;
		t_part.m_fuelTankData.push_back(fuelData);
	}
	const YAML::Node& landingGearNode = t_partDataNode["LandingGear"].as<YAML::Node>();
	for (unsigned i = 0; i < landingGearNode.size(); i++)
	{
		LandingGearData landingData;
		landingGearNode[i] >> landingData;
		t_part.m_landingData.push_back(landingData);
	}
	const YAML::Node& mainThrustersNode = t_partDataNode["MainThruster"].as<YAML::Node>();
	for (unsigned i = 0; i < mainThrustersNode.size(); i++)
	{
		MainThrusterData mainThrusterData;
		mainThrustersNode[i] >> mainThrusterData;
		t_part.m_mainThrusterData.push_back(mainThrusterData);
	}
	const YAML::Node& sideThrustersNode = t_partDataNode["SideThruster"].as<YAML::Node>();
	for (unsigned i = 0; i < sideThrustersNode.size(); i++)
	{
		SideThrusterData sideThrusterData;
		sideThrustersNode[i] >> sideThrusterData;
		t_part.m_sideThrusterData.push_back(sideThrusterData);
	}
}

void operator >> (const YAML::Node & t_groundDataNode, GroundData & t_ground)
{
	t_ground.m_position = sf::Vector2f(t_groundDataNode["position"]["x"].as<float>(), t_groundDataNode["position"]["y"].as<float>());
}

void operator >> (const YAML::Node & t_missileDataNode, MissileData & t_missile)
{
	t_missile.m_position = sf::Vector2f(t_missileDataNode["position"]["x"].as<float>(), t_missileDataNode["position"]["y"].as<float>());
}


void operator >> (const YAML::Node & t_levelDataNode, LevelData & t_level)
{
	t_level.m_color = sf::Color(t_levelDataNode["Color"]["r"].as<float>(), t_levelDataNode["Color"]["g"].as<float>(), t_levelDataNode["Color"]["b"].as<float>(), t_levelDataNode["Color"]["a"].as<float>());
	t_level.m_cameraPos = sf::Vector2f(t_levelDataNode["Camera"]["position"]["x"].as<float>(), t_levelDataNode["Camera"]["position"]["y"].as<float>());
	t_level.m_startPointPos = sf::Vector2f(t_levelDataNode["StartPoint"]["position"]["x"].as<float>(), t_levelDataNode["StartPoint"]["position"]["y"].as<float>());
	t_level.m_endPointPos = sf::Vector2f(t_levelDataNode["TargetPoint"]["position"]["x"].as<float>(), t_levelDataNode["TargetPoint"]["position"]["y"].as<float>());
	
	const YAML::Node& groundNode = t_levelDataNode["Ground"].as<YAML::Node>();
	for (unsigned i = 0; i < groundNode.size(); i++)
	{
		GroundData groundPoints;
		groundNode[i] >> groundPoints;
		t_level.m_groundPoints.push_back(groundPoints);
	}

	const YAML::Node& missileNode = t_levelDataNode["MissilePlatform"].as<YAML::Node>();
	for (unsigned i = 0; i < missileNode.size(); i++)
	{
		MissileData tempMissile;
		missileNode[i] >> tempMissile;
		t_level.m_missilePlatPos.push_back(tempMissile);
	}
}

void operator >> (const YAML::Node & t_levelNode, GameData & t_level)
{
	//make a new node pointing at the base nodes highscores node
	const YAML::Node& scoresNode = t_levelNode["Highscores"].as<YAML::Node>();

	//loop through all of the nodes in the scoresNode and load all of the data
	for (unsigned i = 0; i < scoresNode.size(); ++i)
	{
		HighScoreData scores;
		scoresNode[i] >> scores;
		t_level.m_scores.push_back(scores);
	}

	t_levelNode["Ship"] >> t_level.m_ship;

	t_levelNode["Assets"] >> t_level.m_holderData;
	t_levelNode["Level1"] >> t_level.m_level1;
	t_levelNode["Level2"] >> t_level.m_level2;
	t_levelNode["ShipParts"] >> t_level.m_partData;
}

bool LevelLoader::load(int t_nr, GameData & t_level)
{
	std::stringstream ss;
	ss << "RESOURCES//YAML//";
	ss << t_nr;
	ss << ".yaml";

	try
	{
		m_baseNode = YAML::LoadFile(ss.str());
		if (m_baseNode.IsNull())
		{
			std::string msg("No file found :" + ss.str());
			throw std::exception(msg.c_str());	
		}
		m_baseNode >> t_level;
	}
	catch (YAML::ParserException & e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

bool LevelLoader::load(std::string t_fileName, GameData & t_level)
{
	std::stringstream ss;
	ss << t_fileName;

	try
	{
		m_baseNode = YAML::LoadFile(ss.str());
		if (m_baseNode.IsNull())
		{
			std::string msg("No file found :" + ss.str());
			throw std::exception(msg.c_str());
		}
		m_baseNode >> t_level;
	}
	catch (YAML::ParserException & e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

//Will be changed to take a string so we can change what we want and will take a node name
//this is just the write doesnt do anything ,will be changed by Alecx when highscores are being done
void LevelLoader::write(std::string t_playerName[], int t_playerScore[])
{
	 YAML::Node& scoresNode = m_baseNode["Highscores"].as<YAML::Node>();
	for (int i = 0; i < 10; i++)
	{
		scoresNode[i]["name"] = t_playerName[i];
		scoresNode[i]["score"] = t_playerScore[i];
	}

	//m_baseNode["Highscores"]["name"] = "Jim";// edit one of the nodes 
	std::string file = ".\\ASSETS\\YAML\\GameData.yaml";
	std::ofstream fout(file); // This is the path to the YAML file
	fout << m_baseNode; // dump it back into the file
	fout.close();
}
