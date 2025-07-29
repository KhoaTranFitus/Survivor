#include "Game.h"
#include "Assets.h"
int main()
{
	// Load assets
	Assets::init();

	Game* game = new Game();
	game->run();
	delete game;
	return 0;
}