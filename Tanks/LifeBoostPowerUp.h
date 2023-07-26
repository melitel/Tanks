#pragma once
#include "PowerUp.h"

class LifeBoostPowerUp :
    public PowerUp
{
public:
    void activate(Tank* tank) override;
};

