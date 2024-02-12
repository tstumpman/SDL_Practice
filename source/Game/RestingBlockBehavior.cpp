#include "RestingBlockBehavior.h"
#include "Actor.h"

RestingBlockBehavior::RestingBlockBehavior(Actor* owner, int updateOrder ) : Component(owner) {
	this->remainingTimeUntilFreeze = 0.0f;
	this->maxTimeUntilFreeze = 0.0f;
}

float RestingBlockBehavior::getRemainingTimeUntilFreeze() const {
	return this->remainingTimeUntilFreeze;
}

float RestingBlockBehavior::getMaxTimeUntilFreeze() const {
	return this->maxTimeUntilFreeze;
}

void RestingBlockBehavior::setRemainingTimeUntilFreeze(float remainingTime) {
	this->remainingTimeUntilFreeze = remainingTime;
}

void RestingBlockBehavior::setMaxTimeUntilFreeze(float maxTime) {
	this->maxTimeUntilFreeze = maxTime;
}

bool RestingBlockBehavior::isResting() {
	
	return false;
}

void RestingBlockBehavior::update(float deltaTime) {
	if (isResting()) {
		this->remainingTimeUntilFreeze -= deltaTime;
		if (this->remainingTimeUntilFreeze <= 0.0f) {
			owner->setState(Actor::State::Paused);
		}
	}
	else {
		this->remainingTimeUntilFreeze = this->maxTimeUntilFreeze;
	}
}

