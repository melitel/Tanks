#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tank;

class Projectile
{
public:

	void initialize(const sf::Vector2f& pos);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void update(float delta);
	void move_projectile(float delta);
	float distance_update(float delta);
	float get_projectile_distance();
	sf::FloatRect get_projectile_bounds();
	uint32_t get_owner_team_id();
	const sf::Vector2f get_position() const;

	Projectile(Tank* owner);

	~Projectile()
	{
		
	}
	
	Projectile& operator=(Projectile&& other) noexcept;
	Projectile(Projectile&& other);
	
private:

	Projectile& operator=(Projectile& other);
	Projectile(const Projectile& other);

	enum projectile_type {
		one_bullet,
		tripple_bullet,
		firing_bullet,
		freezing_bullet
	};

	Tank* m_owner;
	const float m_projectile_size = 3.f;
	sf::CircleShape m_projectile{ m_projectile_size };
	float m_projectile_speed = 75.f;
	projectile_type m_projectile_type;
	float m_projectile_distance = 64;
	sf::Vector2f m_direction;

};

