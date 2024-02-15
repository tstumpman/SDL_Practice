#include "game.h"
#include "SDL/SDL.h"
#include "SDL/SDL_Image.h"
#include "../VideoConstants.h"
#include "../MathUtils.h"
#include "TextChunk.h"
#include "Vector2DTest.h"
#include "Actor.h"
#include "Color.h"
#include "FallingBlockGrid.h"
#include "MonospaceCharacter.h"
#include "inputcomponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "TextChunk.h"
#include "FpsCounter.h"
using namespace std;

Game::Game() {
	isQuitting = false;
	isRunning = true;
	mWindow = nullptr;
	mRenderer = nullptr;
	mFontTexture = nullptr;
	minimumFrameLimit = 1.0f / 60.0f;//1/60th of a second
	maxDelta = 1.0f / 8.0f;//1/8th of a second
	loadedTextures = std::map<std::string, SDL_Texture*>();
}

Game::~Game() {
	shutdown();

	loadedTextures.clear();
}

bool Game::initialize() {
	int sdlFlags = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER;
	int sdlResult = SDL_Init(sdlFlags);

	Vector2D windowSize = Vector2D(GBA_WIDTH * 3, GBA_HEIGHT * 3 );

	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// get the SDL2 version
	SDL_version version;
	SDL_GetVersion(&version);
	printf("SDL2 version: %d.%d.%d\n", version.major, version.minor, version.patch);

	int sdlWindowOptions = SDL_WINDOW_OPENGL;
	mWindow = SDL_CreateWindow(
		"Window Title Goes Here",	//Window Title
		100,						//Top Left X coord
		100,						//Top Left Y coord
		windowSize.x,		//Window Width
		windowSize.y,		//Window Height
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

	// Initialize SDL_image
	int imgResult = IMG_Init(IMG_INIT_PNG);
	if(imgResult == 0) {
			SDL_Log("Unable to initialize SDL Image: %s", SDL_GetError());
			return false;
		}

	Vector2DTest vectortest = Vector2DTest();
	int vectorErrors = vectortest.runTests();
	if (vectorErrors != 0) {
		return false;
	}

	generatePaddle(0.4, windowSize, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);

	generateHud();
	return true;
}

SDL_Texture* Game::getTexture(const std::string& texturePath) {
	// Check if the texture is already loaded
	auto it = loadedTextures.find(texturePath);
	if (it != loadedTextures.end()) {
		// Texture is already loaded, return it
		return it->second;
	}

	// Load the texture
	SDL_Texture* newTexture = IMG_LoadTexture(mRenderer, texturePath.c_str());
	if (!newTexture) {
		SDL_Log("Unable to load texture %s: %s", texturePath.c_str(), SDL_GetError());
		return nullptr;
	}

	// Add the new texture to the map
	loadedTextures[texturePath] = newTexture;

	return newTexture;
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
		//if (deltaTime > minimumFrameLimit) {
			processInput();
			updateGame(deltaTime);
			generateOutput();
			previousTime = currentTimestamp;
		//}
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
	while (!actors.empty()) {
		delete actors.back();
	}

	while (!pendingActors.empty()) {
		delete pendingActors.back();
	}

	//Shutdown in reverse order of creation.  Last in, first out.
	//Iterate through all the loaded textures and destroy them
	for (auto& texturePair : loadedTextures) {
		SDL_DestroyTexture(texturePair.second);
	}
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

	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;
}

void Game::updateGame(float deltaTime) {

	//Update actors
	isUpdatingActors = true;
	for (auto actor : actors) {
		actor->update(deltaTime);
	}
	isUpdatingActors = false;  

	for (auto pendingActor : pendingActors) {
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();


	std::vector<Actor*> deadActors;
	for (auto actor : actors) {
		if (actor->getState() == Actor::State::Dead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors) {
		delete deadActor;
	}
}

void Game::generateOutput() {
	renderGraphics();
	renderAudio();
}

void Game::renderAudio() {

}

void Game::renderGraphics() {
	//clear the backbuffer
	SDL_SetRenderDrawColor(
		mRenderer,	//
		0,			//R
		0,			//G
		0,			//B
		0			//A
	);
	SDL_RenderClear(mRenderer);

	for (auto sprite : sprites) {
		sprite->draw(mRenderer);
	}

	//Swap the front and backbuffers.
	SDL_RenderPresent(mRenderer);
}

const Vector2D Game::getWindowSize() const {
	int w, h;
	SDL_GetWindowSize(mWindow, &w, &h);
	return Vector2D(w, h);
}

void Game::generateHud( ) {
	Vector2D textBoxSize = this->getWindowSize() * Vector2D(1, 1.0 / 4.0);
	SDL_Color blue = SDL_Color{ 0, 0, 255, 255 };
	FpsCounter *fpsCounter = new FpsCounter(this);
	fpsCounter->setBackgroundColor(blue);

	Vector2D gridSize = this->getWindowSize();
	CartesianCoordinate gridDimensions = CartesianCoordinate(16, 9);
	FallingBlockGrid* grid = new FallingBlockGrid(this, gridSize, gridDimensions);
	CartesianCoordinate index2d = CartesianCoordinate(0, 0);
	Rect screenRect = Rect(
		grid->getCellPosition(index2d),
		grid->getCellSize()
	);
	//MonospaceCharacter * ch = new MonospaceCharacter(this, screenRect, "resources/monospace_light.png");
	//ch->setCharacter('6');
	//grid->setItem(index2d, ch);

	//index2d = CartesianCoordinate(1,1);
	//screenRect = Rect(
	//	grid->getCellPosition(index2d),
	//	grid->getCellSize()
	//);
	//ch = new MonospaceCharacter(this, screenRect, "resources/monospace_light.png");
	//ch->setCharacter(54);
	//grid->setItem(index2d, ch);

}


void Game::generatePaddle(float xOffset, Vector2D screenSize, SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right ) {
	new FallingBlock(
		this,
		up,
		down,
		left,
		right,
		xOffset
	);
}

void Game::addActor(Actor* actor) {
	if (isUpdatingActors) {
		pendingActors.emplace_back(actor);
	} else {
		actors.emplace_back(actor);
	}
}

bool Game::removeActor(Actor* actor) {
	bool erasedPending = false;
	bool erasedNonPending = false;

	auto it = std::find(pendingActors.begin(), pendingActors.end(), actor);
	if (it != pendingActors.end()) {
		pendingActors.erase(it);
		erasedPending = true;
	}

	if (!isUpdatingActors) {
		auto itActors = std::find(actors.begin(), actors.end(), actor);
		if (itActors != actors.end()) {
			actors.erase(itActors);
			erasedNonPending = true;
		}
	}

	return erasedNonPending || erasedPending;
}


void Game::addSprite(SpriteComponent* newComponent) {
	int drawOrder = newComponent->getDrawOrder();
	auto currentSprite = sprites.begin();
	for (; currentSprite != sprites.end(); ++currentSprite) {
		if (drawOrder < (*currentSprite)->getDrawOrder()) {
			break;
		}
	}
	sprites.insert(currentSprite, newComponent);
}

void Game::addCollider(CollisionComponent* newComponent) {
	int drawOrder = newComponent->getUpdateOrder();
	auto currentComponent = colliders.begin();
	for (; currentComponent != colliders.end(); ++currentComponent) {
		if (drawOrder < (*currentComponent)->getUpdateOrder()) {
			break;
		}
	}
	colliders.insert(currentComponent, newComponent);
}