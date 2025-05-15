#include "Game.h"
#include "TeleportCommand.h"

extern Game* g_Game;

void TeleportCommand::execute()
{
	g_Game->teleport();
}