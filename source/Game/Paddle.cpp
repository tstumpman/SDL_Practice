#include "Paddle.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "Rect.h"
#include "CollisionComponent.h"
#include "game.h"

//Constructor
Paddle::Paddle(
	Game* game,
	unsigned char upKeyboardCode,
	unsigned char downKeyboardCode,
	float screenOffset
) : Actor(game) {

	Vector2D screenSize = game->getWindowSize();
	int paddleWidth = screenSize.getWidth() / 20.0f;
	int paddleHeight = screenSize.getHeight() / 5.0f;
	Rect body = Rect(
		screenSize.getHeight() / 2.0f - paddleHeight / 2.0f,
		screenSize.getWidth() * screenOffset,
		paddleWidth,
		paddleHeight
	);
	this->setForwardVector(Vector2D(0, -1).getNormal());
	this->upKeyboardCode = upKeyboardCode;
	this->downKeyboardCode = downKeyboardCode;
	this->speed = screenSize.getHeight() / 10.0f;
	
	this->spriteComponent = new SpriteComponent(this);
	this->addComponent(spriteComponent);
	game->addSprite(spriteComponent);

	spriteComponent->setDrawSize(body.getSize());
	spriteComponent->setTexture(game->getTexture("resources/paddle.png"));

	this->inputComponent = new InputComponent(this);
	this->addComponent(inputComponent);
	this->inputComponent->setMaxForwardSpeed(game->getWindowSize().getHeight() / 5.0f);
	this->inputComponent->setMaxAngularSpeed(360.0f);
	inputComponent->setForwardKey(upKeyboardCode);
	inputComponent->setBackwardKey(downKeyboardCode);
	inputComponent->setRotateRightKey(SDL_SCANCODE_Q);
	inputComponent->setRotateLeftKey(SDL_SCANCODE_E);

	this->collisionComponent = new CollisionComponent(this);
	this->addComponent(collisionComponent);
	collisionComponent->setRect( body );
}

//Copy Constructor
Paddle::Paddle(const Paddle& other) : Actor(other) {
	(*this) = other;
}

//Destructor
Paddle::~Paddle() {
	removeComponent(spriteComponent);
	removeComponent(inputComponent);
	removeComponent(collisionComponent);
	delete spriteComponent;
	delete inputComponent;
	delete collisionComponent;
}

void Paddle::actorInput(const uint8_t * keyboardState) {
	inputComponent->processInput(keyboardState);
}

void Paddle::updateActor(float deltaTime) {
}