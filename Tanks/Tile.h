#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tile
{
public:

	Tile (
		int tileID,
		bool destroyable,
		bool walkable,
		bool stealth,
		bool pierceable,
		bool armored,
		bool view_through,
		float move_speed_modificator
	) :
		m_tileID(tileID),
		m_destroyable(destroyable),
		m_walkable(walkable),
		m_stealth(stealth),
		m_pierceable(pierceable),
		m_armored(armored),
		m_view_through(view_through),
		m_move_speed_modificator(move_speed_modificator)
	{}

	void update(float dt);
	int get_id();
	bool get_walkable();
	bool get_visible();
	bool get_pierceable();

protected:

	int m_tileID;
	bool m_destroyable;
	bool m_walkable;
	bool m_stealth;
	bool m_pierceable;
	bool m_armored;
	bool m_view_through;

	float m_move_speed_modificator;

};

