#include "TileMap.h"


bool TileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int tiles[19][27], unsigned int width, unsigned int height)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset))
		return false;

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Triangles);
	m_vertices.resize(width * height * 6);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = tiles[j][i];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			// get a pointer to the current tile's two succeeding triangles
			sf::Vertex* triangle = &m_vertices[(i + j * width) * 6];

			// define the 3 corners of the first triangle
			triangle[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			triangle[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			triangle[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

			// define the 3 corners of the second triangle
			triangle[3].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			triangle[4].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
			triangle[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

			// define 3 texture coordinates for first triangle
			triangle[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			triangle[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			triangle[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);

			// define 3 texture coordinates for second triangle
			triangle[3].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			triangle[4].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
			triangle[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		}

	return true;
}

void TileMap::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates rs = states;

	// apply the transform
	rs.transform *= getTransform();

	// apply the tileset texture
	rs.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, rs);
}
