/// @Author Michael Rainsford Ryan

#include "..\include\Game.h"

///////////////////////////////////////////////////////////////////
Game::Game() :
	m_window{ sf::VideoMode{ 800u, 600u, 32u }, "Basic Game" },
	m_exitGame{ false }
{
	setupShapes();
}

///////////////////////////////////////////////////////////////////
Game::~Game()
{

}

///////////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

///////////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}

		else if (sf::Event::KeyPressed == nextEvent.type)
			processKeyPressed(nextEvent);

		else if (sf::Event::MouseButtonPressed == nextEvent.type)
			processMousePressed(nextEvent);
	}
}

///////////////////////////////////////////////////////////////////
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

///////////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear();

	m_window.draw(m_circle);

	m_window.display();
}

///////////////////////////////////////////////////////////////////
void Game::processKeyPressed(sf::Event const& t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
		m_exitGame = true;
}

///////////////////////////////////////////////////////////////////
void Game::processMousePressed(sf::Event const& t_event)
{
	system("cls");

	// Random number of enemy troops between 1 and 30.
	int enemyTroops = rand() % 30 + 1;

	// Random enemy distance between 1 and 70.
	float range = static_cast<float>(rand() % 70 + 1);

	int deploy =
		TroopDeploymentCalculator::getDeploymentAmount(enemyTroops, range);

	std::cout << enemyTroops << " enemy troops spotted at distance of " << range << std::endl;
	std::cout << "Deploying " << deploy << " troops." << std::endl;
}

///////////////////////////////////////////////////////////////////
void Game::setupShapes()
{
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setRadius(30.0f);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setPosition(400.0f, 300.0f);
}

///////////////////////////////////////////////////////////////////