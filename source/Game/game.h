#ifndef CLASS_GAME
#define CLASS_GAME

#include <string>
#include <vector>

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
	long long getDeltaTime(long long previousTimestamp, long long maxDelta);
	void updateGame(long long deltaTime);
	void generateOutput();
	void renderAudio();
	void renderGraphics();
	void logSdlError( std::string errorMessage);
	void logSdlError(std::vector<std::string> messages);

private://Data
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool isRunning;
	bool isQuitting;
protected:

};
#endif CLASS_GAME