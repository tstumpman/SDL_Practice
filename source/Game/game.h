#ifndef CLASS_GAME
#define CLASS_GAME

#include <string>
#include <vector>

//Included for debugging the engine
#include "SineWaveObject.h"
#include "Paddle.h"
#include "SDL/SDL_scancode.h"

//Forward Declarations
struct SDL_Window;
class SDL_Renderer;
class Game {
public://Functions
	Game();
	bool initialize();
	void runLoop();
	void shutdown();

private://Functions
	void processInput();
	float getDeltaTime(float previousTimestamp, float currentTimestamp, float maxDelta);
	void updateGame(float deltaTime);
	void generateOutput();
	void renderAudio();
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
	std::vector<SineWaveObject> objects;
	std::vector<Paddle> paddles;
	void generateSomeObjects(int numObjects);
	void generatePaddle(int xPos, SDL_Rect* screenDimens, SDL_Scancode up, SDL_Scancode down);
	void randomizeObject(SineWaveObject * obj);
protected:

};
#endif CLASS_GAME