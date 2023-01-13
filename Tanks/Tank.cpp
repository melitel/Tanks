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

void Tank::move_tank(const sf::Vector2f & velocity, float delta) {
			
	sf::Vector2f p0 = m_tank.getPosition();
	sf::Vector2f vel = velocity * m_move_speed;
	sf::Vector2f p1 = p0 + delta * vel;

	g_Game->calibrate_pos(p1);

	m_tank.setPosition(p1);
	//std::cout << p1.x << ";" << p1.y << std::endl;
}



void Tank::rotate_tank(sf::Angle angle)
{	
	m_tank.setRotation(angle);	
}
