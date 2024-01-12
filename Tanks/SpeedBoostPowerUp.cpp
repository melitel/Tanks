#include "SpeedBoostPowerUp.h"
#include "Tank.h"

void SpeedBoostPowerUp::activate(Tank* tank)
{
    tank->modify_speed(10.f);
}
