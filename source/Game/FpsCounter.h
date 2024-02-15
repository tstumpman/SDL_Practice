#ifndef C_FPS_COUNTER_H
#define C_FPS_COUNTER_H
#include "game.h"
#include "TextChunk.h"
#include <vector>
class MonospaceCharacter;
class InputComponent;
struct SDL_Texture;
class FpsCounter : public TextChunk {
public://Functions
	//Default constructor
	FpsCounter(Game* game);

	//Destructor
	~FpsCounter();

	virtual void updateActor(float deltaTime);
	virtual void actorInput(const uint8_t* keystate) override;

private://functions
	FpsCounter();
protected://functions
public: //Data
private://Data
	float timeSinceLastRender;
	float timeSinceLastReset;
	unsigned int framesSinceReset;
	float timeBetweenReset;
	float timeBetweenRenders;
protected://Data
};

#endif