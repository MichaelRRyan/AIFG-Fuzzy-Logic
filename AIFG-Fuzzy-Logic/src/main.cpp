/// Game Title
/// @Author
/// @Date

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

#include <iostream>
#include "Game.h"
#include "TroopDeploymentCalculator.h"

int main()
{
	//Game game;
	//game.run();

	int enemyTroops = 8;
	float range = 25.0f;

	int deploy = 
		TroopDeploymentCalculator::getDeploymentAmount(enemyTroops, range);

	std::cout << enemyTroops << " enemy troops spotted at distance of " << range << std::endl;
	std::cout << "Deploying " << deploy << " troops." << std::endl;
	
	system("pause");

	return EXIT_SUCCESS;
}
