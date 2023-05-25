#include "Tank.h"
#include "Game.h"

extern Game* g_Game;

std::unordered_map<std::string, sf::Texture> TextureManager::m_textures;

void Tank::update(float dt, int tank_i)
{
}

void Tank::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_tank);	

}

void Tank::initialize(const sf::Vector2f& pos)
{
	m_tank.setOrigin(sf::Vector2f(float(m_tank_height/2), float (m_tank_width/2)));
	m_tank.setPosition(pos);
	m_tank.setSize(sf::Vector2f((float)m_tank_width, (float)m_tank_height));
}

void Tank::move_tank(movement_direction direction, float delta) {

}

void Tank::rotate_tank(sf::Angle angle)
{	
	m_tank.setRotation(angle);	
}

const sf::Vector2f Tank::get_position() const
{
	return m_tank.getPosition();
}

void Tank::set_position(sf::Vector2f pos)
{
	m_tank.setPosition(pos);
}

const sf::FloatRect Tank::get_tank_bounds() const
{
	return m_tank.getGlobalBounds();
}

const sf::Angle Tank::getRotation() const
{
	return m_tank.getRotation();
}

const sf::Vector2f& Tank::get_direction() const
{
	return m_direction;
}

const sf::Vector2f Tank::get_size() const
{
	sf::Vector2f tank_size = m_tank.getSize();
	return tank_size;
}

const sf::RectangleShape Tank::get_shape() const
{
	sf::RectangleShape tank_shape = m_tank;
	return tank_shape;
}

const uint32_t Tank::get_team_id() const
{
	return m_team_id;
}

bool Tank::if_first_bullet_shot()
{
	return false;
}

void Tank::first_bullet_shot()
{
}

void Tank::last_projectile_shot_time(std::chrono::duration<float> time)
{
}

std::chrono::duration<float> Tank::when_last_projectile_shot()
{
	return m_last_projectile_shot_time;
}

Tank& Tank::operator=(Tank& other)
{
	m_tank = other.m_tank;
	m_health = other.m_health;
	m_damage = other.m_damage;
	m_move_speed = other.m_move_speed;
	m_team_id = other.m_team_id;
	m_tank_attack_type = other.m_tank_attack_type;
	m_tankTexture = other.m_tankTexture;
	return *this;
}

Tank::Tank(const Tank& other)
{
	m_tank = other.m_tank;
	m_health = other.m_health;
	m_damage = other.m_damage;
	m_move_speed = other.m_move_speed;
	m_team_id = other.m_team_id;
	m_tank_attack_type = other.m_tank_attack_type;	
	m_tankTexture = other.m_tankTexture;
}

Tank& Tank::operator=(Tank&& other) noexcept
{
	std::swap(m_tank, other.m_tank);
	std::swap(m_health, other.m_health);
	std::swap(m_damage, other.m_damage);
	std::swap(m_move_speed, other.m_move_speed);
	std::swap(m_team_id, other.m_team_id);
	std::swap(m_tank_attack_type, other.m_tank_attack_type);
	std::swap(m_tankTexture, other.m_tankTexture);
	return *this;
}

Tank::Tank(Tank&& other) noexcept
{
	std::swap(m_tank, other.m_tank);
	std::swap(m_health, other.m_health);
	std::swap(m_damage, other.m_damage);
	std::swap(m_move_speed, other.m_move_speed);
	std::swap(m_team_id, other.m_team_id);
	std::swap(m_tank_attack_type, other.m_tank_attack_type);
	std::swap(m_tankTexture, other.m_tankTexture);
}
