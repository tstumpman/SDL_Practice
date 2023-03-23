#include "Ball.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"

//Constructor
Ball::Ball(
	Vector2D boundaryMinimum,
	Vector2D boundaryMaximum,
	Vector2D size,
	Vector2D position,
	Vector2D velocity,
	SDL_Color* color,
	float maxSpeed
) {
	initialize();
	this->boundaryMinimum = boundaryMinimum;
	this->boundaryMaximum = boundaryMaximum;
	this->size = size;
	this->maxSpeed = maxSpeed;
	this->velocity = velocity;
	*(this->color) = *(color);
	this->isAlive = false;
}

void Ball::initialize() {
	if (this->color == nullptr) {
		this->color = new SDL_Color();
	}
	this->boundaryMinimum = Vector2D();
	this->boundaryMaximum = Vector2D();
	this->size = Vector2D();
	this->velocity = Vector2D();
	this->maxSpeed = 0.0f;
	this->isAlive = false;
}

//Copy Assignment operator
Ball& Ball::operator=(const Ball& other) {
	if (this != &other) {
		*(this->color) = *(other.color);
		this->maxSpeed = other.maxSpeed;
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
Ball::Ball(const Ball& other) {
	initialize();
	*(this->color) = *(other.color);
	this->isAlive = other.isAlive;
}

//Destructor
Ball::~Ball() {
	delete this->color;
	this->color = nullptr;
}

void Ball::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}


void Ball::processInput() {
	//Ball is auto controlled.
}

void Ball::update(float deltaTime) {
	if (!isAlive) return;

	velocity.clampMagnitude(maxSpeed);
	position = position + velocity * deltaTime;
	if (position.getX() < boundaryMinimum.getX()) {
		velocity = velocity.getReflection(Vector2D(1.0f, 0));
	}

	if (position.getX() > boundaryMaximum.getX()) {
		velocity = velocity.getReflection(Vector2D(-1.0f, 0));
	}
	if (position.getY() < boundaryMinimum.getY()) {
		velocity = velocity.getReflection(Vector2D(0.0f, 1.0f));
	}

	if (position.getY() > boundaryMaximum.getY()) {
		velocity = velocity.getReflection(Vector2D(0.0f, -1.0f));
	}


	position.clamp(boundaryMinimum, boundaryMaximum);
}


bool Ball::getIsAlive() const {
	return this->isAlive;
}

void Ball::render(SDL_Renderer* renderer) {
	if (!isAlive)
		return;
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
	SDL_Rect renderRect = SDL_Rect{
		int(position.getX() - size.getX() / 2),
		int(position.getY() - size.getY() / 2),
		int(size.getX()),
		int(size.getX())
	};
	SDL_RenderFillRect(renderer, &renderRect);
}