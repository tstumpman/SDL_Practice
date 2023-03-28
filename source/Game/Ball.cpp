#include "Ball.h"
#include "../MathConstants.h"
#include "SDL/SDL.h"
#include "Paddle.h"
#include "Projectile.h"

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
	(*this) = Ball();
	this->boundaryMinimum = boundaryMinimum;
	this->boundaryMaximum = boundaryMaximum;
	this->size = size;
	this->maxSpeed = maxSpeed;
	this->velocity = velocity;
	*(this->color) = *(color);
	this->isAlive = false;
}

Ball::Ball() {
	this->color = nullptr;
	this->boundaryMinimum = Vector2D();
	this->boundaryMaximum = Vector2D();
	this->size = Vector2D();
	this->velocity = Vector2D();
	this->maxSpeed = 0.0f;
	this->isAlive = false;
	allocateNewData();
}

void Ball::allocateNewData() {
	if (this->color == nullptr) {
		this->color = new SDL_Color();
	}
}

//Copy Assignment operator
Ball& Ball::operator=(const Ball& other) {
	if (this != &other) {
		allocateNewData();
		this->boundaryMaximum = other.boundaryMaximum;
		this->boundaryMinimum = other.boundaryMinimum;
		this->size = other.size;
		this->position = other.position;
		this->velocity = other.velocity;
		(*this->color) = (*other.color);
		this->maxSpeed = other.maxSpeed;
		this->isAlive = other.isAlive;
	}
	return *this;
}

//Copy Constructor
Ball::Ball(const Ball& other) {
	(*this) = other;
}

//Destructor
Ball::~Ball() {
	if (this->color != nullptr) {
		delete this->color;
		this->color = nullptr;
	}
}

void Ball::setIsAlive(bool isEnabled) {
	this->isAlive = isEnabled;
}


void Ball::processInput() {
	//Ball is auto controlled.
}

void Ball::update(float deltaTime) {
	if (!isAlive) return;

	position = position + velocity * deltaTime;
	if (position.getX() < boundaryMinimum.getX()) {
		position = boundaryMaximum * 0.5f;
		velocity = Vector2D();
	}

	if (position.getX() > boundaryMaximum.getX()) {
		position = boundaryMaximum * 0.5f;
		velocity = Vector2D();
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

bool Ball::collidesWith(const ICollideable* other) const {
	if (!getIsAlive()) return false;
	Vector2D otherTopLeft;
	Vector2D otherSize;
	other->getCollisionRect(otherTopLeft, otherSize);
	// Check if the rectangles intersect in the X-axis
	bool xOverlap = ((position.getX() - size.getWidth() / 2) < (otherTopLeft.getX() + otherSize.getWidth())) && ((position.getX() + size.getWidth() / 2) > otherTopLeft.getX());

	// Check if the rectangles intersect in the Y-axis
	bool yOverlap = ((position.getY() - size.getHeight() / 2) < (otherTopLeft.getY() + otherSize.getHeight())) && ((position.getY() + size.getHeight() / 2) > otherTopLeft.getY());

	// Return true if both X-axis and Y-axis overlaps
	return xOverlap && yOverlap;

}

void Ball::resolveCollision(ICollideable* other) {
	//Ball can collide with a paddle and a bullet
	Paddle* paddle = dynamic_cast<Paddle*>(other);
	if (paddle) {
		Vector2D ballCenter = position;
		Vector2D paddleCenter = paddle->getCenter();
		Vector2D newDirection = (ballCenter - paddleCenter).getNormal();
		float previousSpeed = velocity.getMagnitude();
		velocity = newDirection * previousSpeed;
		velocity.clampMagnitude(maxSpeed);
	}

	Projectile* projectile = dynamic_cast<Projectile*>(other);
	if (projectile) {
		Vector2D ballCenter = position;
		Vector2D paddleCenter = projectile->getCenter();
		Vector2D newDirection = (ballCenter - paddleCenter).getNormal();
		float previousSpeed = velocity.getMagnitude();
		//maxSpeed = maxSpeed * 1.1f;
		velocity = newDirection * (previousSpeed + projectile->getSpeed());
	}
}

void Ball::getCollisionRect(Vector2D& topLeft, Vector2D& size) const {
	topLeft = (this->position - (this->size * 0.5f));
	size = this->size;
}

const Vector2D const Ball::getCenter() const {
	return this->position;
}

void Ball::setPosition(Vector2D updatedPosition) {
	this->position = updatedPosition;
}

void Ball::setSpeed(float speed) {
	this->velocity = this->velocity.getNormal() * speed;
}

void Ball::setDirection(Vector2D updatedPosition) {
	this->velocity = updatedPosition.getNormal();
}

Vector2D Ball::getDirection() {
	return this->velocity.getNormal();
}

float Ball::getSpeed() {
	return this->maxSpeed;
}
