#include "KillCountObserver.h"
#include "Tank.h"
#include <iostream>

void KillCountObserver::onTankHit(Tank* tank)
{
    tank->kill_count();
    int killCount = tank->get_kill_count();
    std::cout << "Tank was hit! Kill count: " << killCount << std::endl;
}
