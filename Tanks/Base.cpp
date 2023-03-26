#include "Base.h"

void Base::initialize(const sf::Vector2f& pos, const std::string& name)
{
	m_base.setOrigin(sf::Vector2f(m_base_height / 2, m_base_width / 2));
	m_base.setPosition(pos);
	m_base.setSize(sf::Vector2f((float)m_base_width, (float)m_base_height));
	if (!m_base_texture.loadFromFile(name))
	{
		m_base.setFillColor(sf::Color::Red);
	}
	else {
		m_base.setTexture(&m_base_texture);
	}

}

void Base::update(float dt)
{
}

void Base::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_base);
}

void Base::rotate_base(sf::Angle angle)
{
	m_base.setRotation(angle);
}

sf::Vector2f Base::get_position()
{
	return m_base.getPosition();
}

sf::FloatRect Base::get_bounds()
{	
	return m_base.getGlobalBounds();
}
