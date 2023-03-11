#include "game.h"
#include "SDL/SDL.h"

Game::Game() {
	isQuitting = false;
	isRunning = true;
	mWindow = nullptr;
}

bool Game::initialize() {
	int sdlFlags = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER;
	int sdlResult = SDL_Init(sdlFlags);

	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	int sdlWindowOptions = SDL_WINDOW_OPENGL;
	mWindow = SDL_CreateWindow(
	"Window Title Goes Here",//Window Title
		100,//Top Left X coord
	    100,//Top Left Y coord
		240,//Window Width
		160,//Window Height
		sdlWindowOptions// Window flags
	);

	if (!mWindow) {
		logSdlError(SDL_GetError());
		return false;
	}
	return true;
}

void Game::logSdlError(std::string errorMessage) {
	std::vector<std::string> a = std::vector<std::string>();
	a.push_back(errorMessage);
	logSdlError(a);
}

void Game::logSdlError(std::vector<std::string> messages) {
	for (int i = 0; i < messages.size(); i++) {
		SDL_Log(messages[i].c_str());
	}
}

void Game::runLoop() {
	while (!isQuitting) {
		processInput();
		updateGame();
		generateOutput();
	}


}

void Game::shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
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