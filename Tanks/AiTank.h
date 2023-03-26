#pragma once
#include "Tank.h"
#include "BrainAtk.h"

class AiTank :
    public Tank
{
public:

    AiTank() :
        Tank(10, 1, 55.f, 0) {}

    enum ai_status {
        patrolling,
        defending_base,
        moving_to_enemy_base,
        attacking,
        chasing_enemy_tank

    };

    virtual void update(float dt);
    void get_path(int start_x, int start_y, int goal_x, int goal_y);
    void move_tank(movement_direction direction, float delta) override;
    virtual void initialize(const sf::Vector2f& pos, const std::string& name) override;
    ai_status get_status() const { return m_ai_status; }
    void change_status(ai_status status);

private:

    BrainAtk m_ai_brain;
    std::vector<BrainAtk::Node> m_path;
    ai_status m_ai_status;  
    uint32_t m_offset = 16;
};

