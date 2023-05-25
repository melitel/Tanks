#pragma once
#include "Tank.h"

class ControllableTank : public Tank
{	
public:

	ControllableTank() :
		Tank("commontankup.png", 10, 1, 50.f, 1, attack) {}

	void initialize(const sf::Vector2f& pos) override;
	void update(float dt, int tank_i) override;
	void move_controller(float delta);
	void move_tank(movement_direction direction, float delta) override;
	bool if_first_bullet_shot() override;
	void first_bullet_shot() override;
	void last_projectile_shot_time(std::chrono::duration<float> time) override;
	std::chrono::duration<float> when_last_projectile_shot() override;

private:

	bool m_first_bullet_shot = false;
	std::chrono::duration<float> m_last_projectile_shot{0};
};

