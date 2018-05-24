#define TINYC2_IMPL
#define TINYC2_IMPLEMENTATION

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#pragma comment(lib,"libyaml-cppmdd") 


#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>true</returns>
int main()
{
	//load all of the game data from the yaml file
	GameData data;
	LevelLoader::load(".\\ASSETS\\YAML\\GameData.yaml", data);

	//try catch statement to catch errors if the game isnt loaded correctly
	try
	{
		//constructor of game clalled to load all of the data
		Game game(data);
		//run the game loop
		game.run();
	}
	//if there is a problem the exception will be caught here
	catch (std::exception e)
	{
		std::system("pause");
		//if there is a problem the function will return 0
		return 0;
	}
	//if everything goes well the function will return 1

	return 1;

	
} 