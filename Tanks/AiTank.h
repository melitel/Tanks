#pragma once
#include "Tank.h"


class AiTank :
    public Tank
{
public:

    AiTank() :
        Tank(10, 1, 15.f) {}

    void update(float dt);

private:

    enum ai_status {
        patrolling,
        defending_base,
        moving_to_enemy_base,
        attacking_enemy_base,
        attacking_enemy_tank
    
    };

    ai_status m_ai_status;    
};

