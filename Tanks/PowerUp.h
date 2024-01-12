#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Tank;

class PowerUp
{
public:

	virtual void activate(Tank* tank) = 0;

protected:

	void boost_speed(float speed_boost);
	void add_hp(unsigned int life_boost);
	Tank* tank_to_boost;
};

