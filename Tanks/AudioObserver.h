#pragma once
#include "Observer.h"

class AudioObserver :
    public Observer
{
public:

    void onTankHit(Tank* tank) override;
};

