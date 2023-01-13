#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tank
{
public:
	void update(float dt);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void initialize(const sf::Vector2f& pos, const std::string& name);
	void move_tank(const sf::Vector2f& velocity, float delta);
	void rotate_tank(sf::Angle angle);

protected:
	const uint32_t m_tank_width = 32;
	const uint32_t m_tank_height = 32;
	sf::RectangleShape m_tank;
	sf::Texture m_tank_texture;
	unsigned int m_health = 0;
	unsigned int m_damage = 0;
	float m_move_speed = 15.0;
	float m_projectile_speed = 0.0;
	unsigned int m_texture_id;
	sf::Vector2f m_direction{0.0f, 0.0f};
	enum projectile_type {
		one_bullet,
		tripple_bullet,
		firing_bullet,
		freezing_bullet
	};

};

