#include "Projectile.h"
#include "Tank.h"
#include <algorithm>

void Projectile::initialize(const sf::Vector2f& pos)
{
	m_projectile.setScale(sf::Vector2f(0.f, 0.f));
	m_projectile.setPosition(sf::Vector2f(pos.x - 3, pos.y - 16));
	m_projectile.setFillColor(sf::Color::Red);
	m_projectile_distance = 64;

}

void Projectile::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	auto pp = m_projectile.getPosition();
	window->draw(m_projectile);

}

void Projectile::update(const sf::Vector2f& velocity, float delta)
{	
	m_projectile.setScale(sf::Vector2f(1.f, 1.f));
	sf::Vector2f p0 = m_projectile.getPosition();
	sf::Vector2f vel = velocity * m_projectile_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_projectile.setPosition(p1);
}

float Projectile::distance_update(const sf::Vector2f& velocity, float delta)
{
	sf::Vector2f vel = velocity * m_projectile_speed;
	m_projectile_distance -= delta * vel.length();
	return m_projectile_distance;
}

sf::FloatRect Projectile::get_projectile_bounds()
{
	return m_projectile.getGlobalBounds();
	
}

Projectile::Projectile(Tank* owner)
	:
	m_owner(owner)
{
	initialize(m_owner->get_position());

}

Projectile& Projectile::operator=(Projectile &other)
{
	m_owner = other.m_owner;
	m_projectile = other.m_projectile;
	return *this;
}

Projectile::Projectile(const Projectile& other)
{
	m_owner = other.m_owner;
	m_projectile = other.m_projectile;
}

Projectile& Projectile::operator=(Projectile&& other) noexcept
{
	std::swap(m_owner, other.m_owner);
	std::swap(m_projectile, other.m_projectile);
	std::swap(m_projectile_distance, other.m_projectile_distance);
	return *this;
}

Projectile::Projectile(Projectile&& other)
{
	std::swap(m_owner, other.m_owner);
	std::swap(m_projectile, other.m_projectile);
	std::swap(m_projectile_distance, other.m_projectile_distance);
}



