#ifndef CLASS_GAME
#define CLASS_GAME

#include <string>
#include <vector>
#define PI 3.14159265f
#define RADIANS_PER_CIRCLE PI*2

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
	float objPosX;
	float objPosY;
	float rotation;
	float frequency;
	float amplitude;
protected:

};
#endif CLASS_GAME