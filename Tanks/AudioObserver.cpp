#include "AudioObserver.h"
#include "Tank.h"
#include <iostream>

void AudioObserver::onTankHit(Tank* tank)
{
	std::cout << "Playing audio for tank hit!" << std::endl;
}
