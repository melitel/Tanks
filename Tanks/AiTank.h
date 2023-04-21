#pragma once
#include "Tank.h"
#include "BrainAtk.h"

class AiTank :
    public Tank
{
public:

    AiTank() :
        Tank(10, 1, 60.f, 0) {}

    enum ai_status {
        patrolling,
        defending_base,
        moving_to_enemy_base,
        chasing_enemy_tank

    };

    virtual void update(float dt);
    void get_path(int start_x, int start_y, int goal_x, int goal_y);
    void move_tank(movement_direction direction, float delta) override;
    virtual void initialize(const sf::Vector2f& pos, const std::string& name) override;
    ai_status get_status() const { return m_ai_status; }
    void change_status(ai_status status);

private:

    void move_controller(float delta);
    void processing_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile);
    void change_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile);
    BrainAtk m_ai_brain;
    std::vector<BrainAtk::Node> m_path;
    ai_status m_ai_status;  
    uint32_t m_offset = 16;
    sf::Vector2f m_velocity;
};

