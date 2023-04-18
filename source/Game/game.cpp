#include "game.h"
#include "SDL/SDL.h"
#include "SDL/SDL_Image.h"
#include "../VideoConstants.h"
#include "../MathConstants.h"
#include "Ball.h"
#include "Vector2DTest.h"
using namespace std;

Game::Game() {
	isQuitting = false;
	isRunning = true;
	mWindow = nullptr;
	minimumFrameLimit = 1.0f / 60.0f;//1/60th of a second
	maxDelta = 1.0f / 8.0f;//1/8th of a second
	gameObjects = std::vector<IGameObject*>();
}
Game::~Game() {
	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
		gameObjects[i] = nullptr;
	}
}

bool Game::initialize() {
	int sdlFlags = SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER;
	int sdlResult = SDL_Init(sdlFlags);

	Vector2D windowSize = Vector2D(GBA_WIDTH * 3, GBA_HEIGHT * 3 );

	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	int sdlWindowOptions = SDL_WINDOW_OPENGL;
	mWindow = SDL_CreateWindow(
		"Window Title Goes Here",	//Window Title
		100,						//Top Left X coord
		100,						//Top Left Y coord
		windowSize.getWidth(),		//Window Width
		windowSize.getHeight(),		//Window Height
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

	rightPaddle = generatePaddle(windowSize.getWidth(), windowSize, SDL_SCANCODE_I, SDL_SCANCODE_K);
	leftPaddle = generatePaddle(0, windowSize, SDL_SCANCODE_W, SDL_SCANCODE_S);
	generateBall(windowSize);
	fontTexture = IMG_LoadTexture(mRenderer, "resources/basic_font_monospace.png");
	if (!fontTexture) {
		logSdlError(SDL_GetError());
		return false;
	}
	generateHud(fontTexture);
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
	SDL_DestroyTexture(fontTexture);
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

	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->processInput();
	}
}

void Game::updateGame(float deltaTime) {
	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update(deltaTime);
	}

	//UNSUSTAINABLE FOR LARGE GROUPS OF COLLIDEABLE OBJECTS!!!
	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		ICollideable* collideable1 = dynamic_cast<ICollideable*> (gameObjects[i]);
		if (collideable1) {
			for (unsigned int j = i+1; j < gameObjects.size(); j++) {
				ICollideable* collideable2 = dynamic_cast<ICollideable*> (gameObjects[j]);
				if (collideable2) {
					if (collideable1->collidesWith(collideable2)) {
						collideable1->resolveCollision(collideable2);
						collideable2->resolveCollision(collideable1);
					}
				}
			}
		}
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
		0,		//R
		0,			//G
		0,		//B
		0			//A
	);
	SDL_RenderClear(mRenderer);
	//Draw the scene.
	std::string messageDisplay = std::to_string(SDL_GetTicks()/1000);
	gameHud->setText(messageDisplay);
	for (unsigned int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->render(mRenderer);
	}

	//Swap the front and backbuffers.
	SDL_RenderPresent(mRenderer);
}

void Game::generateBall(Vector2D screenSize) {
	SDL_Color white = SDL_Color{ 255, 128, 0, 255 };
	float startingSpeed = screenSize.getWidth() / 2.0f;
	Vector2D startingVelocity = Vector2D(rand() % 1000, rand() % 1000).getNormal() * startingSpeed;
	float ballSize = screenSize.getMagnitude() * 0.05f;
	gameBall = new Ball(
		Vector2D(-50, 0),//top left
		Vector2D(screenSize.getX()+50, screenSize.getY()),//bottom right
		Vector2D(ballSize, ballSize),//size
		screenSize * 0.5f,//position
		startingVelocity,//velocity
		&white,
		startingSpeed
	);
	gameBall->setIsAlive(true); 

	gameObjects.push_back(gameBall);
}

void Game::generateHud(SDL_Texture* fontTexture ) {
	SDL_Color white = SDL_Color{ 255, 255, 255, 255 };
	gameHud = new TextChunk(
		Vector2D(0, 0),//top left
		Vector2D( 50, 50),//boundary Size
		Vector2D( 10, 10),//letter size
		&white,
		fontTexture
	);
	gameHud->setIsAlive(true);
	gameObjects.push_back(gameHud);
}

Paddle* Game::generatePaddle(int xPos, Vector2D screenSize, SDL_Scancode up, SDL_Scancode down) {

	int paddleWidth = screenSize.getWidth() / 20.0f;
	int paddleHeight = screenSize.getHeight() / 5.0f;
	int yPos = screenSize.getHeight() / 2.0f - paddleHeight / 2.0f;
	SDL_Rect paddleShape = SDL_Rect{ xPos, yPos, paddleWidth, paddleHeight };
	SDL_Rect screenDimens = SDL_Rect{ 0, 0, (int)screenSize.getWidth(), (int)screenSize.getHeight()};
	SDL_Color white = SDL_Color{ 128, 0, 255, 255 };
	Vector2D centerDot = screenSize * 0.5f;
	Vector2D paddleNormal = (centerDot - Vector2D(xPos, centerDot.getY())).getNormal();
	Paddle* p = new Paddle(
		up,
		down,
		screenSize,
		Vector2D(paddleWidth, paddleHeight),
		Vector2D(xPos, screenSize.getHeight()/2),
		paddleNormal,
		&white,
		screenSize.getHeight()
	);
	p->setIsAlive(true);
	gameObjects.push_back(p);
	gameObjects.push_back(p->getBullet());
	return p;
}

void Game::generateSomeObjects(unsigned int numObjects) {
	srand(SDL_GetTicks());

	for (unsigned int i = 0; i < numObjects; i++) {
		SineWaveObject * obj = new SineWaveObject(generateParticle());
		gameObjects.push_back(obj);
	}
}

SineWaveObject Game::generateParticle() {
	int screenHeight = GBA_HEIGHT * 3;
	int screenWidth = GBA_WIDTH * 3;
	uint8_t r = rand() % 255;
	uint8_t g = rand() % 255;
	uint8_t b = rand() % 255;
	SDL_Color color = SDL_Color{ r, g, b, 255 };
	SDL_Rect shape = SDL_Rect{ rand() % screenHeight, 0, rand() % 10 + 30, rand() % 10 + 30 };
	SDL_Rect boundary = SDL_Rect{ 0, 0, screenWidth, screenHeight };
	return SineWaveObject(
		rand() % screenHeight,//Anchor
		(rand() % screenWidth) * 0.5 +1.0f,//speed
		(rand() % screenHeight)*0.5f,//amplitude
		rand() % 100 / 50.0f,//frequency
		&shape,//height
		&boundary,//width
		&color//color
	);
}