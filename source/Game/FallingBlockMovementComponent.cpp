#include "FallingBlockMovementComponent.h"
#include "Actor.h"

FallingBlockMovementComponent::FallingBlockMovementComponent(Actor* owner, int updateOrder ) : Component(owner, updateOrder) {
	this->fallingSpeed = 0.0f;
	this->timeUntilNextFall = 0.0f;
	this->fallingInterval = 0.0f;
}

float FallingBlockMovementComponent::getFallingSpeed() const {
	return this->fallingSpeed;
}

float FallingBlockMovementComponent::getTimeUntilNextFall() const {
	return this->timeUntilNextFall;
}

float FallingBlockMovementComponent::getFallingInterval() const {
	return this->fallingInterval;
}

void FallingBlockMovementComponent::setFallingSpeed(float newSpeed) {
	this->fallingSpeed = newSpeed;
}

void FallingBlockMovementComponent::setTimeUntilNextFall(float remainingTime) {
	this->timeUntilNextFall = remainingTime;
}

void FallingBlockMovementComponent::setFallingInterval(float timeBetweenMovements) {
	this->fallingInterval = timeBetweenMovements;
}

void FallingBlockMovementComponent::update(float deltaTime) {
	this->timeUntilNextFall -= deltaTime;
	if (this->timeUntilNextFall <= 0) {
		//fall however far you need to fall
		timeUntilNextFall = fallingInterval;
	}
}

