#pragma once
#include "Tank.h"
#include "BrainAtk.h"

class AiTank :
    public Tank
{
public:

    AiTank(const std::string& textureFilename, unsigned int health, unsigned int damage, float move_speed, uint32_t team_id, attack_type tank_attack_type)
        : Tank(textureFilename, health, damage, move_speed, team_id, tank_attack_type) {}

    enum ai_status {
        patrolling,
        defending_base,
        moving_to_enemy_base,
        chasing_enemy_tank
    };

    void update(float dt, int tank_i) override;
    void get_path(int start_x, int start_y, int goal_x, int goal_y, int tank_i);
    void move_tank(movement_direction direction, float delta) override;
    void initialize(const sf::Vector2f& pos) override;
    ai_status get_status() const { return m_ai_status; }
    void change_status(ai_status status);
    bool if_first_bullet_shot() override;
    void first_bullet_shot() override;
    void last_projectile_shot_time(std::chrono::duration<float> time) override;
    std::chrono::duration<float> when_last_projectile_shot() override;

private:

    void move_controller(float delta, int tank_i);
    void processing_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile, int tank_i);
    void change_state(sf::Vector2i ai_tank_tile, sf::Vector2i player_tank_tile, sf::Vector2i player_base_tile, sf::Vector2i ai_base_tile);
    BrainAtk m_ai_brain;
    std::vector<BrainAtk::Node> m_path;
    ai_status m_ai_status;  
    uint32_t m_offset = 16;
    sf::Vector2f m_velocity;
    uint32_t m_goal_def_switch = 1;
    bool m_first_ai_bullet_shot = false;
    std::chrono::duration<float> m_last_ai_projectile_shot{0};
};

