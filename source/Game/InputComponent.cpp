#include "InputComponent.h"
#include "Actor.h"
#include "SDL/SDL_keycode.h"

InputComponent::InputComponent(Actor* owner, int updateOrder) : MoveComponent(owner, updateOrder) {
	this->setMaxAngularSpeed(0.0f);
	this->setMaxAngularSpeed(0.0f);
	this->backKey = 255;
	this->forwardKey = 255;
	this->rotateLeftKey = 255;
	this->rotateRightKey = 255;
	this->leftKey = 255;
	this->rightKey = 255;
}

void InputComponent::setForwardKey(int key) {
	this->forwardKey = key;
}

void InputComponent::setBackwardKey(int key) {
	this->backKey = key;
}

void InputComponent::setLeftKey(int key) {
	this->leftKey = key;
}

void InputComponent::setRightKey(int key) {
	this->rightKey = key;
}

void InputComponent::setRotateRightKey(int key) {
	this->rotateRightKey = key;
}

void InputComponent:: setRotateLeftKey(int key) {
	this->rotateLeftKey = key;
}

void InputComponent::processInput(const uint8_t* keystate) {
	float forwardSpeed = 0.0f;
	if (keystate[forwardKey]) {
		forwardSpeed += maxForwardSpeed;
	} 
	if (keystate[backKey]) {
		forwardSpeed -= maxForwardSpeed;
	}
	this->setForwardSpeed(forwardSpeed);

	float horizontalSpeed = 0.0f;
	if (keystate[rightKey]) {
		horizontalSpeed += maxForwardSpeed;
	}
	if (keystate[leftKey]) {
		horizontalSpeed -= maxForwardSpeed;
	}
	this->setHorizontalSpeed(horizontalSpeed);
	float angularSpeed = 0.0f;
	if (keystate[rotateLeftKey]) {
		angularSpeed += maxAngularSpeed;
	}
	if (keystate[rotateRightKey]) {
		angularSpeed -= maxAngularSpeed;
	}
	this->setAngularSpeed(angularSpeed);
}

float InputComponent::getMaxForwardSpeed() const {
	return this->maxForwardSpeed;
}

float InputComponent::getMaxAngularSpeed() const {
	return this->maxAngularSpeed;
}

void InputComponent::setMaxForwardSpeed(float speed) {
	this->maxForwardSpeed = speed;
}

void InputComponent::setMaxAngularSpeed(float speed) {
	this->maxAngularSpeed = speed;
}

