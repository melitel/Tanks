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

private:

	const uint32_t m_base_width = 48;
	const uint32_t m_base_height = 56;
	sf::RectangleShape m_base;
	sf::Texture m_base_texture;
	unsigned int m_base_health;
	unsigned int m_base_damage;

};

