#pragma once
#include "Tank.h"

class AiTank :
    public Tank
{
public:

    AiTank() :
        Tank(10, 1, 15.f) {}
};

