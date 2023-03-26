#include "Projectile.h"
#include "Tank.h"
#include <algorithm>

void Projectile::initialize(const sf::Vector2f& pos)
{
	m_projectile.setScale(sf::Vector2f(0.f, 0.f));
	int owner_team_id = get_owner_team_id();	
	
	if (owner_team_id == 0) {
		sf::Angle ai_direction = m_owner->getRotation();

		if (ai_direction == sf::degrees(0.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x - 3, pos.y + 16));
			m_direction = sf::Vector2f(0.f, 1.f);
		}
		if (ai_direction == sf::degrees(270.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x + 16, pos.y - 3));
			m_direction = sf::Vector2f(1.f, 0.f);
		}
		if (ai_direction == sf::degrees(90.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x - 16, pos.y - 3));
			m_direction = sf::Vector2f(-1.f, 0.f);
		}
		if (ai_direction == sf::degrees(180.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x - 3, pos.y - 16));
			m_direction = sf::Vector2f(0.f, -1.f);
		}
	}
	if (owner_team_id == 1) {

		sf::Angle player_direction = m_owner->getRotation();

		if (player_direction == sf::degrees(0.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x - 3, pos.y - 16));
			m_direction = sf::Vector2f(0.f, -1.f);
		}
		if (player_direction == sf::degrees(270.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x - 16, pos.y - 3));
			m_direction = sf::Vector2f(-1.f, 0.f);
		}
		if (player_direction == sf::degrees(90.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x + 16, pos.y - 3));
			m_direction = sf::Vector2f(1.f, 0.f);
		}
		if (player_direction == sf::degrees(180.f)) {
			m_projectile.setPosition(sf::Vector2f(pos.x - 3, pos.y + 16));
			m_direction = sf::Vector2f(0.f, 1.f);
		}		
	}
	m_projectile.setFillColor(sf::Color::Red);
	m_projectile_distance = 64;

}

void Projectile::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	auto pp = m_projectile.getPosition();
	window->draw(m_projectile);

}

void Projectile::update(float delta)
{	
	m_projectile.setScale(sf::Vector2f(1.f, 1.f));
	sf::Vector2f p0 = m_projectile.getPosition();
	sf::Vector2f vel = m_direction * m_projectile_speed;
	sf::Vector2f p1 = p0 + delta * vel;
	m_projectile.setPosition(p1);
}

float Projectile::distance_update(float delta)
{
	sf::Vector2f vel = m_direction * m_projectile_speed;
	m_projectile_distance -= delta * vel.length();
	return m_projectile_distance;
}

sf::FloatRect Projectile::get_projectile_bounds()
{
	return m_projectile.getGlobalBounds();
	
}

uint32_t Projectile::get_owner_team_id()
{
	return m_owner->get_team_id();
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
	std::swap(m_direction, other.m_direction);
	return *this;
}

Projectile::Projectile(Projectile&& other)
{
	std::swap(m_owner, other.m_owner);
	std::swap(m_projectile, other.m_projectile);
	std::swap(m_projectile_distance, other.m_projectile_distance);
	std::swap(m_direction, other.m_direction);
}



