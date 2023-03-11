#include "game.h"
#include "SDL/SDL.h"

Game::Game() {
	isQuitting = false;
	isRunning = true;

}

bool Game::initialize() {
	int result = SDL_Init(SDL_INIT_VIDEO);

	if (result == 0) {
		return true;
	}
	return false;
}

void Game::runLoop() {
	while (!isQuitting) {
		processInput();
		updateGame();
		generateOutput();
	}


}

void Game::shutdown() {
}

void Game::processInput() {

}

void Game::updateGame() {
}

void Game::generateOutput() {
	renderGraphics();
	renderAudio();
}

void Game::renderAudio() {

}

void Game::renderGraphics() {

}