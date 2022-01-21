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
	void drawForce(int t_enemyTroops, int t_deployment, float t_distance);

	void setupVisuals();

	sf::Color const m_BACKGROUND_COLOR;
	int const m_CHARACTER_SIZE;
	int const m_ROCK_SIZE;
	float const m_SPRITE_SCALE;

	sf::RenderWindow m_window;
	bool m_exitGame;

	sf::Vector2f m_worldSize;

	sf::Texture m_spriteSheet;
	sf::Sprite m_objectSprite;

	sf::RenderTexture m_renderTexture;
	sf::Sprite m_renderTextureSprite;

	sf::Font m_arial;
	sf::Text m_infoText;

};

#endif // !GAME

