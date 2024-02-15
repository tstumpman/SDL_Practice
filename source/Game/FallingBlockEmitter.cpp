#include "FallingBlockEmitter.h"
#include "SDL/SDL.h"

//Constructor
FallingBlockEmitter::FallingBlockEmitter(
	Game* game
) :
	Actor(game)
{
	this->currentBlock = nullptr;
}

//Destructor
FallingBlockEmitter::~FallingBlockEmitter() {

}

void FallingBlockEmitter::actorInput(const uint8_t* keystate) {
}


void FallingBlockEmitter::updateActor(float deltaTime) {

}