#include "Game.h"

Game* game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();

	game->GameLoop();
	
	delete game;

	game = nullptr;

	return 0;
}