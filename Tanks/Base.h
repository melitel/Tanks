#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Base
{
public:

	void initialize(const sf::Vector2f& pos, const std::string& name);
	void update(float dt);
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	void rotate_base(sf::Angle angle);
	sf::Vector2f get_position();
	sf::FloatRect get_bounds();

	Base(
		unsigned int health,
		unsigned int damage,
		uint32_t team_id
	) :
		m_base_health(health),
		m_base_damage(damage),
		m_team_id(team_id)
	{}

private:

	const uint32_t m_base_width = 48;
	const uint32_t m_base_height = 56;
	sf::RectangleShape m_base;
	sf::Texture m_base_texture;
	unsigned int m_base_health;
	unsigned int m_base_damage;
	uint32_t m_team_id;

};

