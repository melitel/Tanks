#include "FireCommand.h"
#include "Game.h"

extern Game* g_Game;

void FireCommand::execute()
{
	g_Game->projectile_shoot(g_Game->get_player_tank());
}
