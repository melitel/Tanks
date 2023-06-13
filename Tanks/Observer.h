#pragma once

class Tank;

class Observer
{
public:	
	virtual void onTankHit(Tank* tank) = 0;
};

