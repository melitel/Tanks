#pragma once
#include "Observer.h"


class KillCountObserver :
    public Observer
{
public:

    void onTankHit(Tank* tank) override;

};

