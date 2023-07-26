#include "PowerUp.h"
#include "Tank.h"


void PowerUp::boost_speed(float speed_boost)
{
	tank_to_boost->modify_speed(speed_boost);
}

void PowerUp::add_hp(unsigned int life_boost)
{
	tank_to_boost->modify_life(life_boost);
}
