#ifndef CLASS_GAME
#define CLASS_GAME

#include <string>
#include <vector>
#include <map>

//Included for debugging the engine
#include "FallingBlock.h"
#include "SDL/SDL_scancode.h"
#include "Vector2d.h"


//Forward Declarations
struct SDL_Window;
class SDL_Renderer;
struct SDL_Texture;
class SpriteComponent;
class InputComponent;
class Actor;
class Game {
public://Functions
	Game();


	//Destructor
	~Game();
	bool initialize();
	void runLoop();
	void shutdown();
	void addActor(Actor* newActor);
	void addSprite(SpriteComponent* newSprite);
	void addCollider(CollisionComponent* newSprite);
	bool removeActor(Actor* actor);
	SDL_Texture* getTexture(const std::string& texturePath);

	const Vector2D getWindowSize() const;

private://Functions
	//Copy Assignment operator
	Game& operator=(const Game& other) {};

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
	SDL_Texture* mFontTexture;
	bool isRunning;
	bool isQuitting;
	bool isUpdatingActors;
	std::vector<Actor*> actors;
	std::vector<Actor*> pendingActors;
	std::vector<SpriteComponent*> sprites;
	std::vector<CollisionComponent*> colliders;
	std::map<std::string, SDL_Texture*> loadedTextures;
	

private://Temporary data for debugging purposes only
	void generatePaddle(float xOffset, Vector2D screenSize, SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right);
	void generateHud();
protected:

};
#endif CLASS_GAME