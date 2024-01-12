#pragma once
#include "Observer.h"

class AnimationObserver :
    public Observer
{
public:

    void onTankHit(Tank* tank) override;
};

