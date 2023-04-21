#include "Tank.h"
#include "Game.h"

extern Game* g_Game;

void Tank::update(float dt)
{
}

void Tank::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_tank);	

}

void Tank::initialize(const sf::Vector2f& pos, const std::string& name)
{
	m_tank.setOrigin(sf::Vector2f(m_tank_height/2, m_tank_width/2));
	m_tank.setPosition(pos);
	m_tank.setSize(sf::Vector2f((float)m_tank_width, (float)m_tank_height));
	if (!m_tank_texture.loadFromFile(name))
	{
		m_tank.setFillColor(sf::Color::Red);
	}
	else {
		m_tank.setTexture(&m_tank_texture);
	}
}

void Tank::move_tank(movement_direction direction, float delta) {

	switch (direction) {
	case up:
		m_direction = sf::Vector2f(0.f, -1.f);
		rotate_tank(sf::degrees(0.f));
		break;
	case left:
		m_direction = sf::Vector2f(-1.f, 0.f);
		rotate_tank(sf::degrees(-90.f));
		break;
	case right:
		m_direction = sf::Vector2f(1.f, 0.f);
		rotate_tank(sf::degrees(90.f));
		break;
	case down:
		m_direction = sf::Vector2f(0.f, 1.f);
		rotate_tank(sf::degrees(180.f));
		break;
	case stop:
		m_direction = sf::Vector2f(0.f, 0.f);		
		break;
	default:
		// handle invalid status value
		m_direction = sf::Vector2f(0.f, 0.f);
		break;
	}
			
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f vel = m_direction * m_move_speed;
	sf::Vector2f p1 = p0 + (delta * vel);
	sf::Vector2f mtd = g_Game->separating_axis(g_Game->m_ai_tank, g_Game->m_player_tank, p1);
	p1 = p1 + mtd;

	g_Game->calibrate_pos(p1);

	m_tank.setPosition(p1);
	//std::cout << p1.x << ";" << p1.y << std::endl;
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



Tank& Tank::operator=(Tank& other)
{
	m_tank = other.m_tank;
	m_health = other.m_health;
	return *this;
}

Tank::Tank(const Tank& other)
{
	m_tank = other.m_tank;
	m_health = other.m_health;
}

Tank& Tank::operator=(Tank&& other) noexcept
{
	std::swap(m_tank, other.m_tank);
	std::swap(m_health, other.m_health);
	return *this;
}

Tank::Tank(Tank&& other) noexcept
{
	std::swap(m_tank, other.m_tank);
	std::swap(m_health, other.m_health);
}
