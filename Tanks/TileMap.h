#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int tiles[19][27], unsigned int width, unsigned int height);

private:

	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	
};

