#include "TileMap.h"
#include "GrassTile.h"
#include "WaterTile.h"
#include "BushTile.h"
#include "BrickTile.h"


bool TileMap::load(const std::string& tileset)
{
	// load the tileset texture
	if (!m_tileset.loadFromFile(tileset))
		return false;	

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Triangles);
	m_vertices.resize(m_width * m_height * 6);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < m_width; ++i)
		for (unsigned int j = 0; j < m_height; ++j)
		{
			// get the current tile number			
			int tileID = m_tiles_map[j][i]->get_id();

			// find its position in the tileset texture
			int tu = tileID % (m_tileset.getSize().x / m_tile_size.x);
			int tv = tileID / (m_tileset.getSize().x / m_tile_size.x);

			// get a pointer to the current tile's two succeeding triangles
			sf::Vertex* triangle = &m_vertices[(i + j * m_width) * 6];

			// define the 3 corners of the first triangle
			triangle[0].position = sf::Vector2f(i * m_tile_size.x, j * m_tile_size.y);
			triangle[1].position = sf::Vector2f((i + 1) * m_tile_size.x, j * m_tile_size.y);
			triangle[2].position = sf::Vector2f((i + 1) * m_tile_size.x, (j + 1) * m_tile_size.y);

			// define the 3 corners of the second triangle
			triangle[3].position = sf::Vector2f(i * m_tile_size.x, j * m_tile_size.y);
			triangle[4].position = sf::Vector2f(i * m_tile_size.x, (j + 1) * m_tile_size.y);
			triangle[5].position = sf::Vector2f((i + 1) * m_tile_size.x, (j + 1) * m_tile_size.y);

			// define 3 texture coordinates for first triangle
			triangle[0].texCoords = sf::Vector2f(tu * m_tile_size.x, tv * m_tile_size.y);
			triangle[1].texCoords = sf::Vector2f((tu + 1) * m_tile_size.x, tv * m_tile_size.y);
			triangle[2].texCoords = sf::Vector2f((tu + 1) * m_tile_size.x, (tv + 1) * m_tile_size.y);

			// define 3 texture coordinates for second triangle
			triangle[3].texCoords = sf::Vector2f(tu * m_tile_size.x, tv * m_tile_size.y);
			triangle[4].texCoords = sf::Vector2f(tu * m_tile_size.x, (tv + 1) * m_tile_size.y);
			triangle[5].texCoords = sf::Vector2f((tu + 1) * m_tile_size.x, (tv + 1) * m_tile_size.y);
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

void TileMap::read_level_from_file(const std::string filename)
{

	std::ifstream in_file;
	in_file.open(filename);

	m_tiles_map.resize(19);

	if (in_file.is_open()) {

		for (int rows = 0; rows != 19; rows++)
		{
			m_tiles_map[rows].resize(27);

			for (int cols = 0; cols != 27; cols++)
			{	
				int tile_id;
				in_file >> tile_id;

					if (tile_id == 0)
					{
						m_tiles_map[rows][cols] = std::make_unique<GrassTile>();
					}
					else if (tile_id == 1)
					{
						m_tiles_map[rows][cols] = std::make_unique<WaterTile>();
					}
					else if (tile_id == 2)
					{
						m_tiles_map[rows][cols] = std::make_unique<BushTile>();
					}
					else if (tile_id == 3)
					{
						m_tiles_map[rows][cols] = std::make_unique<BrickTile>();
					}
				}			
		}
	}
	else {

		std::cerr << "Could not open the file - '"
			<< filename << "'" << std::endl;
	}

	in_file.close();

}

bool TileMap::get_tile_walkable_by_coordinates(int x, int y)
{
	int tileX = x / m_tile_size.x;
	int tileY = y / m_tile_size.y;
	bool get_tile_walkable = m_tiles_map[tileY][tileX]->get_walkable();

	return get_tile_walkable;
}

sf::Vector2f TileMap::get_tile_coordinates(int x, int y)
{
	int tileX = x / m_tile_size.x;
	int tileY = y / m_tile_size.y;
	sf::Vector2f get_tile_coordinates(tileX, tileY);

	return get_tile_coordinates;

}

bool TileMap::get_tile_walkable_by_indices(int x, int y)
{
	bool get_tile_walkable = m_tiles_map[y][x]->get_walkable();

	return get_tile_walkable;
}


int TileMap::get_rows()
{
	return m_height;
}

int TileMap::get_columns()
{
	return m_width;
}

sf::Vector2u TileMap::get_tile_size()
{
	return m_tile_size;
}





