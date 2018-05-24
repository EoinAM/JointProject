# include "Highscores.h"

HighscoreScreen::HighscoreScreen(GameData & t_level, sf::Font &t_font) :
	m_level(t_level), 
	m_font(t_font)
{
	m_title.init("HIGHSCORES", sf::Vector2f(960, 40), m_font, 100, sf::Color::Red);
		for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		m_playerName[i] = (m_level.m_scores.at(i).m_name);
		m_highscore[i] = (m_level.m_scores.at(i).m_score);
		m_level.m_scores.push_back(m_level.m_scores.at(i));
	}

	for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		m_highscoreLabel[i].init(m_playerName[i] + " : " + std::to_string(m_highscore[i]), sf::Vector2f(960, 200 + (i * 50)), m_font, 24, sf::Color::Red);
	}
}

HighscoreScreen::~HighscoreScreen()
{

}


//only call update in the game over screen.
void HighscoreScreen::update()
{
	//Sorts out highscores and places them in order of highest to lowest
	float temp = 0;
	std::string nameTemp = "";
	for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		for (int j = i + 1; j < M_MAX_STORED_SCORES; j++)
		{
			if (m_highscore[j] > m_highscore[i])
			{
				temp = m_highscore[i];
				nameTemp = m_playerName[i];
				m_highscore[i] = m_highscore[j];
				m_playerName[i] = m_playerName[j];
				m_highscore[j] = temp;
				m_playerName[j] = nameTemp;
			}
		}
	}
	//rewrites highscore table
	LevelLoader::write(m_playerName, m_highscore);
}

void HighscoreScreen::render(sf::RenderWindow & t_window)
{
	for (int i = 0; i < M_MAX_STORED_SCORES; i++)
	{
		m_highscoreLabel[i].render(t_window);
	}
	m_title.render(t_window);
}

//find the lowest score and replaces it with the new name and score then calls the updatw which puts the scores in order and rewrites the file.
void HighscoreScreen::newScore(float t_newScore, std::string t_newName)
{
	int lowest = m_highscore[0];
	int lowestIndex = 0;
	for (int i = 1; i < M_MAX_STORED_SCORES; i++)
	{
		if (m_highscore[i] < lowest)
		{
			lowest = m_highscore[i];
			lowestIndex = i;
		}
	}
	m_highscore[lowestIndex] = t_newScore;
	m_playerName[lowestIndex] = t_newName;

	update();
}

void HighscoreScreen::buttonPress(Xbox360Controller t_controller, GameState & t_gamestate)
{
	if (t_controller.m_currentState.Back)
	{
		t_gamestate = GameState::MENU;
	}
}
