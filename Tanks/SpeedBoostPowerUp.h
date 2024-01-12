#pragma once
#include "PowerUp.h"


class SpeedBoostPowerUp :
    public PowerUp
{
public:

    void activate(Tank* tank) override;
    
};

