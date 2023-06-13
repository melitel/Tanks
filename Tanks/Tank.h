#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Observer.h"

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
		const std::string& textureFilename,
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
	{
		// Load the texture from the resource manager
		m_tankTexture = &TextureManager::GetTexture(textureFilename);
		m_tank.setTexture(m_tankTexture);
	}

	Tank& operator=(Tank&& other) noexcept;
	Tank(Tank&& other) noexcept;
	virtual ~Tank() = default;
	
	virtual void update(float dt, int tank_i);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	virtual void initialize(const sf::Vector2f& pos);
	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void hitByBullet();
	virtual void move_tank(movement_direction direction, float delta);
	void rotate_tank(sf::Angle angle);
	const uint32_t get_tank_offset() { return m_tank_offset; }
	const sf::Vector2f get_position() const;
	void set_position(sf::Vector2f pos);
	const sf::FloatRect get_tank_bounds() const;
	const sf::Angle getRotation() const;
	const sf::Vector2f& get_direction() const;
	const sf::Vector2f get_size() const;
	const sf::RectangleShape get_shape() const;
	const uint32_t get_team_id() const;
	void kill_count();
	const uint32_t get_kill_count() const;
	virtual bool if_first_bullet_shot();
	virtual void first_bullet_shot();
	virtual void last_projectile_shot_time(std::chrono::duration<float> time);
	virtual std::chrono::duration<float> when_last_projectile_shot();

	attack_type m_tank_attack_type;

protected:	

	std::vector<Observer*> observers;
	Tank& operator=(Tank& other);
	Tank(const Tank& other);
	const uint32_t m_tank_width = 32;
	const uint32_t m_tank_height = 32;
	const uint32_t m_tank_offset = 16;
	sf::Texture* m_tankTexture;
	sf::RectangleShape m_tank;
	unsigned int m_health;
	unsigned int m_damage;
	float m_move_speed;
	uint32_t m_team_id;
	uint32_t m_kills_count = 0;
	sf::Vector2f m_direction{0.0f, 0.0f};
	std::chrono::duration<float> m_last_projectile_shot_time{0};

};

