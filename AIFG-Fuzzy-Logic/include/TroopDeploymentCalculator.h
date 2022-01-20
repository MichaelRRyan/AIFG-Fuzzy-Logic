#ifndef TROOP_DEPLOYMENT_CALCULATOR_H
#define TROOP_DEPLOYMENT_CALCULATOR_H

#include "Fuzzy.h"

class TroopDeploymentCalculator
{
public:

	static int getDeploymentAmount(int t_enemyTroops, float t_enemyDistance);

};

#endif // !TROOP_DEPLOYMENT_CALCULATOR_H
