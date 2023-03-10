#include "Game/game.h"
#include <iostream>

int main(int argc, char** argv) {

	Game game;
	bool success = game.initialize();

	if (success) {
		game.runLoop();
	}
	game.shutdown();

	return 0;
}