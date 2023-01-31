#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tank;

class Projectile
{
public:

	void initialize(const sf::Vector2f& pos);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void update(const sf::Vector2f& velocity, float delta);
	float distance_update(const sf::Vector2f& velocity, float delta);
	sf::FloatRect get_projectile_bounds();

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
	float m_projectile_speed = 15.f;
	projectile_type m_projectile_type;
	float m_projectile_distance = 64;

};

