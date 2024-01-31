#ifndef C_PADDLE
#define C_PADDLE
#include "ICollideable.h"
#include "Vector2D.h"
#include "Projectile.h"
#include "Color.h"
#include "Actor.h"

class Game;
class SpriteComponent;
class InputComponent;
class CollisionComponent;
class Paddle : 
	public Actor {
public: 
	//Default constructor
	Paddle(
		Game* game,
		unsigned char upKeyboardCode,
		unsigned char downKeyboardCode,
		float screenOffset
	);

	//Copy Constructor
	Paddle(const Paddle& other);

	//Destructor
	~Paddle();

public: //GameObject overrides
	virtual void updateActor(float deltaTime) override;
	virtual void actorInput(const uint8_t* keystate);


private: //Functions
	Paddle();

private:
	SpriteComponent* spriteComponent;
	InputComponent* inputComponent;
	CollisionComponent* collisionComponent;
	unsigned char upKeyboardCode, downKeyboardCode;
	float speed;
};

#endif