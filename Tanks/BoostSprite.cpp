#include "BoostSprite.h"


void BoostSprite::draw(std::unique_ptr<sf::RenderWindow>& window)
{
	window->draw(m_boost);
}

sf::FloatRect BoostSprite::get_bounds()
{
	return m_boost.getGlobalBounds();
}
