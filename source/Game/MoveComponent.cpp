#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder ) : Component(owner, updateOrder) {
	this->angularSpeed = 0.0f;
	this->forwardSpeed = 0.0f;
	this->horizontalSpeed = 0.0f;
}

float MoveComponent::getAngularSpeed() const {
	return this->angularSpeed;
}

float MoveComponent::getForwardSpeed() const {
	return this->forwardSpeed;
}
float MoveComponent::getHorizontalSpeed() const {
	return this->horizontalSpeed;
}

void MoveComponent::setAngularSpeed(float speed) {
	this->angularSpeed = speed;
}

void MoveComponent::setForwardSpeed(float speed) {
	this->forwardSpeed = speed;
}

void MoveComponent::setHorizontalSpeed(float speed) {
	this->horizontalSpeed = speed;
}

void MoveComponent::update(float deltaTime) {
	//you may wish to modify this so that if speed is close to zero we just ignore it;

	owner->rotateBy(angularSpeed * deltaTime);
	owner->translateBy(owner->getForwardVector() * forwardSpeed * deltaTime);
	Vector2D rightVector = owner->getForwardVector().getRotation(-90.0);
	owner->translateBy(rightVector * horizontalSpeed * deltaTime);
}

