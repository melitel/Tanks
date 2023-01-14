#pragma once
#include "Tile.h"

class GrassTile : public Tile
{
public:

	void update(float dt);

private:

	bool destroyable = false;
	bool walkable = true;
	bool stealth = false;
	bool pierceable = false;
	bool armored = false;

	float move_speed_modificator = 0.f;
};

