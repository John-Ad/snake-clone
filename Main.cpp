#include "Game_Engine.h"

int main()
{
	srand(time(NULL));

	Game_Engine game;
	while (game.running())
	{
		game.update();
		game.render();
	}
}