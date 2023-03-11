#ifndef CLASS_GAME
#define CLASS_GAME


struct SDL_Window;
class Game {
public:
	Game();
	bool initialize();

	void runLoop();

	void shutdown();
private:

	void processInput();
	void updateGame();
	void generateOutput();
	void renderAudio();
	void renderGraphics();

	//SDL_Window* mWindow;

	bool isRunning;
	bool isQuitting;
protected:

};
#endif CLASS_GAME