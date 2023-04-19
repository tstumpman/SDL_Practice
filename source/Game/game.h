#ifndef CLASS_GAME
#define CLASS_GAME

#include <string>
#include <vector>

//Included for debugging the engine
#include "SineWaveObject.h"
#include "Paddle.h"
#include "Ball.h"
#include "TextChunk.h"
#include "SDL/SDL_scancode.h"

#include "Vector2d.h"

//Forward Declarations
struct SDL_Window;
class SDL_Renderer;
class Game {
public://Functions
	Game();


	//Destructor
	~Game();
	bool initialize();
	void runLoop();
	void shutdown();

private://Functions
	//Copy Assignment operator
	Game& operator=(const Game& other) {};

	//Copy Constructor
	Game(const Game& other) {};

	void processInput();
	float getDeltaTime(float previousTimestamp, float currentTimestamp, float maxDelta);
	void updateGame(float deltaTime);
	void generateOutput();
	void renderAudio();
	Vector2D getWindowSize();
	void renderGraphics();
	void logSdlError( std::string errorMessage);
	void logSdlError(std::vector<std::string> messages);

private://Data
	float minimumFrameLimit;
	float maxDelta;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool isRunning;
	bool isQuitting;

private://Temporary data for debugging purposes only
	std::vector<IGameObject*> gameObjects;
	Ball* gameBall;
	TextChunk* gameHud;
	Paddle* leftPaddle;
	Paddle* rightPaddle;
	void generateSomeObjects(unsigned int numObjects);
	Paddle* generatePaddle(int xPos, Vector2D screenSize, SDL_Scancode up, SDL_Scancode down);
	void generateBall(Vector2D screenSize);
	void generateHud();
	SineWaveObject generateParticle();
protected:

};
#endif CLASS_GAME