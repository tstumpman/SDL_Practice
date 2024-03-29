#include "FallingBlock.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "Rect.h"
#include "CollisionComponent.h"

#include "game.h"

//Constructor
FallingBlock::FallingBlock(
	Game* game,
	unsigned char upKeyboardCode,
	unsigned char downKeyboardCode,
	unsigned char rightKeyboardCode,
	unsigned char leftKeyboardCode,
	float screenOffset
) : Actor(game) {

	Vector2D screenSize = game->getWindowSize();
	int fallingBlockWidth = screenSize.x / 20.0f;
	int fallingBlockHeight = screenSize.y / 5.0f;
	Rect body = Rect(
		screenSize.x * screenOffset,
		screenSize.y / 2.0f - fallingBlockHeight / 2.0f,
		fallingBlockWidth,
		fallingBlockHeight
	);
	this->setForwardVector(Vector2D(0, -1).getNormal());
	this->setPosition(body.getOrigin());
	
	this->spriteComponent = new SpriteComponent(this);

	spriteComponent->setDrawSize(body.getSize());
	spriteComponent->setTexture(game->getTexture("resources/paddle.png"));

	this->inputComponent = new InputComponent(this);
	this->inputComponent->setMaxForwardSpeed(game->getWindowSize().x / 5.0f);
	this->inputComponent->setMaxAngularSpeed(360.0f);
	inputComponent->setForwardKey(upKeyboardCode);
	inputComponent->setBackwardKey(downKeyboardCode);
	//inputComponent->setLeftKey(leftKeyboardCode);
	//inputComponent->setRightKey(rightKeyboardCode);
	inputComponent->setRotateLeftKey(leftKeyboardCode);
	inputComponent->setRotateRightKey(rightKeyboardCode);

	this->collisionComponent = new CollisionComponent(this);
	collisionComponent->setSize( body.getSize() );

	getGame()->addSprite(spriteComponent);
	getGame()->addCollider(collisionComponent);
}

//Copy Constructor
FallingBlock::FallingBlock(const FallingBlock& other) : Actor(other) {

	this->setForwardVector(Vector2D(0, -1).getNormal());

	this->spriteComponent = new SpriteComponent(this);
	getGame()->addSprite(spriteComponent);

	spriteComponent->setDrawSize(other.spriteComponent->getDrawSize());
	spriteComponent->setTexture(getGame()->getTexture("resources/paddle.png"));

	this->inputComponent = new InputComponent(this);
	this->inputComponent->setMaxForwardSpeed(other.inputComponent->getMaxForwardSpeed());
	this->inputComponent->setMaxAngularSpeed(other.inputComponent->getMaxAngularSpeed());

	this->collisionComponent = new CollisionComponent(this);
	collisionComponent->setSize(other.spriteComponent->getDrawSize());
	getGame()->addSprite(spriteComponent);
	getGame()->addCollider(collisionComponent);
}

//Destructor
FallingBlock::~FallingBlock() {
	removeComponent(spriteComponent);
	removeComponent(inputComponent);
	removeComponent(collisionComponent);
	delete spriteComponent;
	delete inputComponent;
	delete collisionComponent;
}

void FallingBlock::actorInput(const uint8_t * keyboardState) {
	inputComponent->processInput(keyboardState);
}

void FallingBlock::updateActor(float deltaTime) {
	Rect gameWindow = Rect(Vector2D(0, 0), getGame()->getWindowSize());
	Rect overlap = collisionComponent->getRect().getIntersection(gameWindow);
	if (overlap.area() == 0.0f) {
		Vector2D directionToOrigin = (gameWindow.getOrigin() - getPosition()).getAxisAligned();
		Vector2D sizeOffset = directionToOrigin * collisionComponent->getRect().getSize();
		Vector2D windowOffset = directionToOrigin * (gameWindow.getSize());
		Vector2D move = sizeOffset + windowOffset;
		this->translateBy(move);
	}
}