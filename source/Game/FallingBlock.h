#ifndef C_FALLING_BLOCK_H
#define C_FALLING_BLOCK_H
#include "Vector2D.h"
#include "Color.h"
#include "Actor.h"

class Game;
class SpriteComponent;
class InputComponent;
class CollisionComponent;
class FallingBlock : 
	public Actor {
public: 
	//Default constructor
	FallingBlock(
		Game* game,
		unsigned char upKeyboardCode,
		unsigned char downKeyboardCode,
		unsigned char leftKeyboardCode,
		unsigned char rightKeyboardCode,
		float screenOffset
	);

	//Copy Constructor
	FallingBlock(const FallingBlock& other);

	//Destructor
	~FallingBlock();

public: //GameObject overrides
	virtual void updateActor(float deltaTime) override;
	virtual void actorInput(const uint8_t* keystate);

private: //Functions
	FallingBlock();

private:
	SpriteComponent* spriteComponent;
	InputComponent* inputComponent;
	CollisionComponent* collisionComponent;

protected:
};

#endif