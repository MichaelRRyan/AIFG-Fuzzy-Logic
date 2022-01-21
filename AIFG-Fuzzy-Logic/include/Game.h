#ifndef GAME
#define GAME

/// @Author Michael Rainsford Ryan

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TroopDeploymentCalculator.h"

/// <summary>
/// The game's main class. Keeps the game running at 60
/// frames per second and holds all ground level game objects.
/// </summary>
class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void processKeyPressed(sf::Event const& t_event);
	void processMousePressed(sf::Event const & t_event);

	void randomiseForce();
	void drawForce(int t_enemyTroops, int t_deployment);

	void setupVisuals();

	sf::RenderWindow m_window;
	bool m_exitGame;

	sf::Vector2f m_worldSize;

	sf::Texture m_spriteSheet;
	sf::Sprite m_objectSprite;

	sf::RenderTexture m_charactersTexture;
	sf::Sprite m_charactersSprite;

};

#endif // !GAME

