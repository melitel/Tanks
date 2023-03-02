#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tank
{
public:

	virtual void update(float dt) = 0;
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void initialize(const sf::Vector2f& pos, const std::string& name);
	virtual void move_tank(const sf::Vector2f& velocity, float delta);
	void rotate_tank(sf::Angle angle);
	sf::Vector2f get_position();
	sf::FloatRect get_tank_bounds();

	Tank(
		unsigned int health,
		unsigned int damage,
		float move_speed
	) :
		m_health(health),
		m_damage(damage),
		m_move_speed(move_speed)
	{}

	Tank& operator=(Tank&& other) noexcept;
	Tank(Tank&& other) noexcept;

protected:

	Tank& operator=(Tank& other);
	Tank(const Tank& other);
	const uint32_t m_tank_width = 32;
	const uint32_t m_tank_height = 32;
	sf::RectangleShape m_tank;
	sf::Texture m_tank_texture;
	unsigned int m_health;
	unsigned int m_damage;
	float m_move_speed;
	sf::Vector2f m_direction{0.0f, 0.0f};

};

