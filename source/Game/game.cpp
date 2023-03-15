#include "game.h"
#include "SDL/SDL.h"
#include "../VideoConstants.h"
#include "../MathConstants.h"

using namespace std;

Game::Game() {
	isQuitting = false;
	isRunning = true;
	mWindow = nullptr;
	minimumFrameLimit = 1.0f / 60.0f;//1/60th of a second
	maxDelta = 1.0f / 8.0f;//1/8th of a second
	objects = vector<SineWaveObject>();
	generateSomeObjects(10);
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
		"Window Title Goes Here",	//Window Title
		100,						//Top Left X coord
		100,						//Top Left Y coord
		(GBA_WIDTH * 3),			//Window Width
		(GBA_HEIGHT * 3),			//Window Height
		sdlWindowOptions			//Window flags
	);

	if (!mWindow) {
		logSdlError(SDL_GetError());
		return false;
	}

	int sdlRendererOptions = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	mRenderer = SDL_CreateRenderer(
		mWindow,			//Window for wich the renderer is created
		-1,					//Usually -1, to let SDL decide which window to render to.  Games can have multiple windows I guess?
		sdlRendererOptions	//Renderer flags
	);

	if (!mRenderer) {
		logSdlError(SDL_GetError());
		return false;
	}

	return true;
}

void Game::logSdlError(string errorMessage) {
	vector<string> a = vector<string>();
	a.push_back(errorMessage);
	logSdlError(a);
}

void Game::logSdlError(vector<string> messages) {
	for (unsigned int i = 0; i < messages.size(); i++) {
		SDL_Log(messages[i].c_str());
	}
}

void Game::runLoop() {
	float previousTime = SDL_GetTicks() / 1000.0f;
	float deltaTime = 0.0f;
	while (isRunning) {
		float currentTimestamp = SDL_GetTicks() / 1000.0f;
		deltaTime = getDeltaTime(previousTime, currentTimestamp, maxDelta);
		if (deltaTime > minimumFrameLimit) {
			processInput();
			updateGame(deltaTime);
			generateOutput();
			previousTime = currentTimestamp;
		}
	}
}

float Game::getDeltaTime(float previousTimestamp, float currentTimestamp, float maxDelta) {
	float delta = currentTimestamp - previousTimestamp;

	if (maxDelta < 0) {
		return delta;
	}

	if (delta > maxDelta) {
		return maxDelta;
	}

	return delta;
}

void Game::shutdown() {
	//Shutdown in reverse order of creation.  Last in, first out.
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::processInput() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	//Get keyboard state;
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE]) {
		isRunning = false;
	}
}

void Game::updateGame(float deltaTime) {
	float screenWidth = GBA_WIDTH * 3.0f;
	float screenHeight = GBA_HEIGHT * 3.0f;
	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i].getIsAlive()) {
			randomizeObject(&objects[i]);
		}
		objects[i].update(deltaTime, screenWidth, screenHeight);
	}

}

void Game::generateOutput() {
	renderGraphics();
	renderAudio();
}

void Game::renderAudio() {

}

void Game::renderGraphics() {
	int windowHeight = 0;
	int windowWidth = 0;
	SDL_GetWindowSize(mWindow, &windowWidth, &windowHeight);

	//clear the backbuffer
	SDL_SetRenderDrawColor(
		mRenderer,	//
		255,		//R
		0,			//G
		255,		//B
		255			//A
	);
	SDL_RenderClear(mRenderer);
	//Draw the scene.
	for (int i = 0; i < objects.size(); i++) {
		objects[i].render(mRenderer);
	}

	//Swap the front and backbuffers.
	SDL_RenderPresent(mRenderer);
}

void Game::generateSomeObjects(int numObjects) {
	srand(SDL_GetTicks());
	int screenHeight = GBA_HEIGHT * 3;
	int screenWidth = GBA_WIDTH * 3;
	srand(SDL_GetTicks());

	for (int i = 0; i < 10; i++) {
		SineWaveObject obj = SineWaveObject();
		objects.push_back(obj);
	}
}

void Game::randomizeObject(SineWaveObject * obj) {
	int screenHeight = GBA_HEIGHT * 3;
	int screenWidth = GBA_WIDTH * 3;
	obj->resetAll(
		rand() % screenWidth,
		rand() % screenHeight,
		rand() % screenHeight,
		rand() % screenWidth,
		rand() % 10 + 30,
		rand() % 10 + 30,
		rand() % screenHeight,
		rand() % 100 / 50.0f,
		rand() % 5,
		rand() % 255,
		rand() % 255,
		rand() % 255
	);
}