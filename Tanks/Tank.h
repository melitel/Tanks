#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tank
{
public:

	enum movement_direction
	{
		up,
		left,
		right,
		down,
		stop
	};

	enum attack_type
	{
		attack,
		defence		
	};

	Tank(
		unsigned int health,
		unsigned int damage,
		float move_speed,
		uint32_t team_id,
		attack_type tank_attack_type
	) :
		m_health(health),
		m_damage(damage),
		m_move_speed(move_speed),
		m_team_id(team_id),
		m_tank_attack_type(tank_attack_type)
	{}

	Tank& operator=(Tank&& other) noexcept;
	Tank(Tank&& other) noexcept;
	virtual ~Tank() = default;

	virtual void update(float dt, int tank_i);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	virtual void initialize(const sf::Vector2f& pos, const std::string& name);
	virtual void move_tank(movement_direction direction, float delta);
	void rotate_tank(sf::Angle angle);
	const sf::Vector2f get_position() const;
	void set_position(sf::Vector2f pos);
	const sf::FloatRect get_tank_bounds() const;
	const sf::Angle getRotation() const;
	const sf::Vector2f& get_direction() const;
	const sf::Vector2f get_size() const;
	const sf::RectangleShape get_shape() const;
	const uint32_t get_team_id() const;
	attack_type m_tank_attack_type;

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
	uint32_t m_team_id;
	sf::Vector2f m_direction{0.0f, 0.0f};

};

