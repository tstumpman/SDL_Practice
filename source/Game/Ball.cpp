#include "Ball.h"
#include "../MathUtils.h"
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
	Vector2D topLeft = (this->position - (this->size * 0.5f));
	SDL_Rect renderRect = SDL_Rect{
		int(topLeft.getX()),
		int(topLeft.getY()),
		int(size.getX()),
		int(size.getY())
	};
	SDL_RenderFillRect(renderer, &renderRect);
}

std::vector<ICollideable*> Ball::collidesWith(const ICollideable* other) {
	std::vector<ICollideable*> collisions = std::vector<ICollideable*>();
	if (!getIsAlive()) return collisions;
	Vector2D otherTopLeft = other->getTopLeft();
	Vector2D otherSize = other->getSize();
	// Check if the rectangles intersect in the X-axis
	bool xOverlap = ((position.getX() - size.getWidth() / 2) < (otherTopLeft.getX() + otherSize.getWidth())) && ((position.getX() + size.getWidth() / 2) > otherTopLeft.getX());

	// Check if the rectangles intersect in the Y-axis
	bool yOverlap = ((position.getY() - size.getHeight() / 2) < (otherTopLeft.getY() + otherSize.getHeight())) && ((position.getY() + size.getHeight() / 2) > otherTopLeft.getY());

	// Return true if both X-axis and Y-axis overlaps
	if (xOverlap && yOverlap)
		collisions.push_back(this);

	return collisions;
}

void Ball::resolveCollision(ICollideable* other) {
	//Ball can collide with a paddle and a bullet
	Paddle* paddle = dynamic_cast<Paddle*>(other);
	if (paddle) {
		Vector2D ballCenter = position;
		Vector2D paddleCenter = paddle->getPosition();
		Vector2D newDirection = (ballCenter - paddleCenter).getNormal();
		float previousSpeed = velocity.getMagnitude();
		velocity = newDirection * previousSpeed;
		velocity.clampMagnitude(maxSpeed);
	}

	Projectile* projectile = dynamic_cast<Projectile*>(other);
	if (projectile && projectile->getIsAlive()) {
		projectile->setIsAlive(false);
		Vector2D ballCenter = position;
		Vector2D paddleCenter = projectile->getCenter();
		Vector2D newDirection = (ballCenter - paddleCenter).getNormal();
		float previousSpeed = velocity.getMagnitude();
		//maxSpeed = maxSpeed * 1.1f;
		Vector2D projectileVelocity = projectile->getDirection() * projectile->getSpeed();
		velocity = newDirection * (previousSpeed + projectile->getSpeed());
	}
}

std::vector<IGameObject*> Ball::getChildren() {
	return std::vector<IGameObject*>();
};

IGameObject* Ball::getParent() {
	return nullptr;
};

Vector2D Ball::getCenter() const {
	return this->position;
}

Vector2D Ball::getTopLeft() const {
	return  (this->position - (this->size * 0.5f));
}

Vector2D Ball::getSize() const {
	return this->size;
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
