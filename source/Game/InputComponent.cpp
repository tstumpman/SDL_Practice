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
}

void InputComponent::setForwardKey(int key) {
	this->forwardKey = key;
}

void InputComponent::setBackwardKey(int key) {
	this->backKey = key;
}

void InputComponent::setRotateRightKey(int key) {
	this->rotateRightKey = key;
}

void InputComponent:: setRotateLeftKey(int key) {
	this->rotateLeftKey = key;
}

void InputComponent::processInput(const uint8_t* keystate) {
	
	if (keystate[forwardKey]) {
		this->setForwardSpeed(maxForwardSpeed);
	} else if (keystate[backKey]) {
		this->setForwardSpeed(-maxForwardSpeed);
	} else {
		this->setForwardSpeed(0.0f);
	}

	if (keystate[rotateLeftKey]) {
		this->setAngularSpeed(maxAngularSpeed);
	} else if (keystate[rotateRightKey]) {
		this->setAngularSpeed(-maxAngularSpeed);
	} else {
		this->setAngularSpeed(0.0f);
	}
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

