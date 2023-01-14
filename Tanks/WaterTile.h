#pragma once
#include "Tile.h"

class WaterTile : public Tile
{
public:

	void update(float dt);

private:

	bool destroyable = false;
	bool walkable = false;
	bool stealth = false;
	bool pierceable = true;
	bool armored = false;

	float move_speed_modificator = 0.f;
};

