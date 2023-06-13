#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <array>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	
	bool load(const std::string& tileset);
	void read_level_from_file(const std::string filename);
	bool get_tile_walkable_by_coordinates(int x, int y);
	sf::Vector2i get_tile_coordinates(int x, int y);
	bool get_tile_walkable_by_indices(int x, int y);
	bool get_tile_view_through_by_indices(int x, int y);
	int get_rows();
	int get_columns();
	sf::Vector2u get_tile_size();	

private:
	
	unsigned int m_width = 27;
	unsigned int m_height = 20;
	sf::Vector2u m_tile_size = sf::Vector2u(32, 32);
	std::vector <std::vector<std::shared_ptr<Tile>>> m_tiles_map;
	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
	
};

