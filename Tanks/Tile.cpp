#include "Tile.h"

void Tile::update(float dt)
{

}

int Tile::get_id()
{
	return m_tileID;

}

bool Tile::get_walkable()
{
	return m_walkable;
}

bool Tile::get_visible()
{
	return m_view_through;
}


