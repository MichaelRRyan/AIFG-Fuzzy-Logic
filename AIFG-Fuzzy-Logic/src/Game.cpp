/// @Author Michael Rainsford Ryan

#include "..\include\Game.h"

////////////////////////////////////////////////////////////////////////////////
Game::Game() :
	m_window{ sf::VideoMode::getDesktopMode(), "Basic Game", sf::Style::Fullscreen },
	m_exitGame{ false }
{
	// Sets the width and height of the view to have the same view size 
	//		regardless of resolution.
	sf::View view = m_window.getDefaultView();
	float aspectRatio = view.getSize().y / view.getSize().x;
	float pixelWidth = 1920.0f;
	m_worldSize = { pixelWidth, aspectRatio * pixelWidth };
	sf::View newView{ m_worldSize * 0.5f, m_worldSize };
	m_window.setView(newView);

	// Sets up the render texture.
	m_charactersTexture.create(static_cast<unsigned>(m_worldSize.x),
							   static_cast<unsigned>(m_worldSize.y));

	m_charactersTexture.setView(newView);
	m_charactersSprite.setTexture(m_charactersTexture.getTexture());

	setupVisuals();
	randomiseForce();
}

////////////////////////////////////////////////////////////////////////////////
Game::~Game()
{

}

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

////////////////////////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear();

	m_window.draw(m_charactersSprite);

	m_window.display();
}

////////////////////////////////////////////////////////////////////////////////
void Game::processKeyPressed(sf::Event const& t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
		m_exitGame = true;
}

////////////////////////////////////////////////////////////////////////////////
void Game::processMousePressed(sf::Event const& t_event)
{
	randomiseForce();
}

////////////////////////////////////////////////////////////////////////////////
void Game::randomiseForce()
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

	drawForce(enemyTroops, deploy);
}

////////////////////////////////////////////////////////////////////////////////
void Game::drawForce(int t_enemyTroops, int t_deployment)
{
	int rowSize = 10;

	// Draws the aliens.
	m_charactersTexture.clear(sf::Color::Transparent);
	m_objectSprite.setTextureRect({ 0, 0, 96, 96 });

	sf::Vector2f basePos{ 32.0f, 32.0f };

	for (int i = 0; i < t_enemyTroops; ++i)
	{
		m_objectSprite.setPosition(basePos.x + 96.0f * (i % rowSize), 
								   basePos.y + 96.0f * (i / rowSize));

		m_objectSprite.move(static_cast<float>(rand() % 20 - 10),
							static_cast<float>(rand() % 20 - 10));

		m_charactersTexture.draw(m_objectSprite);
	}

	// Draws the humans.
	basePos = { m_worldSize.x - 118.0f, m_worldSize.y - 118.0f };

	for (int i = 0; i < t_deployment; ++i)
	{
		m_objectSprite.setTextureRect({ 96 + 96 * (rand() % 2), 0, 96, 96 });

		m_objectSprite.setPosition(basePos.x - 96.0f * (i % rowSize),
								   basePos.y - 96.0f * (i / rowSize));

		m_objectSprite.move(static_cast<float>(rand() % 20 - 10),
							static_cast<float>(rand() % 20 - 10));

		m_charactersTexture.draw(m_objectSprite);
	}

	m_charactersTexture.display();
}

////////////////////////////////////////////////////////////////////////////////
void Game::setupVisuals()
{
	if (!m_spriteSheet.loadFromFile("assets/images/sprite_sheet.png"))
		std::cout << "Error loading sprite sheet." << std::endl;
	else
		m_objectSprite.setTexture(m_spriteSheet);
}

////////////////////////////////////////////////////////////////////////////////