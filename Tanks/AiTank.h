#pragma once
#include "Tank.h"
#include "BrainAtk.h"

class AiTank :
    public Tank
{
public:

    AiTank() :
        Tank(10, 1, 15.f) {}

    void update(float dt);
    void get_path(int start_x, int start_y, int goal_x, int goal_y);
    void move_tank(const sf::Vector2f& velocity, float delta) override;

private:

    BrainAtk m_ai_brain;

    enum ai_status {
        patrolling,
        defending_base,
        moving_to_enemy_base,
        attacking_enemy_base,
        attacking_enemy_tank
    
    };

    std::vector<BrainAtk::Node> m_path;
    ai_status m_ai_status;  
    uint32_t m_offset = 16;
};

