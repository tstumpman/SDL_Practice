#ifndef C_FALLING_BLOCK_EMITTER_H
#define C_FALLING_BLOCK_EMITTER_H
#include "game.h"
#include <string>
#include <vector>

class FallingBlock;
class FallingBlockEmitter : public Actor {
public://Functions
	//Default constructor
	FallingBlockEmitter(
		Game* game
	);

	//Destructor
	~FallingBlockEmitter();

	virtual void updateActor(float deltaTime);
	virtual void actorInput(const uint8_t* keystate) override;

private://functions
	FallingBlockEmitter();
protected://functions
public: //Data
private://Data
	FallingBlock* currentBlock;
protected://Data
};

#endif