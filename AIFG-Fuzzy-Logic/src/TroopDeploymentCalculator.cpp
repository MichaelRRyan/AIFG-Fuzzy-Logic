#include "TroopDeploymentCalculator.h"

int TroopDeploymentCalculator::getDeploymentAmount(int t_enemyTroops, float t_enemyDistance)
{
	float troops = static_cast<float>(t_enemyTroops);

	// Fuzzy force size subsets:
	float sizeTiny = fuzzy::triangle(troops, -10.0f, 0.0f, 10.0f);
	float sizeSmall = fuzzy::trapezoid(troops, 2.5f, 10.0f, 15.0f, 20.0f);
	float sizeModerate = fuzzy::trapezoid(troops, 15.0f, 20.0f, 25.0f, 30.0f);
	float sizeLarge = fuzzy::grade(troops, 25.0f, 30.0f);

	// Fuzzy force distance subsets:
	float distanceClose = fuzzy::triangle(t_enemyDistance, -30.0f, 0.0f, 30.0f);
	float distanceMedium = fuzzy::trapezoid(t_enemyDistance, 10.0f, 30.0f, 50.0f, 70.0f);
	float distanceFar = fuzzy::grade(t_enemyDistance, 50.0f, 70.0f);

	// Apply the fuzzy rules.
	float threatLow =
		fuzzy::OR(fuzzy::OR(fuzzy::AND(distanceMedium, sizeTiny),
			fuzzy::AND(distanceMedium, sizeSmall)),
			fuzzy::AND(distanceFar, fuzzy::NOT(sizeLarge)));

	float threatMedium =
		fuzzy::OR(fuzzy::OR(fuzzy::AND(distanceClose, sizeTiny),
			fuzzy::AND(distanceMedium, sizeModerate)),
			fuzzy::AND(distanceFar, sizeLarge));

	float threatHigh =
		fuzzy::OR(fuzzy::AND(distanceClose, fuzzy::NOT(sizeTiny)),
			fuzzy::AND(distanceMedium, sizeLarge));

	float deploy =
		round((threatLow * 10.0f + threatMedium * 30 + threatHigh * 50) /
			(threatLow + threatMedium + threatHigh));

    return static_cast<int>(deploy);
}
