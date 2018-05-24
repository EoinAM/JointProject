#pragma once	
#include "tinyc2.h"
#include <Tinyc2Debug.hpp>

struct ScreenSize
{
	static const unsigned int s_screenWidth{ 1920 };
	static const unsigned int s_screenHeight{ 1080 };
};

enum class GameState
{
	INTRO,
	TRANSITION,
	PLAYING,
	MENU,
	OPTIONS,
	HELP,
	MISSIONSETUP,
	HIGHSCORESCREEN,
	EXIT,
	PAUSE
};