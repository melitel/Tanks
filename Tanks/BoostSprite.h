#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class BoostSprite
{
public:

	BoostSprite(
		const std::string& textureFilename,
		uint32_t boost_id,
		sf::Vector2f pos
		): 
		m_boostTexture(&TextureManager::GetTexture(textureFilename)),
		m_boost_id(boost_id),
		m_boost_position(pos)
		
	{
		m_boost.setTexture(m_boostTexture);	
		m_boost.setPosition(m_boost_position);
		m_boost.setSize(sf::Vector2f(32, 32));
	}
		
	void draw(std::unique_ptr<sf::RenderWindow>& window);
	sf::FloatRect get_bounds();
	const uint32_t get_boost_id() const { return m_boost_id; }

private:

	sf::Texture* m_boostTexture;
	sf::RectangleShape m_boost;
	uint32_t m_boost_id;
	sf::Vector2f m_boost_position;

};

