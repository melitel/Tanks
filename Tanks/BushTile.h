#pragma once
#include "Tile.h"

class BushTile : public Tile
{
public:

	void update(float dt);

private:

	bool destroyable = false;
	bool walkable = true;
	bool stealth = true;
	bool pierceable = true;
	bool armored = false;

	float move_speed_modificator = 0.f;
};

