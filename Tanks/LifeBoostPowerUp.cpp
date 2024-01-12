#include "LifeBoostPowerUp.h"
#include "Tank.h"

void LifeBoostPowerUp::activate(Tank* tank)
{
	tank->modify_life(1);
}
