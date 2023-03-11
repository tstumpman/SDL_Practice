#ifndef CLASS_GAME
#define CLASS_GAME

#include <string>
#include <vector>
struct SDL_Window;
class Game {
public://Functions
	Game();
	bool initialize();
	void runLoop();
	void shutdown();

private://Functions
	void processInput();
	void updateGame();
	void generateOutput();
	void renderAudio();
	void renderGraphics();
	void logSdlError( std::string errorMessage);
	void logSdlError(std::vector<std::string> messages);

private://Data
	SDL_Window* mWindow;
	bool isRunning;
	bool isQuitting;
protected:

};
#endif CLASS_GAME