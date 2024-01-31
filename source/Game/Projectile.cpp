#include "Ball.h"
#include "../MathUtils.h"
#include "SDL/SDL.h"
#include "Projectile.h"
#include "Paddle.h"

//Constructor
Projectile::Projectile(
	Vector2D boundaryMinimum,
	Vector2D boundaryMaximum,
	Vector2D size,
	Vector2D position,
	Vector2D velocity,
	SDL_Color* color,
	float maxSpeed,
	Paddle* parent
) :  Ball (
	boundaryMinimum,
	boundaryMaximum, 
	size,
	position, 
	velocity,
	color, 
	maxSpeed
	) {
	this->parent = parent;
}

void Projectile::resolveCollision(ICollideable* other) {
	//Ball can collide with a paddle and a bullet

	Projectile* projectile = dynamic_cast<Projectile*>(other);
	if (projectile && projectile->getIsAlive()) {
		setIsAlive(false);
		projectile->setIsAlive(false);
	}
}

void Projectile::launch(Vector2D startingPosition) {
	if (!getIsAlive()) {
		setPosition(startingPosition);
		setDirection(getDirection());
		setSpeed(getSpeed());
		setIsAlive(true);
	}
}

void Projectile::update(float deltaTime) {
	if (!getIsAlive()) return;

	position = position + velocity * deltaTime;

	float distanceToBoundary = position.vectorToBounds(boundaryMinimum, boundaryMaximum).getMagnitude();
	if (distanceToBoundary > 0.0001 || distanceToBoundary < -0.0001){
		setIsAlive(false);
	}

}