#include "AnimationObserver.h"
#include "Animation.h"
#include "Tank.h"
#include <iostream>
#include "Game.h"

extern Game* g_Game;

void AnimationObserver::onTankHit(Tank* tank)
{
	sf::Vector2f tank_position = tank->get_position();
	uint32_t tank_offset = tank->get_tank_offset();
	g_Game->m_animation.play(0, sf::Vector2f(tank_position.x - tank_offset, tank_position.y - tank_offset), "explosioneffect.png");
	std::cout << "Playing animation for tank hit!" << std::endl;
}
